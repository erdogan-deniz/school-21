"""Deposit calculator model: interest accrual with optional capitalization."""

import ctypes
from ctypes import byref, c_double, c_int
from typing import ClassVar

from model.enums import AccrualPeriod
from model.finance_base import FinanceCalculator
from model.lib_loader import load_lib
from model.results import DepositEntry, DepositResult


class DepositCalculator(FinanceCalculator):
    """Compute deposit growth via the C shared library.

    Supports:
    - Monthly, quarterly, or annual payment periodicity.
    - Interest capitalization (compound) or simple payment to account.
    - Lists of scheduled additions and partial withdrawals.
    """

    _MAX_TAX_RATE: ClassVar[int] = 100

    _PERIODS: ClassVar[dict[AccrualPeriod, int]] = {
        AccrualPeriod.MONTHLY: 12,
        AccrualPeriod.QUARTERLY: 4,
        AccrualPeriod.ANNUALLY: 1,
    }

    def __init__(self) -> None:
        """Load the shared library and configure ctypes signatures."""
        self._lib = load_lib()

        self._lib.s21_deposit.restype = c_int
        self._lib.s21_deposit.argtypes = [
            c_double,                   # amount
            c_int,                      # months
            c_double,                   # rate
            c_double,                   # tax
            c_int,                      # periods_per_year
            c_int,                      # capitalize
            ctypes.POINTER(c_int),      # add_months
            ctypes.POINTER(c_double),   # add_amounts
            c_int,                      # add_count
            ctypes.POINTER(c_int),      # wd_months
            ctypes.POINTER(c_double),   # wd_amounts
            c_int,                      # wd_count
            ctypes.POINTER(c_double),   # total_interest (out)
            ctypes.POINTER(c_double),   # tax_out        (out)
            ctypes.POINTER(c_double),   # final_amount   (out)
        ]

    def calculate(
        self,
        amount: float,
        months: int,
        annual_rate: float,
        tax_rate: float,
        period: AccrualPeriod | str,
        capitalize: bool,
        additions: list[DepositEntry] | None = None,
        withdrawals: list[DepositEntry] | None = None,
    ) -> DepositResult:
        """Calculate deposit outcome over the given term via C library.

        Args:
            amount: Initial deposit amount.
            months: Term in months.
            annual_rate: Annual interest rate in percent.
            tax_rate: Tax rate on interest income in percent.
            period: Payment periodicity — AccrualPeriod or its string value.
            capitalize: If True, accrued interest is added to deposit balance.
            additions: List of {'month': int, 'amount': float} dicts.
            withdrawals: List of {'month': int, 'amount': float} dicts.

        Returns:
            Dict with keys: total_interest, tax_amount, final_amount.

        Raises:
            ValueError: If any input is invalid.

        """
        self._validate_inputs(amount, months, annual_rate, tax_rate, period)
        additions = additions or []
        withdrawals = withdrawals or []

        period_enum = AccrualPeriod(period)
        periods_per_year = self._PERIODS[period_enum]

        # Build flat ctypes arrays for additions; pass None (NULL) if empty.
        add_count = len(additions)
        if add_count > 0:
            add_months_arr = (c_int * add_count)(
                *[a["month"] for a in additions]
            )
            add_amounts_arr = (c_double * add_count)(
                *[a["amount"] for a in additions]
            )
        else:
            add_months_arr = None
            add_amounts_arr = None

        # Build flat ctypes arrays for withdrawals; pass None (NULL) if empty.
        wd_count = len(withdrawals)
        if wd_count > 0:
            wd_months_arr = (c_int * wd_count)(
                *[w["month"] for w in withdrawals]
            )
            wd_amounts_arr = (c_double * wd_count)(
                *[w["amount"] for w in withdrawals]
            )
        else:
            wd_months_arr = None
            wd_amounts_arr = None

        total_interest = c_double()
        tax_out = c_double()
        final_amount = c_double()

        rc = self._lib.s21_deposit(
            c_double(amount),
            c_int(months),
            c_double(annual_rate),
            c_double(tax_rate),
            c_int(periods_per_year),
            c_int(1 if capitalize else 0),
            add_months_arr,
            add_amounts_arr,
            c_int(add_count),
            wd_months_arr,
            wd_amounts_arr,
            c_int(wd_count),
            byref(total_interest),
            byref(tax_out),
            byref(final_amount),
        )
        if rc != 0:
            raise ValueError(
                f"C library error in s21_deposit "
                f"(amount={amount}, months={months}, rate={annual_rate})"
            )

        return {
            "total_interest": total_interest.value,
            "tax_amount": tax_out.value,
            "final_amount": final_amount.value,
        }

    @staticmethod
    def _validate_inputs(
        amount: float,
        months: int,
        annual_rate: float,
        tax_rate: float,
        period: AccrualPeriod | str,
    ) -> None:
        """Raise ValueError if any deposit parameter is invalid.

        Args:
            amount: Initial deposit amount; must be positive.
            months: Term in months; must be positive.
            annual_rate: Annual interest rate in percent; must be positive.
            tax_rate: Tax rate on interest income; must be in [0, 100].
            period: Payment periodicity; must be a valid AccrualPeriod value.

        Raises:
            ValueError: If amount, term, rate, tax, or period are invalid.

        """
        if amount <= 0:
            raise ValueError("Deposit amount must be positive.")
        # Intentional: calling protected base-class helper from subclass.
        FinanceCalculator._validate_term_and_rate(  # noqa: SLF001
            months, annual_rate
        )
        if not 0 <= tax_rate <= DepositCalculator._MAX_TAX_RATE:
            raise ValueError("Tax rate must be between 0 and 100.")
        try:
            AccrualPeriod(period)
        except ValueError as exc:
            valid = [p.value for p in AccrualPeriod]
            raise ValueError(f"Period must be one of {valid}.") from exc

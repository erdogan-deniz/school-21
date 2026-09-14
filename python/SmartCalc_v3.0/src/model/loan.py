"""Loan calculator model: annuity and differentiated payment types."""

import ctypes
from ctypes import byref, c_double, c_int

from model.finance_base import FinanceCalculator
from model.lib_loader import load_lib
from model.results import AnnuityResult, DifferentiatedResult


class LoanCalculator(FinanceCalculator):
    """Compute loan payments via the C shared library.

    Supports two payment types:
    - Annuity:        equal monthly payments throughout the loan.
    - Differentiated: decreasing payments (fixed principal + accruing interest).
    """

    def __init__(self) -> None:
        """Load the shared library and configure ctypes signatures."""
        self._lib = load_lib()

        self._lib.s21_loan_annuity.restype = c_int
        self._lib.s21_loan_annuity.argtypes = [
            c_double,                  # principal
            c_int,                     # months
            c_double,                  # rate
            ctypes.POINTER(c_double),  # *monthly_payment (out)
            ctypes.POINTER(c_double),  # *overpayment     (out)
            ctypes.POINTER(c_double),  # *total           (out)
        ]

        self._lib.s21_loan_differentiated.restype = c_int
        self._lib.s21_loan_differentiated.argtypes = [
            c_double,                  # principal
            c_int,                     # months
            c_double,                  # rate
            ctypes.POINTER(c_double),  # *payments_out array (out)
            ctypes.POINTER(c_double),  # *overpayment        (out)
            ctypes.POINTER(c_double),  # *total              (out)
        ]

    def calculate_annuity(
        self,
        principal: float,
        months: int,
        annual_rate: float,
    ) -> AnnuityResult:
        """Compute annuity (equal) monthly payments via C library.

        Args:
            principal: Total loan amount in currency units.
            months: Loan term in months.
            annual_rate: Annual interest rate in percent (e.g. 12.5).

        Returns:
            AnnuityResult with monthly_payment, overpayment, total.

        Raises:
            ValueError: If any input is non-positive.

        """
        self._validate_inputs(principal, months, annual_rate)
        monthly = c_double()
        overpayment = c_double()
        total = c_double()
        rc = self._lib.s21_loan_annuity(
            c_double(principal),
            c_int(months),
            c_double(annual_rate),
            byref(monthly),
            byref(overpayment),
            byref(total),
        )
        if rc != 0:
            raise ValueError(
                f"C library error in s21_loan_annuity "
                f"(principal={principal}, months={months}, "
                f"rate={annual_rate})"
            )
        return {
            "monthly_payment": monthly.value,
            "overpayment": overpayment.value,
            "total": total.value,
        }

    def calculate_differentiated(
        self,
        principal: float,
        months: int,
        annual_rate: float,
    ) -> DifferentiatedResult:
        """Compute differentiated (decreasing) monthly payments via C library.

        Args:
            principal: Total loan amount in currency units.
            months: Loan term in months.
            annual_rate: Annual interest rate in percent (e.g. 12.5).

        Returns:
            DifferentiatedResult with first_payment, last_payment,
            overpayment, total, payments.

        Raises:
            ValueError: If any input is non-positive.

        """
        self._validate_inputs(principal, months, annual_rate)
        payments_array_cls = c_double * months
        payments_arr = payments_array_cls()
        overpayment = c_double()
        total = c_double()
        rc = self._lib.s21_loan_differentiated(
            c_double(principal),
            c_int(months),
            c_double(annual_rate),
            payments_arr,
            byref(overpayment),
            byref(total),
        )
        if rc != 0:
            raise ValueError(
                f"C library error in s21_loan_differentiated "
                f"(principal={principal}, months={months}, "
                f"rate={annual_rate})"
            )
        payments = list(payments_arr)
        return {
            "first_payment": payments[0],
            "last_payment": payments[-1],
            "overpayment": overpayment.value,
            "total": total.value,
            "payments": payments,
        }

    @staticmethod
    def _validate_inputs(
        principal: float, months: int, annual_rate: float
    ) -> None:
        """Raise ValueError if any loan parameter is invalid.

        Args:
            principal: Total loan amount; must be positive.
            months: Loan term in months; must be positive.
            annual_rate: Annual interest rate in percent; must be positive.

        Raises:
            ValueError: If principal, months, or annual_rate are invalid.

        """
        if principal <= 0:
            raise ValueError("Principal must be positive.")
        # Intentional: calling protected base-class helper from subclass.
        FinanceCalculator._validate_term_and_rate(  # noqa: SLF001
            months, annual_rate
        )

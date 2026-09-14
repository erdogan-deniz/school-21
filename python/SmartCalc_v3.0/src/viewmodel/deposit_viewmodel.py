"""ViewModel for the deposit calculator."""

import logging
from typing import TypedDict

from model.deposit import DepositCalculator
from model.enums import AccrualPeriod
from model.results import DepositEntry
from viewmodel import Signal


# Entry type used in the public API: raw text pairs read from the table by View.
TableRow = tuple[str, str]

# Input range constraints for the deposit form.
AMOUNT_MIN: float = 1.0
AMOUNT_MAX: float = 1_000_000_000.0
MONTHS_MIN: int = 1
MONTHS_MAX: int = 600
RATE_MIN: float = 0.0
RATE_MAX: float = 100.0

# Default values shown when the form first opens.
DEFAULT_AMOUNT: float = 100_000.0
DEFAULT_MONTHS: int = 12
DEFAULT_RATE: float = 8.0
DEFAULT_TAX_RATE: float = 13.0

# Default new-row values for additions/withdrawals tables.
DEFAULT_TABLE_MONTH: str = "1"
DEFAULT_TABLE_AMOUNT: str = "10000"


class DepositViewResult(TypedDict):
    """Merged result dict emitted by DepositViewModel.result_ready signal."""

    total_interest: float
    tax_amount: float
    final_amount: float
    total_interest_text: str  # Formatted display string for total interest.
    tax_amount_text: str  # Formatted display string for tax amount.
    final_amount_text: str  # Formatted display string for final amount.


# Human-readable labels for AccrualPeriod, in enum declaration order.
_PERIOD_LABELS: list[str] = ["Ежемесячно", "Ежеквартально", "Ежегодно"]
# AccrualPeriod values in the same order as _PERIOD_LABELS.
_PERIOD_VALUES: list[AccrualPeriod] = [
    AccrualPeriod.MONTHLY,
    AccrualPeriod.QUARTERLY,
    AccrualPeriod.ANNUALLY,
]

_logger = logging.getLogger("smartcalc")


class DepositViewModel:
    """Provide deposit calculation results to the View via signals.

    Attributes:
        result_ready:    Emitted with a dict containing the results.
        error_occurred:  Emitted with a human-readable error message.
        warning_occurred: Emitted with a human-readable warning (e.g. skipped
            table rows). Empty string means no warning.
    """

    @staticmethod
    def period_labels() -> list[str]:
        """Return display labels for the accrual period combo box."""
        return list(_PERIOD_LABELS)

    @staticmethod
    def default_table_row() -> tuple[str, str]:
        """Return default (month, amount) strings for a new table row."""
        return DEFAULT_TABLE_MONTH, DEFAULT_TABLE_AMOUNT

    def __init__(self, deposit_calculator: DepositCalculator) -> None:
        """Initialize with a DepositCalculator model instance.

        Args:
            deposit_calculator: DepositCalculator model instance.

        """
        self.result_ready: Signal = Signal()
        self.error_occurred: Signal = Signal()
        self.warning_occurred: Signal = Signal()
        self._model = deposit_calculator

    @staticmethod
    def _parse_table_rows(
        rows: list[TableRow], max_month: int
    ) -> tuple[list[DepositEntry], bool]:
        """Parse raw text rows into DepositEntry objects.

        Rows with invalid values or a month exceeding *max_month* are skipped.

        Args:
            rows: Raw (month_text, amount_text) pairs from the View.
            max_month: Deposit term; rows with month > max_month are dropped.

        Returns:
            Tuple of (valid_entries, has_out_of_range).

        """
        entries: list[DepositEntry] = []
        has_out_of_range = False
        for month_text, amount_text in rows:
            try:
                month = int(month_text)
                amount = float(amount_text)
                if month >= 1 and amount > 0:
                    if month > max_month:
                        has_out_of_range = True
                        continue
                    entries.append(DepositEntry(month=month, amount=amount))
            except (ValueError, AttributeError):
                pass
        return entries, has_out_of_range

    def calculate(
        self,
        amount: float,
        months: int,
        annual_rate: float,
        tax_rate: float,
        period_index: int,
        capitalize: bool,
        additions: list[TableRow] | None = None,
        withdrawals: list[TableRow] | None = None,
    ) -> None:
        """Run the deposit calculation and emit results.

        Args:
            amount: Initial deposit amount.
            months: Term in months.
            annual_rate: Annual interest rate in percent.
            tax_rate: Tax on interest income in percent.
            period_index: Index into period_labels() selecting the accrual period.
            capitalize: Whether to reinvest interest.
            additions: Raw (month_text, amount_text) rows from the additions table.
            withdrawals: Raw (month_text, amount_text) rows from the withdrawals table.

        """
        parsed_additions, add_warn = self._parse_table_rows(
            additions or [], months
        )
        parsed_withdrawals, wd_warn = self._parse_table_rows(
            withdrawals or [], months
        )
        has_out_of_range = add_warn or wd_warn
        if has_out_of_range:
            self.warning_occurred.emit(
                f"Некоторые строки пропущены: "
                f"месяц превышает срок вклада ({months} мес.)"
            )
        else:
            self.warning_occurred.emit("")
        try:
            period = _PERIOD_VALUES[period_index]
            result = self._model.calculate(
                amount,
                months,
                annual_rate,
                tax_rate,
                period,
                capitalize,
                parsed_additions or None,
                parsed_withdrawals or None,
            )
            _logger.info(
                "Deposit calculated: amount=%.2f months=%d rate=%.2f period=%s",
                amount,
                months,
                annual_rate,
                period.value,
            )
            view_result = DepositViewResult(
                total_interest=result["total_interest"],
                tax_amount=result["tax_amount"],
                final_amount=result["final_amount"],
                total_interest_text=f"{result['total_interest']:,.2f} ₽",
                tax_amount_text=f"{result['tax_amount']:,.2f} ₽",
                final_amount_text=f"{result['final_amount']:,.2f} ₽",
            )
            self.result_ready.emit(view_result)
        except ValueError as exc:
            _logger.warning("Deposit calculation error: %s", exc)
            self.error_occurred.emit(str(exc))

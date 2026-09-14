"""ViewModel for the loan calculator."""

import logging
from typing import TypedDict

from model.enums import PaymentType
from model.loan import LoanCalculator
from viewmodel import Signal


# Input range constraints for the loan form.
AMOUNT_MIN: float = 1.0
AMOUNT_MAX: float = 1_000_000_000.0
MONTHS_MIN: int = 1
MONTHS_MAX: int = 600
RATE_MIN: float = 0.0
RATE_MAX: float = 100.0

# Default values shown when the form first opens.
DEFAULT_PRINCIPAL: float = 100_000.0
DEFAULT_MONTHS: int = 12
DEFAULT_RATE: float = 12.0

# Human-readable labels for PaymentType, in enum declaration order.
_PAYMENT_TYPE_LABELS: list[str] = ["Аннуитетный", "Дифференцированный"]
# PaymentType values in the same order as _PAYMENT_TYPE_LABELS.
_PAYMENT_TYPE_VALUES: list[PaymentType] = [
    PaymentType.ANNUITY,
    PaymentType.DIFFERENTIATED,
]


class LoanViewResult(TypedDict):
    """Merged result dict emitted by LoanViewModel.result_ready signal.

    Fields absent for a given payment type are set to None.
    Annuity:        monthly_payment is set; first/last/payments are None.
    Differentiated: first_payment/last_payment/payments are set; monthly
                    is None.
    monthly_payment_text is always set — View uses it directly for display.
    """

    monthly_payment: float | None  # Fixed instalment (annuity only).
    first_payment: float | None  # Largest instalment (differentiated only).
    last_payment: float | None  # Smallest instalment (differentiated only).
    overpayment: float  # Total interest paid over the loan term.
    total: float  # Sum of all monthly payments.
    payments: list[float] | None  # Per-month amounts (differentiated only).
    monthly_payment_text: str  # Formatted display string for monthly payment.
    overpayment_text: str  # Formatted display string for overpayment.
    total_text: str  # Formatted display string for total.


_logger = logging.getLogger("smartcalc")


class LoanViewModel:
    """Provide loan calculation results to the View via signals.

    Attributes:
        result_ready: Emitted with a dict containing the calculation results.
        error_occurred: Emitted with a human-readable error message.
    """

    @staticmethod
    def payment_type_labels() -> list[str]:
        """Return display labels for the payment type combo box."""
        return list(_PAYMENT_TYPE_LABELS)

    def __init__(self, loan_calculator: LoanCalculator) -> None:
        """Initialize with a LoanCalculator model instance.

        Args:
            loan_calculator: LoanCalculator model instance.

        """
        self.result_ready: Signal = Signal()
        self.error_occurred: Signal = Signal()
        self._model = loan_calculator

    def calculate(
        self,
        principal: float,
        months: int,
        annual_rate: float,
        payment_type_index: int,
    ) -> None:
        """Run the loan calculation and emit the result.

        Args:
            principal: Total loan amount.
            months: Loan term in months.
            annual_rate: Annual interest rate in percent.
            payment_type_index: Index into payment_type_labels() selecting
                the payment schedule type.

        """
        try:
            payment_type = _PAYMENT_TYPE_VALUES[payment_type_index]
            result: LoanViewResult
            if payment_type == PaymentType.ANNUITY:
                ann = self._model.calculate_annuity(
                    principal, months, annual_rate
                )
                result = LoanViewResult(
                    monthly_payment=ann["monthly_payment"],
                    first_payment=None,
                    last_payment=None,
                    overpayment=ann["overpayment"],
                    total=ann["total"],
                    payments=None,
                    monthly_payment_text=f"{ann['monthly_payment']:,.2f} ₽",
                    overpayment_text=f"{ann['overpayment']:,.2f} ₽",
                    total_text=f"{ann['total']:,.2f} ₽",
                )
            else:
                diff = self._model.calculate_differentiated(
                    principal, months, annual_rate
                )
                first = diff["first_payment"]
                last = diff["last_payment"]
                result = LoanViewResult(
                    monthly_payment=None,
                    first_payment=first,
                    last_payment=last,
                    overpayment=diff["overpayment"],
                    total=diff["total"],
                    payments=diff["payments"],
                    monthly_payment_text=f"{first:,.2f} ₽ → {last:,.2f} ₽",
                    overpayment_text=f"{diff['overpayment']:,.2f} ₽",
                    total_text=f"{diff['total']:,.2f} ₽",
                )
            _logger.info(
                "Loan calculated: principal=%.2f months=%d rate=%.2f type=%s",
                principal,
                months,
                annual_rate,
                payment_type.value,
            )
            self.result_ready.emit(result)
        except (ValueError, IndexError) as exc:
            _logger.warning("Loan calculation error: %s", exc)
            self.error_occurred.emit(str(exc))

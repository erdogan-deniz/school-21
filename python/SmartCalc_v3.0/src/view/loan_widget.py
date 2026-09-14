"""Loan calculator widget: inputs for principal, term, rate, and type."""

from PyQt6.QtWidgets import (
    QComboBox,
    QDoubleSpinBox,
    QFormLayout,
    QGroupBox,
    QLabel,
    QPushButton,
    QSpinBox,
    QVBoxLayout,
    QWidget,
)

from view.base_widget import BaseFinanceWidget
from viewmodel.loan_viewmodel import (
    AMOUNT_MAX,
    AMOUNT_MIN,
    DEFAULT_MONTHS,
    DEFAULT_PRINCIPAL,
    DEFAULT_RATE,
    MONTHS_MAX,
    MONTHS_MIN,
    RATE_MAX,
    RATE_MIN,
    LoanViewModel,
)


class LoanWidget(BaseFinanceWidget):
    """Loan calculator panel with form inputs and result display.

    Delegates all computation to LoanViewModel.
    """

    def __init__(
        self, viewmodel: LoanViewModel, parent: QWidget | None = None
    ) -> None:
        """Create the loan calculator panel.

        Args:
            viewmodel: LoanViewModel instance.
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self._vm = viewmodel
        self._setup_ui()
        self._vm.result_ready.connect(self._show_result)
        self._vm.error_occurred.connect(self._show_error)

    def _setup_ui(self) -> None:
        """Build the widget layout."""
        layout = QVBoxLayout(self)
        layout.addWidget(self._create_form())
        calc_btn = QPushButton("Рассчитать")
        calc_btn.clicked.connect(self._calculate)
        layout.addWidget(calc_btn)
        layout.addWidget(self._create_results())
        layout.addStretch()

    def _create_form(self) -> QGroupBox:
        """Create the loan parameters form group.

        Returns:
            QGroupBox containing all loan input fields.

        """
        form_group = QGroupBox("Параметры кредита")
        form = QFormLayout(form_group)

        self._principal = QDoubleSpinBox()
        self._principal.setRange(AMOUNT_MIN, AMOUNT_MAX)
        self._principal.setValue(DEFAULT_PRINCIPAL)
        self._principal.setSuffix(" ₽")
        form.addRow("Сумма кредита:", self._principal)

        self._months = QSpinBox()
        self._months.setRange(MONTHS_MIN, MONTHS_MAX)
        self._months.setValue(DEFAULT_MONTHS)
        self._months.setSuffix(" мес.")
        form.addRow("Срок:", self._months)

        self._rate = QDoubleSpinBox()
        self._rate.setRange(RATE_MIN, RATE_MAX)
        self._rate.setDecimals(2)
        self._rate.setValue(DEFAULT_RATE)
        self._rate.setSuffix(" % год.")
        form.addRow("Процентная ставка:", self._rate)

        self._type = QComboBox()
        self._type.addItems(LoanViewModel.payment_type_labels())
        form.addRow("Тип:", self._type)

        return form_group

    def _create_results(self) -> QGroupBox:
        """Create the result display group.

        Returns:
            QGroupBox with monthly payment, overpayment, and total labels.

        """
        result_group = QGroupBox("Результат")
        result_layout = QFormLayout(result_group)

        self._monthly_label = QLabel("—")
        result_layout.addRow("Ежемесячный платёж:", self._monthly_label)

        self._overpay_label = QLabel("—")
        result_layout.addRow("Переплата:", self._overpay_label)

        self._total_label = QLabel("—")
        result_layout.addRow("Общая выплата:", self._total_label)

        self._error_label = self._make_error_label()
        result_layout.addRow(self._error_label)

        return result_group

    def _calculate(self) -> None:
        """Read inputs and trigger the ViewModel calculation."""
        self._vm.calculate(
            self._principal.value(),
            self._months.value(),
            self._rate.value(),
            self._type.currentIndex(),
        )

    def _show_result(self, result: dict) -> None:
        """Populate result labels from the ViewModel result dict.

        Args:
            result: LoanViewResult dict containing monthly_payment or
                first_payment/last_payment, overpayment, and total keys.

        """
        self._error_label.setText("")
        self._monthly_label.setText(result["monthly_payment_text"])
        self._overpay_label.setText(result["overpayment_text"])
        self._total_label.setText(result["total_text"])

    def _clear_results(self) -> None:
        """Reset result labels to '—'."""
        self._monthly_label.setText("—")
        self._overpay_label.setText("—")
        self._total_label.setText("—")

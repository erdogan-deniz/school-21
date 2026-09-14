"""Deposit calculator widget."""

from PyQt6.QtWidgets import (
    QCheckBox,
    QComboBox,
    QDoubleSpinBox,
    QFormLayout,
    QGroupBox,
    QHBoxLayout,
    QHeaderView,
    QLabel,
    QPushButton,
    QSpinBox,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from view.base_widget import BaseFinanceWidget
from viewmodel.deposit_viewmodel import (
    AMOUNT_MAX,
    AMOUNT_MIN,
    DEFAULT_AMOUNT,
    DEFAULT_MONTHS,
    DEFAULT_RATE,
    DEFAULT_TAX_RATE,
    MONTHS_MAX,
    MONTHS_MIN,
    RATE_MAX,
    RATE_MIN,
    DepositViewModel,
)


class DepositWidget(BaseFinanceWidget):
    """Deposit calculator panel with form inputs and result display.

    Delegates all computation to DepositViewModel.
    """

    def __init__(
        self, viewmodel: DepositViewModel, parent: QWidget | None = None
    ) -> None:
        """Create the deposit calculator panel.

        Args:
            viewmodel: DepositViewModel instance.
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self._vm = viewmodel
        self._setup_ui()
        self._vm.result_ready.connect(self._show_result)
        self._vm.error_occurred.connect(self._show_error)
        self._vm.warning_occurred.connect(self._show_warning)

    def _setup_ui(self) -> None:
        """Build the widget layout."""
        layout = QVBoxLayout(self)
        layout.addWidget(self._create_form())
        additions_group, withdrawals_group = self._create_tables()
        layout.addWidget(additions_group)
        layout.addWidget(withdrawals_group)
        calc_btn = QPushButton("Рассчитать")
        calc_btn.clicked.connect(self._calculate)
        layout.addWidget(calc_btn)
        layout.addWidget(self._create_results())
        layout.addStretch()

    def _create_form(self) -> QGroupBox:
        """Create the deposit parameters form group.

        Returns:
            QGroupBox containing all deposit input fields.

        """
        form_group = QGroupBox("Параметры депозита")
        form = QFormLayout(form_group)

        self._amount = QDoubleSpinBox()
        self._amount.setRange(AMOUNT_MIN, AMOUNT_MAX)
        self._amount.setValue(DEFAULT_AMOUNT)
        self._amount.setSuffix(" ₽")
        form.addRow("Сумма депозита:", self._amount)

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

        self._tax_rate = QDoubleSpinBox()
        self._tax_rate.setRange(RATE_MIN, RATE_MAX)
        self._tax_rate.setDecimals(2)
        self._tax_rate.setValue(DEFAULT_TAX_RATE)
        self._tax_rate.setSuffix(" %")
        form.addRow("Налоговая ставка:", self._tax_rate)

        self._period = QComboBox()
        self._period.addItems(self._vm.period_labels())
        form.addRow("Периодичность выплат:", self._period)

        self._capitalize = QCheckBox("Капитализация процентов")
        self._capitalize.setChecked(False)
        form.addRow(self._capitalize)

        return form_group

    def _create_tables(self) -> tuple[QGroupBox, QGroupBox]:
        """Create additions and withdrawals table groups.

        Returns:
            Tuple of (additions_group, withdrawals_group) QGroupBoxes.

        """
        self._additions_table = self._make_entry_table()
        self._withdrawals_table = self._make_entry_table()
        return (
            self._make_table_group("Пополнения", self._additions_table),
            self._make_table_group("Снятия", self._withdrawals_table),
        )

    def _create_results(self) -> QGroupBox:
        """Create the result display group.

        Returns:
            QGroupBox with interest, tax, and final amount labels.

        """
        result_group = QGroupBox("Результат")
        result_form = QFormLayout(result_group)

        self._interest_label = QLabel("—")
        result_form.addRow("Начисленные проценты:", self._interest_label)

        self._tax_label = QLabel("—")
        result_form.addRow("Сумма налога:", self._tax_label)

        self._final_label = QLabel("—")
        result_form.addRow("Сумма на вкладе:", self._final_label)

        self._error_label = self._make_error_label()
        result_form.addRow(self._error_label)

        return result_group

    # ------------------------------------------------------------------
    # Helpers for the additions / withdrawals tables
    # ------------------------------------------------------------------

    @staticmethod
    def _make_entry_table() -> QTableWidget:
        """Create a two-column table for month/amount entries.

        Returns:
            QTableWidget with Month and Amount (₽) columns.

        """
        table = QTableWidget(0, 2)
        table.setHorizontalHeaderLabels(["Месяц", "Сумма (₽)"])
        header = table.horizontalHeader()
        if header is not None:
            header.setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        table.setMaximumHeight(110)
        return table

    def _make_table_group(self, title: str, table: QTableWidget) -> QGroupBox:
        """Wrap a table with Add/Remove buttons inside a QGroupBox.

        Args:
            title: Text displayed as the group box title.
            table: The table widget to embed inside the group box.

        Returns:
            QGroupBox containing the table and action buttons.

        """
        group = QGroupBox(title)
        vbox = QVBoxLayout(group)

        btn_row = QHBoxLayout()
        add_btn = QPushButton("+ Добавить")
        add_btn.clicked.connect(lambda: self._add_row(table))
        del_btn = QPushButton("- Удалить")
        del_btn.clicked.connect(lambda: self._remove_row(table))
        btn_row.addWidget(add_btn)
        btn_row.addWidget(del_btn)
        btn_row.addStretch()

        vbox.addLayout(btn_row)
        vbox.addWidget(table)
        return group

    def _add_row(self, table: QTableWidget) -> None:
        """Append a default row to the table."""
        row = table.rowCount()
        table.insertRow(row)
        default_month, default_amount = self._vm.default_table_row()
        table.setItem(row, 0, QTableWidgetItem(default_month))
        table.setItem(row, 1, QTableWidgetItem(default_amount))

    @staticmethod
    def _remove_row(table: QTableWidget) -> None:
        """Remove all currently selected rows from the table."""
        rows = sorted(
            {idx.row() for idx in table.selectedIndexes()}, reverse=True
        )
        for row in rows:
            table.removeRow(row)

    # ------------------------------------------------------------------

    @staticmethod
    def _read_table(table: QTableWidget) -> list[tuple[str, str]]:
        """Read all non-empty rows from a QTableWidget as raw text pairs."""
        rows: list[tuple[str, str]] = []
        for row in range(table.rowCount()):
            item0 = table.item(row, 0)
            item1 = table.item(row, 1)
            if item0 is not None and item1 is not None:
                rows.append((item0.text(), item1.text()))
        return rows

    def _calculate(self) -> None:
        """Read all inputs and trigger the ViewModel calculation."""
        self._vm.calculate(
            self._amount.value(),
            self._months.value(),
            self._rate.value(),
            self._tax_rate.value(),
            self._period.currentIndex(),
            self._capitalize.isChecked(),
            additions=self._read_table(self._additions_table),
            withdrawals=self._read_table(self._withdrawals_table),
        )

    def _show_result(self, result: dict) -> None:
        """Populate result labels from the ViewModel result dict.

        Args:
            result: DepositResult dict with total_interest, tax_amount,
                and final_amount keys.

        """
        self._error_label.setText("")
        self._interest_label.setText(result["total_interest_text"])
        self._tax_label.setText(result["tax_amount_text"])
        self._final_label.setText(result["final_amount_text"])

    def _show_warning(self, message: str) -> None:
        """Display a warning message from the ViewModel.

        Args:
            message: Ready-to-display warning text, or empty string for none.

        """
        self._error_label.setText(message)

    def _clear_results(self) -> None:
        """Reset result labels to '—'."""
        self._interest_label.setText("—")
        self._tax_label.setText("—")
        self._final_label.setText("—")

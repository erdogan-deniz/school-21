"""Base class for finance calculator widgets (Loan, Deposit)."""

from PyQt6.QtWidgets import QLabel, QWidget


class BaseFinanceWidget(QWidget):
    """Provide shared error display logic for LoanWidget and DepositWidget.

    Subclasses must:
    1. Assign ``self._error_label`` during ``_setup_ui()`` using
       ``self._error_label = self._make_error_label()``.
    2. Implement ``_clear_results()`` to reset all result labels to '—'.
    """

    _error_label: QLabel

    @staticmethod
    def _make_error_label() -> QLabel:
        """Create a standard red error label.

        Returns:
            QLabel styled with red text, initially empty.

        """
        label = QLabel("")
        label.setStyleSheet("color: red;")
        return label

    def _show_error(self, message: str) -> None:
        """Display an error message and reset all result labels.

        Args:
            message: Human-readable error message to display.

        """
        self._error_label.setText(message)
        self._clear_results()

    def _clear_results(self) -> None:
        """Reset all result labels to '—'. Implemented by subclasses."""
        raise NotImplementedError(
            f"{type(self).__name__} must implement _clear_results()"
        )

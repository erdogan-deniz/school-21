"""History widget: shows past calculations and allows loading them."""

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QHBoxLayout,
    QLabel,
    QListWidget,
    QListWidgetItem,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from viewmodel import Signal


class HistoryWidget(QWidget):
    """Sidebar panel displaying the list of past expressions.

    Attributes:
        expression_selected: Emitted with the expression string when the
            user double-clicks a history entry.
        clear_requested: Emitted when the user clicks "Очистить".
    """

    def __init__(self, parent: QWidget | None = None) -> None:
        """Create the history panel with a list and control buttons.

        Args:
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self.expression_selected: Signal = Signal()
        self.clear_requested: Signal = Signal()
        layout = QVBoxLayout(self)

        header = QLabel("История")
        header.setStyleSheet("font-weight: bold; font-size: 13px;")
        layout.addWidget(header)

        self._list = QListWidget()
        self._list.setAlternatingRowColors(True)
        self._list.itemDoubleClicked.connect(self._on_item_double_clicked)
        layout.addWidget(self._list)

        btn_row = QHBoxLayout()
        self._clear_btn = QPushButton("Очистить")
        self._clear_btn.clicked.connect(self.clear_requested.emit)
        btn_row.addWidget(self._clear_btn)
        layout.addLayout(btn_row)

    def update_history(self, entries: list[dict]) -> None:
        """Repopulate the list from the given history entries.

        Args:
            entries: List of dicts with 'expression', 'result', 'timestamp'.

        """
        self._list.clear()
        for entry in entries:
            item = QListWidgetItem(entry["display_text"])
            item.setToolTip(entry["timestamp"])
            item.setData(Qt.ItemDataRole.UserRole, entry["expression"])
            self._list.addItem(item)

    def _on_item_double_clicked(self, item: QListWidgetItem) -> None:
        """Emit the stored expression when a row is activated.

        Args:
            item: The list item that was double-clicked.

        """
        expression = item.data(Qt.ItemDataRole.UserRole)
        if expression:
            self.expression_selected.emit(expression)

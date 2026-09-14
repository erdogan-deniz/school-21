"""Calculator widget: expression input, button grid, x-variable, and graph."""

from typing import ClassVar

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QDoubleSpinBox,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QPushButton,
    QSizePolicy,
    QVBoxLayout,
    QWidget,
)

from view.graph_widget import GraphWidget
from viewmodel.calc_viewmodel import CalcViewModel


class CalcWidget(QWidget):
    """Main calculator panel with display, buttons, and embedded graph.

    All user actions delegate to the ViewModel. This widget only
    contains presentation logic (button layout, label updates).
    """

    # Button grid layout: each inner tuple is one row, left-to-right.
    _BUTTONS: ClassVar[list[tuple[str, ...]]] = [
        ("sin(", "cos(", "tan(", "asin(", "acos(", "atan("),
        ("sqrt(", "ln(", "log(", "mod", "(", ")"),
        ("7", "8", "9", "/", "^", "C"),
        ("4", "5", "6", "*", "x", "⌫"),
        ("1", "2", "3", "-", "+", ""),
        ("0", ".", "e", "π", "=", ""),
    ]

    def __init__(
        self, viewmodel: CalcViewModel, parent: QWidget | None = None
    ) -> None:
        """Create the calculator panel and connect it to the ViewModel.

        Args:
            viewmodel: CalcViewModel instance.
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self._vm = viewmodel
        self._setup_ui()
        self._connect_signals()

    def _setup_ui(self) -> None:
        """Build the widget layout."""
        limit = self._vm.graph_y_limit
        main_layout = QHBoxLayout(self)
        main_layout.addLayout(self._create_left_panel(limit), stretch=1)
        main_layout.addLayout(self._create_right_panel(limit), stretch=1)

    def _create_left_panel(self, limit: float) -> QVBoxLayout:
        """Create the calculator display, button grid, and x-variable input.

        Args:
            limit: Absolute bound for the x spinbox range (from config).

        Returns:
            Populated left-side QVBoxLayout.

        """
        left = QVBoxLayout()

        self._display = QLineEdit()
        self._display.setReadOnly(True)
        self._display.setAlignment(Qt.AlignmentFlag.AlignRight)
        self._display.setMinimumHeight(50)
        self._display.setStyleSheet("font-size: 20px;")
        self._display.setMaxLength(self._vm.max_input_length)
        left.addWidget(self._display)

        self._result_label = QLabel("")
        self._result_label.setAlignment(Qt.AlignmentFlag.AlignRight)
        self._result_label.setStyleSheet("font-size: 16px; color: #2a5caa;")
        left.addWidget(self._result_label)

        grid = QGridLayout()
        grid.setSpacing(4)
        for row_idx, row in enumerate(self._BUTTONS):
            for col_idx, label in enumerate(row):
                if not label:
                    continue
                btn = QPushButton(label)
                btn.setSizePolicy(
                    QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding
                )
                btn.setMinimumHeight(40)
                btn.clicked.connect(
                    lambda _checked, t=label: self._on_button_clicked(t)
                )
                if label == "=":
                    btn.setStyleSheet(
                        "background-color: #2a5caa; "
                        "color: white; font-weight: bold;"
                    )
                elif label == "C":
                    btn.setStyleSheet(
                        "background-color: #c0392b; color: white;"
                    )
                grid.addWidget(btn, row_idx, col_idx)
        left.addLayout(grid)

        x_row = QHBoxLayout()
        x_row.addWidget(QLabel("Значение x:"))
        self._x_spin = QDoubleSpinBox()
        self._x_spin.setRange(-limit, limit)
        self._x_spin.setDecimals(self._vm.precision)
        x_row.addWidget(self._x_spin)
        left.addLayout(x_row)

        return left

    def _create_right_panel(self, limit: float) -> QVBoxLayout:
        """Create the graph range controls and plot widget.

        Args:
            limit: Absolute bound for the x/y spinbox ranges (from config).

        Returns:
            Populated right-side QVBoxLayout.

        """
        right = QVBoxLayout()

        range_row = QHBoxLayout()
        range_row.addWidget(QLabel("x от:"))
        self._x_min = QDoubleSpinBox()
        self._x_min.setRange(-limit, limit)
        self._x_min.setValue(-10)
        range_row.addWidget(self._x_min)
        range_row.addWidget(QLabel("до:"))
        self._x_max = QDoubleSpinBox()
        self._x_max.setRange(-limit, limit)
        self._x_max.setValue(10)
        range_row.addWidget(self._x_max)

        y_range_row = QHBoxLayout()
        y_range_row.addWidget(QLabel("y от:"))
        self._y_min = QDoubleSpinBox()
        self._y_min.setRange(-limit, limit)
        self._y_min.setValue(-10)
        y_range_row.addWidget(self._y_min)
        y_range_row.addWidget(QLabel("до:"))
        self._y_max = QDoubleSpinBox()
        self._y_max.setRange(-limit, limit)
        self._y_max.setValue(10)
        y_range_row.addWidget(self._y_max)

        self._plot_btn = QPushButton("Построить график")
        self._plot_btn.clicked.connect(self._on_plot_clicked)

        self._graph = GraphWidget()

        right.addLayout(range_row)
        right.addLayout(y_range_row)
        right.addWidget(self._plot_btn)
        right.addWidget(self._graph)

        return right

    def _connect_signals(self) -> None:
        """Wire ViewModel signals to View update methods."""
        self._vm.display_changed.connect(self._display.setText)
        self._vm.result_changed.connect(self._show_result)
        self._vm.error_occurred.connect(self._show_error)
        self._vm.graph_ready.connect(self._on_graph_ready)
        self._vm.cleared.connect(self._on_cleared)

    def _on_cleared(self) -> None:
        """Reset result label and graph when ViewModel emits cleared."""
        self._result_label.setText("")
        self._graph.clear()

    def _on_button_clicked(self, token: str) -> None:
        """Route button presses to the ViewModel.

        Args:
            token: Button label (e.g. 'sin(', '=', 'π').

        """
        if token == "=":
            self._vm.calculate(self._x_spin.value())
        elif token == "C":
            self._vm.clear()
        elif token == "⌫":
            self._vm.backspace()
        else:
            self._vm.append_token(token)

    def _on_plot_clicked(self) -> None:
        """Trigger graph generation in the ViewModel."""
        self._vm.plot_graph(
            self._x_min.value(),
            self._x_max.value(),
        )

    def _show_result(self, result: str) -> None:
        """Display a successful calculation result.

        Args:
            result: Formatted result string from the ViewModel.

        """
        self._result_label.setStyleSheet("font-size: 16px; color: #2a5caa;")
        self._result_label.setText(f"= {result}")

    def _show_error(self, message: str) -> None:
        """Display an error message in the result label.

        Args:
            message: Ready-to-display error text from the ViewModel.

        """
        self._result_label.setStyleSheet("font-size: 16px; color: #c0392b;")
        self._result_label.setText(message)

    def _on_graph_ready(
        self, segments: list[tuple[list[float], list[float]]]
    ) -> None:
        """Render the graph once segment data is available from the ViewModel.

        Args:
            segments: Continuous (xs, ys) pairs from CalcViewModel.split_segments().

        """
        self._graph.plot(
            segments,
            self._x_min.value(),
            self._x_max.value(),
            self._y_min.value(),
            self._y_max.value(),
        )

    def load_expression(self, expression: str) -> None:
        """Load an expression from history into the display.

        Args:
            expression: Previously evaluated expression string.

        """
        self._vm.load_from_history(expression)

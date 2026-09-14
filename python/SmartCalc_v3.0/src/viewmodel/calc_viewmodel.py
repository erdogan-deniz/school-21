"""ViewModel for the main calculator: bridges Calculator/History and View."""

import logging
import math
from typing import ClassVar

from model.calculator import Calculator
from model.history import History
from viewmodel import Signal


_logger = logging.getLogger("smartcalc")


class CalcViewModel:
    """Manage calculator state and notify the View via signals.

    Attributes:
        display_changed: Emitted with the current expression string.
        result_changed:  Emitted with the formatted result string.
        error_occurred:  Emitted with a human-readable error message.
        history_updated: Emitted with the list of history dicts.
        graph_ready:     Emitted with (xs, ys) lists for the plot.
        cleared:         Emitted (no args) when expression is cleared via
            C button.
    """

    # Maps display symbols (π, e) to numeric strings expected by the C library.
    _TOKEN_MAP: ClassVar[dict[str, str]] = {
        "e": str(math.e),
        "π": str(math.pi),
    }

    def __init__(
        self,
        calculator: Calculator,
        history: History,
        precision: int = 7,
    ) -> None:
        """Initialize the ViewModel with model objects.

        Args:
            calculator: Calculator model instance.
            history: History model instance.
            precision: Number of significant digits for display.

        """
        self.display_changed: Signal = Signal()
        self.result_changed: Signal = Signal()  # emits formatted result str (no prefix)
        self.error_occurred: Signal = Signal()
        self.history_updated: Signal = Signal()
        self.graph_ready: Signal = Signal()
        self.cleared: Signal = Signal()
        self._calc: Calculator = calculator
        self._history: History = history
        self._precision: int = precision
        self._expression: str = ""

    @property
    def graph_y_limit(self) -> float:
        """Y-axis clipping limit for spinbox ranges and graph rendering."""
        return self._calc.GRAPH_Y_LIMIT

    @property
    def max_input_length(self) -> int:
        """Maximum allowed expression length in characters."""
        return self._calc.MAX_INPUT_LENGTH

    @property
    def precision(self) -> int:
        """Number of significant digits used for result display."""
        return self._precision

    def append_token(self, token: str) -> None:
        """Append a character or function name to the expression.

        Display symbols such as 'π' and 'e' are mapped to their numeric
        string equivalents before being appended.

        Args:
            token: Button label or function token (e.g. 'sin(', 'π').

        """
        value = self._TOKEN_MAP.get(token, token)
        if len(self._expression) + len(value) > self._calc.MAX_INPUT_LENGTH:
            self.error_occurred.emit(
                f"Превышен лимит {self._calc.MAX_INPUT_LENGTH} символов"
            )
            return
        self._expression += value
        self.display_changed.emit(self._expression)

    def backspace(self) -> None:
        """Remove the last character from the expression."""
        self._expression = self._expression[:-1]
        self.display_changed.emit(self._expression)

    def clear(self) -> None:
        """Clear the entire expression and notify the View to reset display."""
        self._expression = ""
        self.display_changed.emit(self._expression)
        self.cleared.emit()

    def calculate(self, x_value: float = 0.0) -> None:
        """Evaluate the current expression and emit the result.

        Args:
            x_value: Value to substitute for variable x.

        """
        if not self._expression:
            return
        try:
            result = self._calc.calculate(self._expression, x_value)
            result_str = f"{result:.{self._precision}g}"
            self._history.add_entry(self._expression, result_str)
            _logger.info("Calculated: %s = %s", self._expression, result_str)
            self.result_changed.emit(result_str)
            self.history_updated.emit(self._prepare_history())
        except (ValueError, OverflowError) as exc:
            _logger.warning("Calculation error: %s", exc)
            self.error_occurred.emit(str(exc))

    def plot_graph(
        self,
        x_min: float,
        x_max: float,
        num_points: int = 500,
    ) -> None:
        """Generate graph data for the current expression and emit it.

        Args:
            x_min: Start of the displayed x range.
            x_max: End of the displayed x range.
            num_points: Number of sample points.

        """
        if not self._expression:
            self.error_occurred.emit(
                "Введите выражение для построения графика"
            )
            return
        try:
            xs, ys = self._calc.get_graph_points(
                self._expression, x_min, x_max, num_points
            )
            self.graph_ready.emit(self.split_segments(xs, ys))
        except (ValueError, OverflowError) as exc:
            self.error_occurred.emit(str(exc))

    def load_from_history(self, expression: str) -> None:
        """Load an expression from history into the display.

        Args:
            expression: Previously evaluated expression string.

        """
        self._expression = expression
        self.display_changed.emit(self._expression)

    def clear_history(self) -> None:
        """Delete all history entries and notify the View."""
        self._history.clear_history()
        self.history_updated.emit([])

    def refresh_history(self) -> None:
        """Emit the current history list without modifying it."""
        self.history_updated.emit(self._prepare_history())

    def _prepare_history(self) -> list[dict]:
        """Return history entries enriched with display_text for the View."""
        return [
            {**entry, "display_text": f"{entry['expression']} = {entry['result']}"}
            for entry in self._history.get_history()
        ]

    @staticmethod
    def split_segments(
        xs: list[float], ys: list[float | None]
    ) -> list[tuple[list[float], list[float]]]:
        """Split parallel x/y lists into continuous segments at None gaps.

        Args:
            xs: X-axis sample values.
            ys: Corresponding Y values; None marks a discontinuity.

        Returns:
            List of (seg_x, seg_y) pairs, each a continuous run of points.

        """
        segments: list[tuple[list[float], list[float]]] = []
        seg_x: list[float] = []
        seg_y: list[float] = []
        for x, y in zip(xs, ys, strict=True):
            if y is None:
                if seg_x:
                    segments.append((seg_x, seg_y))
                    seg_x, seg_y = [], []
            else:
                seg_x.append(x)
                seg_y.append(y)
        if seg_x:
            segments.append((seg_x, seg_y))
        return segments

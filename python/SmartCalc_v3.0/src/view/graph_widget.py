"""Graph widget: matplotlib figure embedded in a Qt widget."""

from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg
from matplotlib.figure import Figure
from PyQt6.QtWidgets import QVBoxLayout, QWidget


class GraphWidget(QWidget):
    """Display a function plot using matplotlib inside a PyQt6 widget.

    The axes are drawn with coordinate lines, grid, and adaptive tick
    spacing. Discontinuities (None values in ys) are shown as gaps.
    """

    def __init__(self, parent: QWidget | None = None) -> None:
        """Create the widget with an embedded matplotlib canvas.

        Args:
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self._fig = Figure(figsize=(6, 4), layout="tight")
        self._ax = self._fig.add_subplot(111)
        self._canvas = FigureCanvasQTAgg(  # type: ignore[no-untyped-call]
            self._fig
        )

        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.addWidget(self._canvas)

        self._setup_axes()

    def _setup_axes(self) -> None:
        """Configure default axis appearance."""
        self._ax.set_xlabel("x")
        self._ax.set_ylabel("y")
        self._ax.axhline(0, color="black", linewidth=0.8)
        self._ax.axvline(0, color="black", linewidth=0.8)
        self._ax.grid(True, linestyle="--", alpha=0.5)

    def plot(
        self,
        segments: list[tuple[list[float], list[float]]],
        x_min: float,
        x_max: float,
        y_min: float = -10.0,
        y_max: float = 10.0,
    ) -> None:
        """Draw the function curve from pre-split continuous segments.

        Args:
            segments: List of (xs, ys) pairs, each a continuous run of
                points. Produced by CalcViewModel.split_segments().
            x_min: Left boundary of the display range.
            x_max: Right boundary of the display range.
            y_min: Lower boundary of the Y display range.
            y_max: Upper boundary of the Y display range.

        """
        self._ax.cla()
        self._setup_axes()

        for seg_x, seg_y in segments:
            self._ax.plot(seg_x, seg_y, "b-", linewidth=1.5)

        self._ax.set_xlim(x_min, x_max)
        self._ax.set_ylim(y_min, y_max)
        self._canvas.draw()  # type: ignore[no-untyped-call]

    def clear(self) -> None:
        """Clear the plot area."""
        self._ax.cla()
        self._setup_axes()
        self._canvas.draw()  # type: ignore[no-untyped-call]

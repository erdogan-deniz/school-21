"""Maze solution state manager."""

from PyQt5.QtGui import QColor, QImage

from app.render.maze_grider import MazeGrider
from app.render.render import MazeSolutionRender


class SolveManager:
    """Stores the state and display logic for the maze solution.

    Not a QObject — manages only data and overlay rendering.
    Signals remain on AppController.

    Attributes:
        start: start cell coordinate (row, col) or None.
        end: end cell coordinate (row, col) or None.
        path: current found path or None.
        agent_trained: flag indicating that the Q-agent has been trained.
        grider: grider of the current maze for pixel calculations.
        base_image: base maze image without overlay.
    """

    start: tuple[int, int] | None
    end: tuple[int, int] | None
    path: list[tuple[int, int]] | None
    agent_trained: bool
    grider: MazeGrider | None
    base_image: QImage | None

    def __init__(self) -> None:
        """Initializes all solver state fields to their default values."""
        self.start: tuple[int, int] | None = None
        self.end: tuple[int, int] | None = None
        self.path: list[tuple[int, int]] | None = None
        self.agent_trained: bool = False
        self.grider: MazeGrider | None = None
        self.base_image: QImage | None = None

    def reset(self) -> None:
        """Resets the solver state.

        grider and base_image are NOT affected — they are only updated when
        a new maze is loaded.
        """
        self.start = None
        self.end = None
        self.path = None
        self.agent_trained = False

    def clear(self) -> None:
        """Full reset, including grider and base_image."""
        self.reset()
        self.grider = None
        self.base_image = None

    def can_solve(self) -> bool:
        """Returns True if both start and end are selected."""
        return self.start is not None and self.end is not None

    def get_hint(self) -> tuple[str, bool]:
        """Returns (hint text, solve_button_enabled).

        Returns:
            Tuple (hint, ready) for the solve_ui_updated signal.
        """
        if self.agent_trained and self.end is not None:
            return f"End {self.end} — click any cell to set start", True
        if self.start is None:
            return "Click a cell to set the start", False
        if self.end is None:
            return "Click a cell to set the end", False
        return f"Start {self.start} → End {self.end}", True

    def handle_regular_click(self, cell: tuple[int, int]) -> None:
        """Updates start/end following sequential click logic.

        1st click → start, 2nd → end, 3rd → reset and new start.

        Args:
            cell: coordinate of the clicked cell (row, col).
        """
        if self.start is None:
            self.start = cell
            self.path = None
        elif self.end is None:
            self.end = cell
        else:
            self.start = cell
            self.end = None
            self.path = None

    def pixel_to_cell(self, img_x: int, img_y: int) -> tuple[int, int] | None:
        """Converts pixel coordinates to a (row, col) cell index.

        Args:
            img_x: x pixel coordinate on the canvas.
            img_y: y pixel coordinate on the canvas.

        Returns:
            (row, col) if inside the field bounds, None otherwise.
        """
        if self.grider is None:
            return None
        step_x = self.grider.cell_size.width + self.grider.wall_thickness
        step_y = self.grider.cell_size.height + self.grider.wall_thickness
        col = (img_x - self.grider.start_offset.x) // step_x
        row = (img_y - self.grider.start_offset.y) // step_y
        if not (0 <= row < self.grider.rows and 0 <= col < self.grider.cols):
            return None
        return (row, col)

    def render_overlay(self, path_color: QColor | None = None) -> QImage | None:
        """Draws the path overlay on top of the base image.

        Args:
            path_color: color of the path line; None uses the default color.

        Returns:
            The finished image, or None if base_image/grider is missing.
        """
        if self.base_image is None or self.grider is None:
            return None
        path = self.path or []
        renderer = MazeSolutionRender(
            self.base_image,
            self.grider,
            path,
            start=self.start,
            end=self.end,
            path_color=path_color,
        )
        return renderer.get_image()

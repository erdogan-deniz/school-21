"""Rendering classes for mazes, caves, and solutions based on PyQt5 QImage."""

import logging
from collections.abc import Iterator
from contextlib import contextmanager

from PyQt5.QtCore import Qt
from PyQt5.QtGui import QColor, QImage, QPainter, QPen

from utils.config import (
    CANVAS_HEIGHT,
    CANVAS_WIDTH,
    COLOR_AGENT_PATH,
    COLOR_BACKGROUND,
    COLOR_CAVE_CELL,
    COLOR_END,
    COLOR_PATH,
    COLOR_START,
    COLOR_WALL,
    PATH_THICKNESS,
    SOLVE_MARKER_RADIUS,
)

from .base_grider import BaseGrider, Size
from .cave_grider import CaveGrider
from .maze_grider import MazeGrider

logger: logging.Logger = logging.getLogger(__name__)


class BaseRender:
    """Base renderer: creates a blank QImage and provides a shared
    painter context."""

    grider: BaseGrider
    cell_size: Size
    wall_thickness: int
    img_size: Size
    img_color: QColor
    image: QImage

    def __init__(self, grider: BaseGrider) -> None:
        """Initializes the renderer with grid parameters
        and creates a blank white image.

        Args:
            grider: Grid object with cell size and wall thickness.
        """
        self.grider = grider
        self.cell_size = grider.get_cell_size()
        self.wall_thickness = grider.get_wall_thickness()

        self.img_size = Size(CANVAS_WIDTH, CANVAS_HEIGHT)
        self.img_color = QColor(*COLOR_BACKGROUND)
        self.image = self._create_image(self.img_size, self.img_color)

    def _create_image(self, size: Size, img_color: QColor) -> QImage:
        """Creates a blank QImage of the given size filled with the
        specified color.

        Returns:
            A new QImage in RGB32 format.
        """
        image = QImage(size.width, size.height, QImage.Format_RGB32)
        image.fill(img_color)
        return image

    def get_image(self) -> QImage:
        """Returns the current rendered image."""
        return self.image

    @contextmanager
    def _painter_context(self, setup_pen: bool = False) -> Iterator[QPainter]:
        """Context manager for working with QPainter."""
        painter = QPainter(self.image)

        if setup_pen and hasattr(self, "pen"):
            painter.setPen(self.pen)

        try:
            yield painter
        finally:
            painter.end()


class MazeRender(BaseRender):
    """Maze renderer: draws vertical and horizontal walls."""

    vertical_walls: list[tuple[int, int]]
    horizontal_walls: list[tuple[int, int]]
    pen_color: QColor
    pen_width: int
    pen: QPen

    def __init__(self, grider: MazeGrider) -> None:
        """Renders the maze by drawing walls from MazeGrider coordinate lists.

        Args:
            grider: Maze grid object with wall lists.
        """
        if not isinstance(grider, MazeGrider):
            raise TypeError(f"Expected MazeGrider, got {type(grider)}")

        super().__init__(grider)

        self.vertical_walls = grider.get_vertical_walls()
        self.horizontal_walls = grider.get_horizontal_walls()

        self.pen_color = QColor(*COLOR_WALL)
        self.pen_width = self.wall_thickness
        self.pen = QPen(self.pen_color)
        self.pen.setWidth(self.pen_width)

        with self._painter_context(setup_pen=True) as painter:
            self._draw_maze(painter)

    def _draw_maze(self, painter: QPainter) -> None:
        """Draws lines from wall start points."""
        length_y = self.cell_size.height + self.wall_thickness
        for x, y in self.vertical_walls:
            painter.drawLine(x, y, x, y - length_y)

        length_x = self.cell_size.width + self.wall_thickness
        for x, y in self.horizontal_walls:
            painter.drawLine(x, y, x - length_x, y)


class MazeSolutionRender:
    """
    Overlays a path and start/end markers onto a finished maze image.
    Does not modify the original — works on a copy.
    """

    image: QImage

    PATH_COLOR = QColor(*COLOR_PATH)
    AGENT_COLOR = QColor(*COLOR_AGENT_PATH)
    START_COLOR = QColor(*COLOR_START)
    END_COLOR = QColor(*COLOR_END)
    MARKER_RADIUS = SOLVE_MARKER_RADIUS

    def __init__(
        self,
        base_image: QImage,
        grider: MazeGrider,
        path: list[tuple[int, int]],
        start: tuple[int, int] | None = None,
        end: tuple[int, int] | None = None,
        path_color: QColor | None = None,
    ) -> None:
        """Takes a finished maze image and overlays
        the route and start/end markers onto a copy of it.

        Args:
            base_image: Source maze image (not modified).
            grider: Maze grid object for computing cell centres.
            path: List of route cells as [(row, col), ...].
            start: Start cell (row, col) or None.
            end: End cell (row, col) or None.
            path_color: Color of the route line; if None,
                PATH_COLOR is used.
        """
        self.image = base_image.copy()
        color = path_color if path_color is not None else self.PATH_COLOR
        painter = QPainter(self.image)
        try:
            self._draw_path_line(painter, grider, path, color)
            if start:
                self._draw_marker(painter, grider, start, self.START_COLOR)
            if end:
                self._draw_marker(painter, grider, end, self.END_COLOR)
        finally:
            painter.end()

    def get_image(self) -> QImage:
        """Returns the maze image with the path overlay applied."""
        return self.image

    def _cell_center(
        self, grider: MazeGrider, row: int, col: int
    ) -> tuple[int, int]:
        """Returns the pixel coordinates of the cell centre."""
        step_x = grider.cell_size.width + grider.wall_thickness
        step_y = grider.cell_size.height + grider.wall_thickness
        x = (
            grider.start_offset.x
            + grider.wall_thickness
            + col * step_x
            + grider.cell_size.width // 2
        )
        y = (
            grider.start_offset.y
            + grider.wall_thickness
            + row * step_y
            + grider.cell_size.height // 2
        )
        return x, y

    def _draw_path_line(
        self,
        painter: QPainter,
        grider: MazeGrider,
        path: list[tuple[int, int]],
        color: QColor,
    ) -> None:
        """Draws the route as a 2px-wide line through cell centres."""
        if len(path) < 2:
            return
        pen = QPen(color)
        pen.setWidth(PATH_THICKNESS)
        painter.setPen(pen)
        centers = [self._cell_center(grider, r, c) for r, c in path]
        for i in range(len(centers) - 1):
            x1, y1 = centers[i]
            x2, y2 = centers[i + 1]
            painter.drawLine(x1, y1, x2, y2)

    def _draw_marker(
        self,
        painter: QPainter,
        grider: MazeGrider,
        cell: tuple[int, int],
        color: QColor,
    ) -> None:
        """Draws a circular marker at the centre of the cell."""
        x, y = self._cell_center(grider, cell[0], cell[1])
        r = self.MARKER_RADIUS
        painter.setPen(Qt.NoPen)
        painter.setBrush(color)
        painter.drawEllipse(x - r, y - r, r * 2, r * 2)


class CaveRender(BaseRender):
    """Cave renderer: fills live cells (True) with black."""

    filled_cell: list[tuple[int, int]]

    def __init__(self, grider: CaveGrider) -> None:
        """Renders the cave by filling live cells from CaveGrider.

        Args:
            grider: Cave grid object with the list of cells to fill.
        """
        if not isinstance(grider, CaveGrider):
            raise TypeError(f"Expected CaveGrider, got {type(grider)}")

        super().__init__(grider)

        self.filled_cell = grider.get_filled_cell()

        with self._painter_context(setup_pen=False) as painter:
            self._draw_cave(painter)

    def _draw_cave(self, painter: QPainter) -> None:
        """Draws the cave."""
        width = self.cell_size.width
        height = self.cell_size.height

        for x, y in self.filled_cell:
            painter.fillRect(x, y, width, height, QColor(*COLOR_CAVE_CELL))

        x0 = self.grider.start_offset.x
        y0 = self.grider.start_offset.y
        pen = QPen(QColor(*COLOR_WALL))
        pen.setWidth(1)
        painter.setPen(pen)
        painter.setBrush(Qt.NoBrush)
        painter.drawRect(
            x0, y0, self.grider.cols * width - 1, self.grider.rows * height - 1
        )

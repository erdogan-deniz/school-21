"""Base types and grid calculation class for field rendering."""

from typing import NamedTuple

from models.field import FieldModel
from utils.config import CANVAS_HEIGHT, CANVAS_WIDTH


class Point(NamedTuple):
    """A point with x and y coordinates."""

    x: int
    y: int

    def __add__(self, other: "Point") -> "Point":  # type: ignore[override]
        """Returns a new point as the component-wise sum of two points."""
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other: "Point") -> "Point":
        """Returns a new point as the component-wise difference of
        two points."""
        return Point(self.x - other.x, self.y - other.y)


class Size(NamedTuple):
    """A region with width and height."""

    width: int
    height: int


class BaseGrider:
    """
    Base class for calculating coordinates for grid rendering.
    Supports mazes, caves, and other two-dimensional cell-based fields.
    """

    _wall_thickness: int  # must be set by subclass

    size: Size
    rows: int
    cols: int
    wall_thickness: int
    cell_size: Size
    start_offset: Point

    def __init__(self, field: FieldModel) -> None:
        """Initializes the canvas size (canvas_size), field rows and columns,
        wall thickness, cell size, and offsets for centering the grid.

        Args:
            field: Field model from which rows and cols are taken.
        """
        self.size = Size(CANVAS_WIDTH, CANVAS_HEIGHT)

        self.rows = field.rows
        self.cols = field.cols

        self.wall_thickness = self._wall_thickness

        self.cell_size = self.get_cell_size_px()
        self.start_offset = self.get_start_offset()

    def get_wall_thickness(self) -> int:
        """Returns the wall thickness in pixels."""
        return self.wall_thickness

    def _axes_cell_size_px(self, max_pixels: int, n_cells: int) -> int:
        """
        Calculates the cell size in pixels (excluding walls)
        along one dimension.

        Args:
            max_pixels: Maximum size along one axis (width or height)
            n_cells: Number of cells along this axis

        Returns:
            cell_size: cell size in pixels
        """
        total_walls_space = self.wall_thickness * (n_cells + 1)
        available_cell_space = max_pixels - total_walls_space
        cell_size = available_cell_space // n_cells
        return cell_size

    def get_cell_size_px(self) -> Size:
        """Calculates and returns the cell size in pixels
        accounting for wall thickness."""
        width = self._axes_cell_size_px(self.size.width, self.cols)
        height = self._axes_cell_size_px(self.size.height, self.rows)
        return Size(width, height)

    def _get_offsets_px(self, max_pixels: int, n_cells: int) -> tuple[int, int]:
        """
        Calculates offsets for centering the field.
        This is a generic method that calculates the offset along one dimension.

        Args:
            max_pixels: Maximum size along one axis (width or height)
            n_cells: Number of cells along this axis

        Returns:
            (offset_start, offset_end)
            offset_start: leading offset (left/top)
            offset_end: trailing offset (right/bottom)
        """
        cell_size = self._axes_cell_size_px(max_pixels, n_cells)
        total_walls_space = self.wall_thickness * (n_cells + 1)
        remaining_space = max_pixels - total_walls_space - cell_size * n_cells
        offset_start = remaining_space // 2
        offset_end = remaining_space - offset_start

        return offset_start, offset_end

    def get_start_offset(self) -> Point:
        """Calculates the top-left offset for centering the field."""
        start_x, _ = self._get_offsets_px(self.size.width, self.cols)
        start_y, _ = self._get_offsets_px(self.size.height, self.rows)
        return Point(start_x, start_y)

    def get_cell_size(self) -> Size:
        """Returns the pre-calculated cell size."""
        return self.cell_size

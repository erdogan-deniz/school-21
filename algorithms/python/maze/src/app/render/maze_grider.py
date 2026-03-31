"""Calculation of maze wall coordinates for subsequent rendering."""

from models.field import MazeFieldModel
from utils.config import WALL_THICKNESS

from .base_grider import BaseGrider


class MazeGrider(BaseGrider):
    """Class for calculating wall coordinates for maze rendering.

    Converts Maze wall matrices into coordinate lists for the renderer.
    """

    _wall_thickness: int = WALL_THICKNESS

    vertical_walls: list[tuple[int, int]]
    horizontal_walls: list[tuple[int, int]]

    def __init__(self, maze: MazeFieldModel) -> None:
        """Builds the lists of vertical and horizontal wall
        coordinates for the maze.

        Args:
            maze: Maze field model with vertical_walls
                and horizontal_walls matrices.
        """
        if not isinstance(maze, MazeFieldModel):
            raise TypeError(f"Expected MazeFieldModel, got {type(maze)}")

        super().__init__(maze)

        self.vertical_walls = self._calc_vertical_walls(maze.vertical_walls)
        self.horizontal_walls = self._calc_horizontal_walls(
            maze.horizontal_walls
        )

    def _get_walls_matrix(
        self, pattern_matrix: list[list[int]]
    ) -> list[tuple[int, int]]:
        """The result list contains start-point coordinates
        from which walls should be drawn (downward for vertical walls
        or rightward for horizontal walls)."""
        x_step = self.cell_size.width + self.wall_thickness
        y_step = self.cell_size.height + self.wall_thickness
        y = self.start_offset.y + y_step
        result = []
        for row in pattern_matrix:
            x = self.start_offset.x + x_step
            for col in row:
                if col:
                    result.append((x, y))
                x += x_step
            y += y_step
        return result

    def _calc_vertical_walls(
        self, pattern_matrix: list[list[int]]
    ) -> list[tuple[int, int]]:
        """Calculates (x, y) start-point coordinates of vertical walls,
        including the outer left border and inner walls."""
        result = []

        # Left wall (outer border)
        x0 = self.start_offset.x
        y_step = self.cell_size.height + self.wall_thickness
        y_start = self.start_offset.y

        for i in range(1, self.rows + 1):
            y = y_start + i * y_step
            if 0 <= y <= self.size.height:
                result.append((x0, y))

        # From the vertical wall matrix of the maze
        result += self._get_walls_matrix(pattern_matrix)
        return result

    def _calc_horizontal_walls(
        self, pattern_matrix: list[list[int]]
    ) -> list[tuple[int, int]]:
        """Calculates (x, y) start-point coordinates of horizontal walls,
        including the outer top border and inner walls."""
        result = []

        # Top wall (outer border)
        y0 = self.start_offset.y
        x_step = self.cell_size.width + self.wall_thickness
        x_start = self.start_offset.x

        for i in range(1, self.cols + 1):
            x = x_start + i * x_step
            if 0 <= x <= self.size.width:
                result.append((x, y0))

        # From the horizontal wall matrix of the maze
        result += self._get_walls_matrix(pattern_matrix)

        return result

    def get_vertical_walls(self) -> list[tuple[int, int]]:
        """Returns the list of start-point coordinates of vertical walls."""
        return self.vertical_walls

    def get_horizontal_walls(self) -> list[tuple[int, int]]:
        """Returns the list of start-point coordinates of horizontal walls."""
        return self.horizontal_walls

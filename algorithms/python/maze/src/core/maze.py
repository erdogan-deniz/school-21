"""Module describing the thin-wall maze structure."""

from core.base_field import BaseField


class Maze(BaseField):
    """A maze with thin walls.

    Stores two binary fields: right (vertical)
    and bottom (horizontal) walls.
    1 indicates a wall is present, 0 indicates a passage.

    Attributes:
        rights: right wall matrix
            (rights[i][j] == 1 → wall to the right of cell (i, j)).
        bottoms: bottom wall matrix
            (bottoms[i][j] == 1 → wall below cell (i, j)).
    """

    rights: list[list[int]]
    bottoms: list[list[int]]

    def __init__(
        self,
        rows: int = 0,
        cols: int = 0,
        rights: list[list[int]] | None = None,
        bottoms: list[list[int]] | None = None,
    ) -> None:
        """Creates a maze of the given size.

        Args:
            rows: Number of rows.
            cols: Number of columns.
            rights: Vertical wall matrix (1 = wall, 0 = passage), or None
                to initialise with an empty (all-None) matrix.
            bottoms: Horizontal wall matrix, same format as ``rights``.

        Raises:
            ValueError: If dimensions are out of range or the matrices contain
                values other than 0 and 1.
        """
        super().__init__(rows, cols)

        self.rights = self._init_field(rights)
        self.bottoms = self._init_field(bottoms)

    def __repr__(self) -> str:
        """Returns a detailed string representation of the maze
        for debugging."""
        return (
            f"Maze(rows={self.rows}, cols={self.cols}, "
            f"rights={self.rights}, bottoms={self.bottoms})"
        )

    def visualize(self) -> str:
        """Returns a text map of the maze using ``+``, ``-``,
        and ``|`` characters.

        Returns ``'Empty maze'`` for a 0×0 field.
        """
        if self.rows == 0 or self.cols == 0:
            return "Empty maze"

        result = []

        # Top border
        top_line = "+"
        for _j in range(self.cols):
            top_line += "---+"  # All top walls are always present (border)
        result.append(top_line)

        for i in range(self.rows):
            # Cells and right walls
            cell_line = "|"
            for j in range(self.cols):
                cell_line += "   "  # Cell interior (empty)
                if j == self.cols - 1:
                    cell_line += "|"  # Right border of the maze
                else:
                    cell_line += " " if not self.rights[i][j] else "|"
            result.append(cell_line)

            # Bottom walls (except the last row)
            if i == self.rows - 1:
                bottom_line = "+"
                for _j in range(self.cols):
                    bottom_line += "---+"  # Bottom border of the maze
            else:
                bottom_line = "+"
                for j in range(self.cols):
                    bottom_line += "   " if not self.bottoms[i][j] else "---"
                    bottom_line += "+"
            result.append(bottom_line)

        return "\n".join(result)

    def get_vertical_walls(self) -> list[list[int]]:
        """Returns a copy of the right wall matrix (1 = wall, 0 = passage)."""
        return [row[:] for row in self.rights]

    def get_horizontal_walls(self) -> list[list[int]]:
        """Returns a copy of the bottom wall matrix (1 = wall, 0 = passage)."""
        return [row[:] for row in self.bottoms]

    def set_vertical_walls(self, walls: list[list[int]]) -> None:
        """Sets the vertical wall matrix."""
        if len(walls) != self.rows:
            raise ValueError(f"Vertical walls must have {self.rows} rows")
        for i, row in enumerate(walls):
            if len(row) != self.cols:
                raise ValueError(f"Row {i} must have {self.cols} columns")
        self.rights = [row[:] for row in walls]

    def set_horizontal_walls(self, walls: list[list[int]]) -> None:
        """Sets the horizontal wall matrix."""
        if len(walls) != self.rows:
            raise ValueError(f"Horizontal walls must have {self.rows} rows")
        for i, row in enumerate(walls):
            if len(row) != self.cols:
                raise ValueError(f"Row {i} must have {self.cols} columns")
        self.bottoms = [row[:] for row in walls]

    def get_neighbors(self, row: int, col: int) -> list[tuple[int, int]]:
        """Returns cells reachable from (row, col) with no wall between them.

        Args:
            row: cell row.
            col: cell column.

        Returns:
            List of neighbouring cells (row, col) that can be moved to.
        """
        neighbors: list[tuple[int, int]] = []
        if col < self.cols - 1 and not self.rights[row][col]:
            neighbors.append((row, col + 1))
        if col > 0 and not self.rights[row][col - 1]:
            neighbors.append((row, col - 1))
        if row < self.rows - 1 and not self.bottoms[row][col]:
            neighbors.append((row + 1, col))
        if row > 0 and not self.bottoms[row - 1][col]:
            neighbors.append((row - 1, col))
        return neighbors

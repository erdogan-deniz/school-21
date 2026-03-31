"""Calculation of pixel coordinates for filled cave cells used in rendering."""

from models.field import CaveFieldModel

from .base_grider import BaseGrider


class CaveGrider(BaseGrider):
    """Class for calculating cave cell coordinates.

    Contains the pixel coordinates (left and top) of each cell to be filled.
    """

    _wall_thickness: int = 0

    filled_cells: list[tuple[int, int]]

    def __init__(self, cave: CaveFieldModel) -> None:
        """Builds the list of pixel coordinates of cave cells
        that need to be filled.

        Args:
            cave: Cave field model with a matrix of live/dead cells.
        """
        if not isinstance(cave, CaveFieldModel):
            raise TypeError(f"Expected CaveFieldModel, got {type(cave)}")

        super().__init__(cave)

        self.filled_cells = self._calc_filled_cells(cave.cells)

    def _calc_filled_cells(
        self, cells: list[list[int]]
    ) -> list[tuple[int, int]]:
        """Calculates the pixel coordinates (left and top)
        of cells that should be filled (True)."""
        x0 = self.start_offset.x
        y0 = self.start_offset.y
        x_step = self.cell_size.width
        y_step = self.cell_size.height
        result = []
        for i, row in enumerate(cells):
            for j, cell in enumerate(row):
                if cell:
                    x = x0 + j * x_step
                    y = y0 + i * y_step
                    result.append((x, y))
        return result

    def get_filled_cell(self) -> list[tuple[int, int]]:
        """Returns the list of pixel coordinates (x, y) of filled cells."""
        return self.filled_cells

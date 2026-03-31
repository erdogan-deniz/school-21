"""Generation of a perfect maze using Eller's algorithm."""

import logging
import random
from abc import ABC, abstractmethod
from copy import copy

from core.maze import Maze
from utils.config import MAX_COLS, MAX_ROWS

logger: logging.Logger = logging.getLogger(__name__)


class MazeGenerator(ABC):
    """Base class for maze generators."""

    @abstractmethod
    def generate(self, rows: int, cols: int) -> Maze:
        """Generates a maze of the given size.

        Args:
            rows: Number of rows.
            cols: Number of columns.

        Returns:
            The generated maze.
        """
        raise NotImplementedError  # pragma: no cover


class MazeGeneratorImpl(MazeGenerator):
    """Maze generator using Eller's algorithm.

    The algorithm builds the maze row by row, assigning cells to sets
    and placing right and bottom walls with a given probability.

    Attributes:
        RIGHT_WALL_PROBABILITY: Probability of placing a right wall
            between cells from different sets.
        BOTTOM_WALL_PROBABILITY: Probability of placing a bottom wall
            if doing so would not seal off a set.
    """

    GEN_BOTTOM_PROBABILITY = 0.4
    GEN_RIGHT_PROBABILITY = 0.4

    def generate(self, rows: int, cols: int) -> Maze:
        """Generates a maze of the given size.

        Args:
            rows: Number of rows (from 1 to 50 inclusive).
            cols: Number of columns (from 1 to 50 inclusive).

        Returns:
            The generated maze.

        Raises:
            ValueError: If rows or cols are outside the range [1, 50].
        """
        self._validate_dimensions(rows, cols)
        self._initialize_state(rows, cols)

        for row in range(self._rows - 1):
            self._build_right_walls(row)
            self._build_bottom_walls(row)
            self._prepare_next_row(row)

        self._finalize_last_row()

        logger.info("Maze %dx%d successfully generated", rows, cols)

        return Maze(
            rows=self._rows,
            cols=self._cols,
            rights=self._right_walls,
            bottoms=self._bottom_walls,
        )

    @staticmethod
    def _validate_dimensions(rows: int, cols: int) -> None:
        """Validates the maze dimensions.

        Args:
            rows: Number of rows.
            cols: Number of columns.

        Raises:
            ValueError: If rows or cols are outside the range [1, 50].
        """
        errors: list[str] = []
        if rows < 1:
            errors.append(f"number of rows must be >= 1 ({rows} < 1)")
        elif rows > MAX_ROWS:
            errors.append(
                f"number of rows must be <= {MAX_ROWS} ({rows} > {MAX_ROWS})"
            )
        if cols < 1:
            errors.append(f"number of columns must be >= 1 ({cols} < 1)")
        elif cols > MAX_COLS:
            errors.append(
                f"number of columns must be <= {MAX_COLS} ({cols} > {MAX_COLS})"
            )

        if errors:
            raise ValueError(f"Invalid dimensions: {', '.join(errors)}")

    @staticmethod
    def _random_wall(probability: float) -> bool:
        """Randomly decides whether to place a wall.

        Args:
            probability: Probability of placing a wall (0.0 to 1.0).

        Returns:
            True if a wall should be placed.
        """
        return random.random() < probability

    def _initialize_state(self, rows: int, cols: int) -> None:
        """Initializes the internal state of the generator.

        Args:
            rows: Number of rows.
            cols: Number of columns.
        """
        self._rows: int = rows
        self._cols: int = cols

        # Initialize the right and bottom boundaries
        self._next_set_id: int = cols
        self._cell_sets: list[list[int]] = [list(range(self._next_set_id))]

        self._right_walls: list[list[int]] = [
            [0] * cols for _ in range(rows - 1)
        ]
        self._bottom_walls: list[list[int]] = [
            [0] * cols for _ in range(rows - 1)
        ]

    def _build_right_walls(self, row: int) -> None:
        """Places right walls for the given row.

        Cells from the same set are always separated by a wall
        (to avoid cycles). Cells from different sets are separated
        with probability RIGHT_WALL_PROBABILITY;
        if no wall is placed the sets are merged.

        Args:
            row: Row index.
        """
        walls = self._right_walls[row]

        for col in range(self._cols - 1):
            if self._random_wall(self.GEN_RIGHT_PROBABILITY) or (
                self._cell_sets[row][col] == self._cell_sets[row][col + 1]
            ):
                walls[col] = 1
            else:
                self._merge_sets(row, col)

        walls[-1] = 1  # Right border of the maze

    def _build_bottom_walls(self, row: int) -> None:
        """Places bottom walls for the given row.

        A wall is placed with probability BOTTOM_WALL_PROBABILITY
        only if doing so would not fully seal off a set.

        Args:
            row: Row index.
        """
        walls = self._bottom_walls[row]

        for col in range(self._cols):
            if self._random_wall(
                self.GEN_BOTTOM_PROBABILITY
            ) and self._can_place_bottom_wall(row, col):
                walls[col] = 1

    def _prepare_next_row(self, row: int) -> None:
        """Creates sets for the next row.

        Cells with a bottom wall receive a new unique set identifier;
        the rest inherit the set of the current row.

        Args:
            row: Current row index.
        """
        next_sets = copy(self._cell_sets[-1])

        for col in range(self._cols):
            if self._bottom_walls[row][col]:
                next_sets[col] = self._next_set_id
                self._next_set_id += 1

        self._cell_sets.append(next_sets)

    def _finalize_last_row(self) -> None:
        """Processes the last row of the maze.

        All adjacent cells from different sets are merged
        (wall is removed). Cells from the same set remain separated.
        The bottom border is a solid wall.
        """
        last = len(self._cell_sets) - 1

        walls: list[int]
        if self._rows > 1:
            walls = copy(self._right_walls[last - 1])
        else:
            walls = [0] * (self._cols - 1) + [1]

        for col in range(self._cols - 1):
            if self._cell_sets[last][col] != self._cell_sets[last][col + 1]:
                walls[col] = 0
                self._merge_sets(last, col)
            elif self._cell_sets[last][col] == self._cell_sets[last][col + 1]:
                walls[col] = 1

        walls[self._cols - 1] = 1  # Right border
        self._right_walls.append(walls)
        self._bottom_walls.append([1] * self._cols)  # Bottom border

    def _merge_sets(self, row: int, col: int) -> None:
        """Merges the set of cell ``col + 1`` into the set of cell ``col``.

        All cells in the row belonging to the right cell's set
        receive the left cell's set identifier.

        Args:
            row: Row index.
            col: Index of the left cell in the pair.
        """
        current_row = self._cell_sets[row]
        old_set = current_row[col + 1]
        new_set = current_row[col]

        for i in range(self._cols):
            if current_row[i] == old_set:
                current_row[i] = new_set

    def _can_place_bottom_wall(self, row: int, col: int) -> bool:
        """Checks whether a bottom wall can be placed without sealing a set.

        A wall cannot be placed if all other cells of the set in the
        current row already have a bottom wall (otherwise the set would
        not carry over to the next row).

        Args:
            row: Row index.
            col: Column index.

        Returns:
            True if the bottom wall can be safely placed.
        """
        current_row = self._cell_sets[row]
        bottom_walls = self._bottom_walls[row]
        target_set = current_row[col]

        set_size = 0
        walled_count = 0

        for i in range(self._cols):
            if current_row[i] == target_set:
                set_size += 1
                if bottom_walls[i]:
                    walled_count += 1

        return walled_count < set_size - 1

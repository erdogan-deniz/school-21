"""Field model DTOs that carry data between core, controller, and render
layers."""

from abc import ABC
from dataclasses import dataclass, field

from core.cave import Cave
from core.maze import Maze
from utils.config import (
    DEFAULT_BIRTH_LIMIT,
    DEFAULT_DEATH_LIMIT,
    DEFAULT_INIT_CHANCE,
)


@dataclass
class FieldModel(ABC):
    """
    Abstract base field model for rendering.
    DTO (Data Transfer Object) for passing data between layers:
    - core (business logic) → controller → render
    """

    rows: int
    cols: int


@dataclass
class MazeFieldModel(FieldModel):
    """
    Field model for mazes.
    Contains matrices of vertical and horizontal walls.
    """

    vertical_walls: list[list[int]] = field(default_factory=list)
    horizontal_walls: list[list[int]] = field(default_factory=list)

    @classmethod
    def from_maze(cls, maze: Maze) -> "MazeFieldModel":
        """Creates from the maze business model."""
        return cls(
            rows=maze.get_rows(),
            cols=maze.get_cols(),
            vertical_walls=maze.get_vertical_walls(),
            horizontal_walls=maze.get_horizontal_walls(),
        )

    def get_maze(self) -> Maze:
        """
        Recreates the core maze model from the FieldModel.
        Required for business logic (maze solving, generation).
        """
        from core.maze import Maze

        maze = Maze(self.rows, self.cols)
        maze.set_vertical_walls(self.vertical_walls)
        maze.set_horizontal_walls(self.horizontal_walls)
        return maze


@dataclass
class CaveFieldModel(FieldModel):
    """
    Field model for caves.
    Contains a cell matrix (1/0 for alive/dead cells).
    """

    cells: list[list[int]] = field(default_factory=list)
    init_chance: int = DEFAULT_INIT_CHANCE
    birth_limit: int = DEFAULT_BIRTH_LIMIT
    death_limit: int = DEFAULT_DEATH_LIMIT

    @classmethod
    def from_cave(cls, cave: Cave) -> "CaveFieldModel":
        """Creates from the cave business model."""
        return cls(
            rows=cave.get_rows(),
            cols=cave.get_cols(),
            cells=cave.get_field(),
            init_chance=cave.get_init_chance(),
            birth_limit=cave.get_birth_limit(),
            death_limit=cave.get_death_limit(),
        )

    def get_cave(self) -> Cave:
        """
        Recreates the core cave model from the FieldModel.
        Required for business logic (next generation, auto-play mode).
        """
        from core.cave import Cave

        cave = Cave(
            rows=self.rows,
            cols=self.cols,
            field_mtx=self.cells,
            init_chance=self.init_chance,
            birth_limit=self.birth_limit,
            death_limit=self.death_limit,
        )
        return cave

    def is_empty(self) -> bool:
        """Returns True when the field has no live cells
        (all dead or no rows)."""
        return not any(cell for row in self.cells for cell in row)

    def is_final_generation(self) -> bool:
        """
        Checks whether the final generation has been reached.
        """
        cave = self.get_cave()
        return cave.is_final_generation()

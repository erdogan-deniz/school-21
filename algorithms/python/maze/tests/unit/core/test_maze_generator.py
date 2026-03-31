"""Tests for MazeGeneratorImpl — Eller's algorithm output validation."""

# python3 -m pytest tests/test_maze_generator.py -v

import random

import pytest

from core.maze import Maze
from core.maze_generator import MazeGeneratorImpl
from core.maze_solver import MazeSolver


@pytest.fixture
def gen() -> MazeGeneratorImpl:
    """Default MazeGeneratorImpl instance."""
    return MazeGeneratorImpl()


# ---------------------------------------------------------------------------
# Helper function: counts open passages (0 entries in the wall matrix)
# ---------------------------------------------------------------------------


def _count_passages(maze: Maze) -> int:
    """Counts the number of open (wall=0) passages in both wall matrices."""
    rights = maze.get_vertical_walls()
    bottoms = maze.get_horizontal_walls()
    rows, cols = maze.get_rows(), maze.get_cols()

    count = 0
    for i in range(rows):
        for j in range(cols - 1):  # last column is the boundary
            if not rights[i][j]:
                count += 1
    for i in range(rows - 1):  # last row is the boundary
        for j in range(cols):
            if not bottoms[i][j]:
                count += 1
    return count


# ---------------------------------------------------------------------------
# Dimension validation
# ---------------------------------------------------------------------------


def test_invalid_rows_zero(gen: MazeGeneratorImpl) -> None:
    """generate(0, n) raises ValueError."""
    with pytest.raises(ValueError):
        gen.generate(0, 5)


def test_invalid_cols_zero(gen: MazeGeneratorImpl) -> None:
    """generate(n, 0) raises ValueError."""
    with pytest.raises(ValueError):
        gen.generate(5, 0)


def test_invalid_rows_too_large(gen: MazeGeneratorImpl) -> None:
    """generate(51, n) raises ValueError (exceeds MAX_ROWS)."""
    with pytest.raises(ValueError):
        gen.generate(51, 5)


def test_invalid_cols_too_large(gen: MazeGeneratorImpl) -> None:
    """generate(n, 51) raises ValueError (exceeds MAX_COLS)."""
    with pytest.raises(ValueError):
        gen.generate(5, 51)


def test_negative_dimensions(gen: MazeGeneratorImpl) -> None:
    """generate(-1, n) raises ValueError."""
    with pytest.raises(ValueError):
        gen.generate(-1, 5)


# ---------------------------------------------------------------------------
# Dimensions and structure of the generated maze
# ---------------------------------------------------------------------------


def test_output_dimensions(gen: MazeGeneratorImpl) -> None:
    """Generated maze has exactly the requested number of rows and columns."""
    maze = gen.generate(7, 9)
    assert maze.get_rows() == 7
    assert maze.get_cols() == 9


def test_wall_matrix_sizes(gen: MazeGeneratorImpl) -> None:
    """Both wall matrices have the correct shape (rows × cols)."""
    maze = gen.generate(4, 6)
    rights = maze.get_vertical_walls()
    bottoms = maze.get_horizontal_walls()
    assert len(rights) == 4
    assert all(len(row) == 6 for row in rights)
    assert len(bottoms) == 4
    assert all(len(row) == 6 for row in bottoms)


# ---------------------------------------------------------------------------
# Boundary walls: the rightmost column and bottom row are always closed
# ---------------------------------------------------------------------------


def test_right_boundary_walls(gen: MazeGeneratorImpl) -> None:
    """The last column of the right-wall matrix is always 1 (boundary wall)."""
    maze = gen.generate(5, 5)
    rights = maze.get_vertical_walls()
    for i in range(maze.get_rows()):
        assert rights[i][-1] == 1, f"Missing right boundary in row {i}"


def test_bottom_boundary_walls(gen: MazeGeneratorImpl) -> None:
    """The last row of the bottom-wall matrix is always 1 (boundary wall)."""
    maze = gen.generate(5, 5)
    bottoms = maze.get_horizontal_walls()
    for j in range(maze.get_cols()):
        assert bottoms[-1][j] == 1, f"Missing bottom boundary in column {j}"


def test_wall_values_are_binary(gen: MazeGeneratorImpl) -> None:
    """All wall matrix values are 0 or 1."""
    maze = gen.generate(6, 6)
    for row in maze.get_vertical_walls():
        assert all(v in (0, 1) for v in row)
    for row in maze.get_horizontal_walls():
        assert all(v in (0, 1) for v in row)


# ---------------------------------------------------------------------------
# Perfect maze properties
# ---------------------------------------------------------------------------


def test_perfect_maze_passage_count(gen: MazeGeneratorImpl) -> None:
    """A perfect maze is a spanning tree: exactly rows*cols-1 passages."""
    rows, cols = 6, 8
    maze = gen.generate(rows, cols)
    assert _count_passages(maze) == rows * cols - 1


def test_fully_connected(gen: MazeGeneratorImpl) -> None:
    """Every cell is reachable from every other cell."""
    rows, cols = 5, 5
    maze = gen.generate(rows, cols)
    solver = MazeSolver(maze)
    for r in range(rows):
        for c in range(cols):
            path = solver.solve((0, 0), (r, c))
            assert path is not None, f"No path from (0,0) to ({r},{c})"


# ---------------------------------------------------------------------------
# Edge cases
# ---------------------------------------------------------------------------


def test_1x1_maze(gen: MazeGeneratorImpl) -> None:
    """A 1×1 maze has only boundary walls (rights=[[1]], bottoms=[[1]])."""
    maze = gen.generate(1, 1)
    assert maze.get_rows() == 1
    assert maze.get_cols() == 1
    assert maze.get_vertical_walls() == [[1]]
    assert maze.get_horizontal_walls() == [[1]]


def test_1xn_maze(gen: MazeGeneratorImpl) -> None:
    """A 1×10 maze is a single corridor with exactly 9 passages."""
    maze = gen.generate(1, 10)
    assert _count_passages(maze) == 9
    solver = MazeSolver(maze)
    for c in range(10):
        assert solver.solve((0, 0), (0, c)) is not None


def test_nx1_maze(gen: MazeGeneratorImpl) -> None:
    """A 10×1 maze is a single vertical corridor with exactly 9 passages."""
    maze = gen.generate(10, 1)
    assert _count_passages(maze) == 9
    solver = MazeSolver(maze)
    for r in range(10):
        assert solver.solve((0, 0), (r, 0)) is not None


def test_max_size(gen: MazeGeneratorImpl) -> None:
    """50×50 maze is generated and is a perfect maze."""
    maze = gen.generate(50, 50)
    assert maze.get_rows() == 50
    assert maze.get_cols() == 50
    assert _count_passages(maze) == 50 * 50 - 1


# ---------------------------------------------------------------------------
# Determinism
# ---------------------------------------------------------------------------


def test_deterministic_with_seed(gen: MazeGeneratorImpl) -> None:
    """With the same seed, the generated maze is identical."""
    random.seed(42)
    maze1 = gen.generate(5, 5)

    random.seed(42)
    maze2 = gen.generate(5, 5)

    assert maze1.get_vertical_walls() == maze2.get_vertical_walls()
    assert maze1.get_horizontal_walls() == maze2.get_horizontal_walls()

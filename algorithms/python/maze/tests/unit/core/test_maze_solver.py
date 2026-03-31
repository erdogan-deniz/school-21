# python3 -m pytest tests/test_maze_solver.py -v
"""Tests for MazeSolver — BFS shortest-path finder."""

from core.maze import Maze
from core.maze_solver import MazeSolver
from handlers.file_handler import MazeFileHandler
from utils.paths import ProjectPaths

# ---------------------------------------------------------------------------
# Helper function: verifies that a path is valid (no step passes through a wall)
# ---------------------------------------------------------------------------


def _is_valid_path(maze: Maze, path: list[tuple[int, int]]) -> bool:
    """Returns True if every step in path moves one cell and crosses no wall."""
    rights = maze.rights
    bottoms = maze.bottoms
    for i in range(len(path) - 1):
        r0, c0 = path[i]
        r1, c1 = path[i + 1]
        # each step must move exactly one cell along one axis
        if abs(r0 - r1) + abs(c0 - c1) != 1:
            return False
        # right
        if c1 == c0 + 1 and rights[r0][c0]:
            return False
        # left
        if c1 == c0 - 1 and rights[r0][c1]:
            return False
        # down
        if r1 == r0 + 1 and bottoms[r0][c0]:
            return False
        # up
        if r1 == r0 - 1 and bottoms[r1][c0]:
            return False
    return True


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------


def test_same_start_end() -> None:
    """Start == end → path consisting of a single cell."""
    maze = Maze(3, 3, rights=[[0, 0, 0]] * 3, bottoms=[[0, 0, 0]] * 3)
    solver = MazeSolver(maze)
    assert solver.solve((1, 1), (1, 1)) == [(1, 1)]


def test_straight_corridor() -> None:
    """Horizontal corridor with no walls."""
    maze = Maze(1, 4, rights=[[0, 0, 0, 0]], bottoms=[[0, 0, 0, 0]])
    solver = MazeSolver(maze)
    path = solver.solve((0, 0), (0, 3))
    assert path == [(0, 0), (0, 1), (0, 2), (0, 3)]


def test_vertical_corridor() -> None:
    """Vertical corridor with no walls."""
    maze = Maze(4, 1, rights=[[0], [0], [0], [0]], bottoms=[[0], [0], [0], [0]])
    solver = MazeSolver(maze)
    path = solver.solve((0, 0), (3, 0))
    assert path == [(0, 0), (1, 0), (2, 0), (3, 0)]


def test_no_path_blocked_by_wall() -> None:
    """A wall completely blocks the only path → None."""
    # 1×2 maze, wall between (0,0) and (0,1)
    maze = Maze(1, 2, rights=[[1, 0]], bottoms=[[0, 0]])
    solver = MazeSolver(maze)
    assert solver.solve((0, 0), (0, 1)) is None


def test_path_forced_detour() -> None:
    """The direct path is blocked — BFS finds a detour."""
    # 2×3: wall to the right of (0,1) and below (0,1)
    # only path: (0,0)→(1,0)→(1,1)→(1,2)→(0,2)
    rights = [[0, 1, 0], [0, 0, 0]]
    bottoms = [[0, 1, 0], [0, 0, 0]]
    maze = Maze(2, 3, rights=rights, bottoms=bottoms)
    solver = MazeSolver(maze)

    path = solver.solve((0, 0), (0, 2))

    assert path is not None
    assert path[0] == (0, 0)
    assert path[-1] == (0, 2)
    assert path == [(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)]
    assert _is_valid_path(maze, path)


def test_shortest_path() -> None:
    """BFS returns the shortest path, not just any path."""
    # Open 3×3: a diagonal path requires 3 cells (2 moves),
    # not 4 (a longer detour).
    rights = [[0, 0, 0]] * 3
    bottoms = [[0, 0, 0]] * 3
    maze = Maze(3, 3, rights=rights, bottoms=bottoms)
    solver = MazeSolver(maze)

    path = solver.solve((0, 0), (1, 1))

    assert path is not None
    assert len(path) == 3  # (0,0) → one neighbour → (1,1): 2 moves = 3 cells
    assert path[0] == (0, 0)
    assert path[-1] == (1, 1)
    assert _is_valid_path(maze, path)


def test_path_valid_no_wall_crossed() -> None:
    """The path does not pass through any wall."""
    rights = [[0, 1, 0], [0, 0, 0], [0, 0, 0]]
    bottoms = [[0, 0, 1], [1, 0, 0], [0, 0, 0]]
    maze = Maze(3, 3, rights=rights, bottoms=bottoms)
    solver = MazeSolver(maze)

    path = solver.solve((0, 0), (2, 2))

    assert path is not None
    assert path[0] == (0, 0)
    assert path[-1] == (2, 2)
    assert _is_valid_path(maze, path)


def test_solve_from_file() -> None:
    """Load 4x4.txt and verify connectivity —
    all cells are reachable from (0,0)."""
    paths = ProjectPaths()
    filepath = str(paths.get_maze_data_dir() / "4x4.txt")
    maze = MazeFileHandler.read_from_file(filepath)
    solver = MazeSolver(maze)

    rows, cols = maze.get_rows(), maze.get_cols()
    for r in range(rows):
        for c in range(cols):
            path = solver.solve((0, 0), (r, c))
            assert path is not None, f"No path from (0,0) to ({r},{c})"
            assert path[0] == (0, 0)
            assert path[-1] == (r, c)
            assert _is_valid_path(maze, path), (
                f"Path to ({r},{c}) passes through a wall"
            )

"""Integration tests for MazeFileHandler and CaveFileHandler —
read, save, and roundtrip."""

# python3 -m pytest tests/test_file_handler.py -v

from pathlib import Path

import pytest

from core.cave import Cave
from core.maze import Maze
from handlers.file_handler import CaveFileHandler, MazeFileHandler
from utils.config import DEFAULT_BIRTH_LIMIT, DEFAULT_DEATH_LIMIT
from utils.paths import ProjectPaths

MAZE_4X4 = str(ProjectPaths().get_maze_data_dir() / "4x4.txt")
CAVE_4X4 = str(ProjectPaths().get_cave_data_dir() / "4x4.txt")


# ===========================================================================
# MazeFileHandler — reading
# ===========================================================================


def test_maze_read_returns_maze() -> None:
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    assert isinstance(maze, Maze)


def test_maze_read_dimensions() -> None:
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    assert maze.get_rows() == 4
    assert maze.get_cols() == 4


def test_maze_read_wall_matrix_sizes() -> None:
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    rights = maze.get_vertical_walls()
    bottoms = maze.get_horizontal_walls()
    assert len(rights) == 4 and all(len(r) == 4 for r in rights)
    assert len(bottoms) == 4 and all(len(r) == 4 for r in bottoms)


def test_maze_read_correct_walls() -> None:
    """Checks the first row of the right-wall matrix from 4x4.txt."""
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    assert maze.get_vertical_walls()[0] == [0, 0, 0, 1]
    assert maze.get_horizontal_walls()[0] == [1, 0, 1, 0]


def test_maze_file_not_found() -> None:
    with pytest.raises(FileNotFoundError):
        MazeFileHandler.read_from_file("nonexistent/path/maze.txt")


# ===========================================================================
# MazeFileHandler — saving and roundtrip
# ===========================================================================


def test_maze_save_creates_file(tmp_path: Path) -> None:
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    out = str(tmp_path / "maze_out.txt")
    MazeFileHandler.save_to_file(maze, out)
    import os

    assert os.path.exists(out)


def test_maze_roundtrip(tmp_path: Path) -> None:
    """Save → load → data matches."""
    original = MazeFileHandler.read_from_file(MAZE_4X4)
    out = str(tmp_path / "maze_rt.txt")
    MazeFileHandler.save_to_file(original, out)

    reloaded = MazeFileHandler.read_from_file(out)

    assert reloaded.get_rows() == original.get_rows()
    assert reloaded.get_cols() == original.get_cols()
    assert reloaded.get_vertical_walls() == original.get_vertical_walls()
    assert reloaded.get_horizontal_walls() == original.get_horizontal_walls()


def test_maze_save_creates_nested_dirs(tmp_path: Path) -> None:
    maze = MazeFileHandler.read_from_file(MAZE_4X4)
    out = str(tmp_path / "a" / "b" / "c" / "maze.txt")
    MazeFileHandler.save_to_file(maze, out)
    import os

    assert os.path.exists(out)


def test_maze_roundtrip_large(tmp_path: Path) -> None:
    """Roundtrip for a 10×10 file."""
    src = str(ProjectPaths().get_maze_data_dir() / "example_1.txt")
    original = MazeFileHandler.read_from_file(src)
    out = str(tmp_path / "maze10.txt")
    MazeFileHandler.save_to_file(original, out)
    reloaded = MazeFileHandler.read_from_file(out)

    assert reloaded.get_vertical_walls() == original.get_vertical_walls()
    assert reloaded.get_horizontal_walls() == original.get_horizontal_walls()


# ===========================================================================
# CaveFileHandler — reading
# ===========================================================================


def test_cave_read_returns_cave() -> None:
    cave = CaveFileHandler.read_from_file(CAVE_4X4)
    assert isinstance(cave, Cave)


def test_cave_read_dimensions() -> None:
    cave = CaveFileHandler.read_from_file(CAVE_4X4)
    assert cave.get_rows() == 4
    assert cave.get_cols() == 4


def test_cave_read_correct_field() -> None:
    """Checks the first row of the field from 4x4.txt."""
    cave = CaveFileHandler.read_from_file(CAVE_4X4)
    assert cave.get_field()[0] == [0, 1, 0, 1]


def test_cave_read_default_limits() -> None:
    cave = CaveFileHandler.read_from_file(CAVE_4X4)
    assert cave.get_birth_limit() == DEFAULT_BIRTH_LIMIT
    assert cave.get_death_limit() == DEFAULT_DEATH_LIMIT


def test_cave_file_not_found() -> None:
    with pytest.raises(FileNotFoundError):
        CaveFileHandler.read_from_file("nonexistent/path/cave.txt")


# ===========================================================================
# CaveFileHandler — saving and roundtrip
# ===========================================================================


def test_cave_save_creates_file(tmp_path: Path) -> None:
    cave = CaveFileHandler.read_from_file(CAVE_4X4)
    out = str(tmp_path / "cave_out.txt")
    CaveFileHandler.save_to_file(cave, out)
    import os

    assert os.path.exists(out)


def test_cave_roundtrip(tmp_path: Path) -> None:
    """Save → load → data matches."""
    original = CaveFileHandler.read_from_file(CAVE_4X4)
    out = str(tmp_path / "cave_rt.txt")
    CaveFileHandler.save_to_file(original, out)

    reloaded = CaveFileHandler.read_from_file(out)

    assert reloaded.get_rows() == original.get_rows()
    assert reloaded.get_cols() == original.get_cols()
    assert reloaded.get_field() == original.get_field()


# ===========================================================================
# Invalid content
# ===========================================================================


def test_bad_content_raises_error(tmp_path: Path) -> None:
    bad_file = tmp_path / "bad.txt"
    bad_file.write_text("4 4\nnot numbers here\n")
    with pytest.raises(ValueError):
        MazeFileHandler.read_from_file(str(bad_file))


def test_maze_empty_file_raises_value_error(tmp_path: Path) -> None:
    """Empty file must raise ValueError, not IndexError."""
    empty = tmp_path / "empty.txt"
    empty.write_text("   \n\n   ")
    with pytest.raises(ValueError):
        MazeFileHandler.read_from_file(str(empty))


def test_maze_single_number_header_raises_value_error(tmp_path: Path) -> None:
    """Header with one number instead of two must raise ValueError."""
    bad = tmp_path / "bad_header.txt"
    bad.write_text("10\n0 1\n1 0\n")
    with pytest.raises(ValueError):
        MazeFileHandler.read_from_file(str(bad))


def test_cave_empty_file_raises_value_error(tmp_path: Path) -> None:
    """Empty cave file must raise ValueError, not IndexError."""
    empty = tmp_path / "empty.txt"
    empty.write_text("\n\n")
    with pytest.raises(ValueError):
        CaveFileHandler.read_from_file(str(empty))


def test_cave_single_number_header_raises_value_error(tmp_path: Path) -> None:
    """Cave file with single-number header must raise ValueError."""
    bad = tmp_path / "bad_header.txt"
    bad.write_text("4\n0 1 0 1\n")
    with pytest.raises(ValueError):
        CaveFileHandler.read_from_file(str(bad))

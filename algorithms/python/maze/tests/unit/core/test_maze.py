"""Tests for Maze — wall matrices, visualize, get/set walls,
and BaseField validation."""

# python3 -m pytest tests/test_maze.py -v

import pytest

from core.maze import Maze
from utils.config import MAX_ROWS


@pytest.fixture
def corridor() -> Maze:
    """Horizontal corridor 1×3 with no internal vertical walls."""
    return Maze(rows=1, cols=3, rights=[[0, 0, 1]], bottoms=[[1, 1, 1]])


@pytest.fixture
def maze2x2() -> Maze:
    """2×2 maze with mixed wall configuration for general testing."""
    return Maze(
        rows=2, cols=2, rights=[[0, 1], [0, 1]], bottoms=[[0, 0], [1, 1]]
    )


# ---------------------------------------------------------------------------
# __repr__
# ---------------------------------------------------------------------------


class TestRepr:
    """Tests for Maze.__repr__."""

    def test_repr_contains_dimensions(self, maze2x2: Maze) -> None:
        """__repr__ includes rows and cols values."""
        r = repr(maze2x2)
        assert "rows=2" in r
        assert "cols=2" in r

    def test_repr_contains_walls(self, maze2x2: Maze) -> None:
        """__repr__ includes rights and bottoms wall matrices."""
        r = repr(maze2x2)
        assert "rights=" in r
        assert "bottoms=" in r


# ---------------------------------------------------------------------------
# visualize
# ---------------------------------------------------------------------------


class TestVisualize:
    """Tests for Maze.visualize — ASCII text representation."""

    def test_empty_maze_returns_stub(self) -> None:
        """visualize returns 'Empty maze' for a 0×0 maze."""
        m = Maze(rows=0, cols=0)
        assert m.visualize() == "Empty maze"

    def test_visualize_1x1_has_borders(self) -> None:
        """1×1 maze visualize output contains border characters."""
        m = Maze(rows=1, cols=1, rights=[[1]], bottoms=[[1]])
        result = m.visualize()
        assert "+---+" in result
        assert "|" in result

    def test_visualize_1x3_shows_corridor(self, corridor: Maze) -> None:
        """1×3 corridor shows the top border and open passages between cells."""
        result = corridor.visualize()
        # Top border is present
        assert "+---+---+---+" in result
        # No vertical walls between cells (rights=0 → ' ')
        assert "    " in result  # empty space with no wall

    def test_visualize_has_top_border(self, maze2x2: Maze) -> None:
        """First line of visualize output starts with '+'."""
        lines = maze2x2.visualize().split("\n")
        assert lines[0].startswith("+")

    def test_visualize_has_bottom_border(self, maze2x2: Maze) -> None:
        """Last line of visualize output starts with '+' and contains '---'."""
        lines = maze2x2.visualize().split("\n")
        assert lines[-1].startswith("+")
        assert "---" in lines[-1]

    def test_visualize_2x2_wall_present(self) -> None:
        """A rights[i][j]=1 entry produces a '|' separator in the cell row."""
        # rights[0][0]=1 → vertical wall between (0,0) and (0,1)
        m = Maze(
            rows=2, cols=2, rights=[[1, 1], [1, 1]], bottoms=[[1, 1], [1, 1]]
        )
        result = m.visualize()
        # Internal vertical walls are represented by '|'
        lines = result.split("\n")
        cell_line = lines[1]  # first row of cells
        assert "|" in cell_line

    def test_visualize_2x2_bottom_wall_present(self) -> None:
        """A bottoms[i][j]=1 entry produces '---' in the separator row."""
        # bottoms[0][0]=1 → horizontal wall below (0,0)
        m = Maze(
            rows=2, cols=2, rights=[[1, 1], [1, 1]], bottoms=[[1, 1], [1, 1]]
        )
        result = m.visualize()
        lines = result.split("\n")
        # The row between cell rows should contain '---'
        assert "---" in lines[2]

    def test_visualize_2x2_no_bottom_wall(self) -> None:
        """A bottoms[i][j]=0 entry produces spaces in the separator row."""
        # bottoms[0][0]=0 → no horizontal wall
        m = Maze(
            rows=2, cols=2, rights=[[0, 1], [0, 1]], bottoms=[[0, 0], [1, 1]]
        )
        result = m.visualize()
        lines = result.split("\n")
        # Row between cell rows is just '+   +' (no '---')
        assert "   " in lines[2]

    def test_visualize_returns_string(self, maze2x2: Maze) -> None:
        """visualize always returns a str."""
        assert isinstance(maze2x2.visualize(), str)


# ---------------------------------------------------------------------------
# set_vertical_walls / set_horizontal_walls
# ---------------------------------------------------------------------------


class TestSetWalls:
    """Tests for Maze.set_vertical_walls and set_horizontal_walls."""

    def test_set_vertical_walls(self, maze2x2: Maze) -> None:
        """set_vertical_walls updates rights to the provided matrix."""
        maze2x2.set_vertical_walls([[1, 1], [1, 1]])
        assert maze2x2.rights == [[1, 1], [1, 1]]

    def test_set_horizontal_walls(self, maze2x2: Maze) -> None:
        """set_horizontal_walls updates bottoms to the provided matrix."""
        maze2x2.set_horizontal_walls([[1, 1], [1, 1]])
        assert maze2x2.bottoms == [[1, 1], [1, 1]]

    def test_set_vertical_walls_is_copy(self, maze2x2: Maze) -> None:
        """set_vertical_walls stores a copy — mutating the source
        does not affect the maze."""
        new_walls = [[1, 1], [1, 1]]
        maze2x2.set_vertical_walls(new_walls)
        new_walls[0][0] = 0
        assert maze2x2.rights[0][0] == 1

    def test_set_horizontal_walls_is_copy(self, maze2x2: Maze) -> None:
        """set_horizontal_walls stores a copy — mutating the source
        does not affect the maze."""
        new_walls = [[1, 1], [1, 1]]
        maze2x2.set_horizontal_walls(new_walls)
        new_walls[0][0] = 0
        assert maze2x2.bottoms[0][0] == 1

    def test_set_vertical_walls_wrong_row_count_raises(
        self, maze2x2: Maze
    ) -> None:
        """Passing a matrix with the wrong number of rows raises ValueError."""
        with pytest.raises(ValueError, match="rows"):
            maze2x2.set_vertical_walls([[1, 1]])  # 1 row instead of 2

    def test_set_vertical_walls_wrong_col_count_raises(
        self, maze2x2: Maze
    ) -> None:
        """Passing a row with the wrong column count raises ValueError."""
        with pytest.raises(ValueError, match="columns"):
            maze2x2.set_vertical_walls(
                [[1, 1, 1], [1, 1]]
            )  # 3 columns in the first row

    def test_set_horizontal_walls_wrong_row_count_raises(
        self, maze2x2: Maze
    ) -> None:
        """Passing a matrix with the wrong number of rows raises ValueError."""
        with pytest.raises(ValueError, match="rows"):
            maze2x2.set_horizontal_walls([[1, 1]])  # 1 row instead of 2

    def test_set_horizontal_walls_wrong_col_count_raises(
        self, maze2x2: Maze
    ) -> None:
        """Passing a row with the wrong column count raises ValueError."""
        with pytest.raises(ValueError, match="columns"):
            maze2x2.set_horizontal_walls(
                [[1, 1, 1], [1, 1]]
            )  # 3 columns in the first row


# ---------------------------------------------------------------------------
# BaseField: dimension validation on construction
# ---------------------------------------------------------------------------


class TestBaseFieldDimensions:
    """Tests for BaseField dimension validation (via Maze construction)."""

    def test_too_large_rows_raises_on_creation(self) -> None:
        """Constructing a maze with rows > MAX_ROWS raises ValueError."""
        with pytest.raises(ValueError):
            Maze(rows=MAX_ROWS + 1, cols=1)

    def test_negative_rows_raises_on_creation(self) -> None:
        """Constructing a maze with negative rows raises ValueError."""
        with pytest.raises(ValueError):
            Maze(rows=-1, cols=1)


# ---------------------------------------------------------------------------
# BaseField: _init_field — matrix validation
# ---------------------------------------------------------------------------


class TestInitField:
    """Tests for BaseField._init_field matrix shape and value validation."""

    def test_wrong_row_count_raises(self) -> None:
        """Passing a matrix with more rows than declared raises ValueError."""
        # Passing a matrix with 3 rows instead of the expected 2
        with pytest.raises(ValueError, match="rows"):
            Maze(
                rows=2,
                cols=2,
                rights=[[0, 1], [0, 1], [0, 1]],
                bottoms=[[0, 0], [1, 1]],
            )

    def test_wrong_col_count_raises(self) -> None:
        """Passing a row with more columns than declared raises ValueError."""
        # First row has 3 columns instead of 2
        with pytest.raises(ValueError, match="columns"):
            Maze(
                rows=2,
                cols=2,
                rights=[[0, 1, 0], [0, 1]],
                bottoms=[[0, 0], [1, 1]],
            )

    def test_invalid_value_in_matrix_raises(self) -> None:
        """A value other than 0 or 1 in the matrix raises ValueError."""
        # Value 2 is not allowed (only 0 and 1)
        with pytest.raises(ValueError, match="invalid value"):
            Maze(
                rows=2,
                cols=2,
                rights=[[0, 2], [0, 1]],
                bottoms=[[0, 0], [1, 1]],
            )

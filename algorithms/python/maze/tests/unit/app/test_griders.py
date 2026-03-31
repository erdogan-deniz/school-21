"""Tests for BaseGrider, MazeGrider, and CaveGrider — pure maths, no Qt."""

import pytest

from app.render.base_grider import Point, Size
from app.render.cave_grider import CaveGrider
from app.render.maze_grider import MazeGrider
from models.field import CaveFieldModel, MazeFieldModel
from utils.config import CANVAS_HEIGHT, CANVAS_WIDTH, WALL_THICKNESS

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def cave_model() -> CaveFieldModel:
    """3×3 CaveFieldModel with a checkerboard of live/dead cells."""
    cells = [
        [True, False, True],
        [False, True, False],
        [True, True, False],
    ]
    return CaveFieldModel(rows=3, cols=3, cells=cells)


@pytest.fixture
def maze_grider(maze_model: MazeFieldModel) -> MazeGrider:
    """MazeGrider built from the shared 4×4 maze_model fixture."""
    return MazeGrider(maze_model)


@pytest.fixture
def cave_grider(cave_model: CaveFieldModel) -> CaveGrider:
    """CaveGrider built from the 3×3 cave_model fixture."""
    return CaveGrider(cave_model)


# ---------------------------------------------------------------------------
# Point / Size NamedTuple
# ---------------------------------------------------------------------------


class TestPointSize:
    """Tests for the Point and Size NamedTuple helpers."""

    def test_point_add(self) -> None:
        assert Point(1, 2) + Point(3, 4) == Point(4, 6)

    def test_point_sub(self) -> None:
        assert Point(5, 7) - Point(2, 3) == Point(3, 4)

    def test_size_fields(self) -> None:
        s = Size(10, 20)
        assert s.width == 10 and s.height == 20


# ---------------------------------------------------------------------------
# BaseGrider (via MazeGrider)
# ---------------------------------------------------------------------------


class TestBaseGrider:
    """Tests for BaseGrider — cell-size computation and canvas bounds."""

    def test_cell_size_positive(self, maze_grider: MazeGrider) -> None:
        cs = maze_grider.get_cell_size()
        assert cs.width > 0 and cs.height > 0

    def test_cell_size_fits_canvas(self, maze_grider: MazeGrider) -> None:
        cs = maze_grider.get_cell_size()
        wt = maze_grider.get_wall_thickness()
        rows, cols = maze_grider.rows, maze_grider.cols
        # All cells + walls must fit within the canvas
        total_w = cols * cs.width + (cols + 1) * wt
        total_h = rows * cs.height + (rows + 1) * wt
        assert total_w <= CANVAS_WIDTH
        assert total_h <= CANVAS_HEIGHT

    def test_wall_thickness(self, maze_grider: MazeGrider) -> None:
        assert maze_grider.get_wall_thickness() == WALL_THICKNESS

    def test_start_offset_non_negative(self, maze_grider: MazeGrider) -> None:
        off = maze_grider.start_offset
        assert off.x >= 0 and off.y >= 0

    def test_get_cell_size_equals_stored(self, maze_grider: MazeGrider) -> None:
        assert maze_grider.get_cell_size() == maze_grider.cell_size

    def test_wrong_type_raises(self, cave_model: CaveFieldModel) -> None:
        with pytest.raises(TypeError):
            MazeGrider(cave_model)


# ---------------------------------------------------------------------------
# MazeGrider
# ---------------------------------------------------------------------------


class TestMazeGrider:
    """Tests for MazeGrider — wall coordinate lists."""

    def test_vertical_walls_not_empty(self, maze_grider: MazeGrider) -> None:
        # 4×4 maze with some walls=1 → list is not empty
        assert len(maze_grider.get_vertical_walls()) > 0

    def test_horizontal_walls_not_empty(self, maze_grider: MazeGrider) -> None:
        assert len(maze_grider.get_horizontal_walls()) > 0

    def test_wall_coords_within_canvas(self, maze_grider: MazeGrider) -> None:
        for x, y in maze_grider.get_vertical_walls():
            assert 0 <= x <= CANVAS_WIDTH
            assert 0 <= y <= CANVAS_HEIGHT

    def test_no_walls_gives_only_border(self) -> None:
        model = MazeFieldModel(
            rows=2,
            cols=2,
            vertical_walls=[[0, 0], [0, 0]],
            horizontal_walls=[[0, 0], [0, 0]],
        )
        g = MazeGrider(model)
        # Only the outer borders (rows left + cols top)
        assert len(g.get_vertical_walls()) == 2
        assert len(g.get_horizontal_walls()) == 2


# ---------------------------------------------------------------------------
# CaveGrider
# ---------------------------------------------------------------------------


class TestCaveGrider:
    """Tests for CaveGrider — filled-cell coordinate list."""

    def test_filled_count_matches_live_cells(
        self, cave_grider: CaveGrider, cave_model: CaveFieldModel
    ) -> None:
        live = sum(cell for row in cave_model.cells for cell in row)
        assert len(cave_grider.get_filled_cell()) == live

    def test_filled_coords_within_canvas(self, cave_grider: CaveGrider) -> None:
        cs = cave_grider.get_cell_size()
        for x, y in cave_grider.get_filled_cell():
            assert 0 <= x <= CANVAS_WIDTH - cs.width
            assert 0 <= y <= CANVAS_HEIGHT - cs.height

    def test_empty_cave_no_filled(self) -> None:
        model = CaveFieldModel(
            rows=3, cols=3, cells=[[False] * 3 for _ in range(3)]
        )
        g = CaveGrider(model)
        assert g.get_filled_cell() == []

    def test_wrong_type_raises(self, maze_model: MazeFieldModel) -> None:
        with pytest.raises(TypeError):
            CaveGrider(maze_model)

    def test_wall_thickness_is_zero(self, cave_grider: CaveGrider) -> None:
        assert cave_grider.get_wall_thickness() == 0

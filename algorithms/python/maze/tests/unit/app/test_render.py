"""Tests for MazeRender, CaveRender, and MazeSolutionRender
(requires QApplication)."""

import pytest
from PyQt5.QtGui import QColor, QImage
from PyQt5.QtWidgets import QApplication

from app.render.cave_grider import CaveGrider
from app.render.maze_grider import MazeGrider
from app.render.render import CaveRender, MazeRender, MazeSolutionRender
from models.field import CaveFieldModel, MazeFieldModel
from utils.config import (
    CANVAS_HEIGHT,
    CANVAS_WIDTH,
    COLOR_BACKGROUND,
    COLOR_WALL,
)

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def cave_model() -> CaveFieldModel:
    """2×2 CaveFieldModel with two live cells on the diagonal."""
    cells = [[True, False], [False, True]]
    return CaveFieldModel(rows=2, cols=2, cells=cells)


@pytest.fixture
def maze_grider(maze_model: MazeFieldModel) -> MazeGrider:
    """MazeGrider built from the shared 4×4 maze_model fixture."""
    return MazeGrider(maze_model)


@pytest.fixture
def cave_grider(cave_model: CaveFieldModel) -> CaveGrider:
    """CaveGrider built from the 2×2 cave_model fixture."""
    return CaveGrider(cave_model)


@pytest.fixture
def maze_render(qapp: QApplication, maze_model: MazeFieldModel) -> MazeRender:
    """MazeRender for the shared 4×4 maze_model."""
    return MazeRender(MazeGrider(maze_model))


@pytest.fixture
def cave_render(qapp: QApplication, cave_model: CaveFieldModel) -> CaveRender:
    """CaveRender for the 2×2 cave_model."""
    return CaveRender(CaveGrider(cave_model))


# ---------------------------------------------------------------------------
# MazeRender
# ---------------------------------------------------------------------------


class TestMazeRender:
    """Tests for MazeRender — image dimensions, colours, and type guards."""

    def test_image_size(self, maze_render: MazeRender) -> None:
        img = maze_render.get_image()
        assert img.width() == CANVAS_WIDTH
        assert img.height() == CANVAS_HEIGHT

    def test_image_not_null(self, maze_render: MazeRender) -> None:
        assert not maze_render.get_image().isNull()

    def test_background_color(self, maze_render: MazeRender) -> None:
        """The centre of the first cell should be the background
        colour (not a wall)."""
        img = maze_render.get_image()
        # For a 4×4 maze on 500×500 px the centre of the first
        # cell is roughly (50, 50)
        pixel = QColor(img.pixel(50, 50))
        expected = QColor(*COLOR_BACKGROUND)
        assert pixel.rgb() == expected.rgb()

    def test_has_wall_pixels(self, maze_render: MazeRender) -> None:
        """At least one pixel must be the wall colour."""
        img = maze_render.get_image()
        wall_color = QColor(*COLOR_WALL).rgb()
        found = any(
            QColor(img.pixel(x, y)).rgb() == wall_color
            for x in range(0, CANVAS_WIDTH, 5)
            for y in range(0, CANVAS_HEIGHT, 5)
        )
        assert found

    def test_wrong_type_raises(
        self, qapp: QApplication, cave_grider: CaveGrider
    ) -> None:
        with pytest.raises(TypeError):
            MazeRender(cave_grider)


# ---------------------------------------------------------------------------
# CaveRender
# ---------------------------------------------------------------------------


class TestCaveRender:
    """Tests for CaveRender — image dimensions, live-cell painting,
    and type guards."""

    def test_image_size(self, cave_render: CaveRender) -> None:
        img = cave_render.get_image()
        assert img.width() == CANVAS_WIDTH
        assert img.height() == CANVAS_HEIGHT

    def test_has_black_pixels(self, cave_render: CaveRender) -> None:
        """Live cells should be painted black."""
        img = cave_render.get_image()
        black = QColor(0, 0, 0).rgb()
        found = any(
            QColor(img.pixel(x, y)).rgb() == black
            for x in range(0, CANVAS_WIDTH, 5)
            for y in range(0, CANVAS_HEIGHT, 5)
        )
        assert found

    def test_wrong_type_raises(
        self, qapp: QApplication, maze_grider: MazeGrider
    ) -> None:
        with pytest.raises(TypeError):
            CaveRender(maze_grider)


# ---------------------------------------------------------------------------
# MazeSolutionRender
# ---------------------------------------------------------------------------


class TestMazeSolutionRender:
    """Tests for MazeSolutionRender — path overlay on a base maze image."""

    def test_does_not_modify_original(
        self, qapp: QApplication, maze_model: MazeFieldModel
    ) -> None:
        grider = MazeGrider(maze_model)
        base = MazeRender(grider).get_image()
        original_pixel = base.pixel(100, 100)
        MazeSolutionRender(base, grider, [(0, 0), (0, 1), (1, 1)])
        assert base.pixel(100, 100) == original_pixel

    def test_single_cell_path_no_line(
        self, qapp: QApplication, maze_model: MazeFieldModel
    ) -> None:
        """A path of one cell — no line is drawn (no pairs)."""
        grider = MazeGrider(maze_model)
        base = MazeRender(grider).get_image()
        sol = MazeSolutionRender(base, grider, [(0, 0)])
        assert isinstance(sol.get_image(), QImage)

    def test_custom_path_color(
        self, qapp: QApplication, maze_model: MazeFieldModel
    ) -> None:
        grider = MazeGrider(maze_model)
        base = MazeRender(grider).get_image()
        orange = QColor(255, 140, 0)
        sol = MazeSolutionRender(
            base, grider, [(0, 0), (0, 1)], path_color=orange
        )
        assert isinstance(sol.get_image(), QImage)

    def test_with_start_and_end_markers(
        self, qapp: QApplication, maze_model: MazeFieldModel
    ) -> None:
        grider = MazeGrider(maze_model)
        base = MazeRender(grider).get_image()
        sol = MazeSolutionRender(
            base, grider, [(0, 0), (1, 1)], start=(0, 0), end=(1, 1)
        )
        assert isinstance(sol.get_image(), QImage)

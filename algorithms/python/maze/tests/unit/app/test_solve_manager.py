"""Tests for SolveManager."""

from unittest.mock import MagicMock

import pytest
from PyQt5.QtGui import QImage
from PyQt5.QtWidgets import QApplication

from app.controller.solve_manager import SolveManager
from app.render.maze_grider import MazeGrider
from app.render.render import MazeRender
from models.field import MazeFieldModel


@pytest.fixture
def mgr() -> SolveManager:
    """Fresh SolveManager with all fields at their default
    (None/False) state."""
    return SolveManager()


@pytest.fixture
def grider_and_image(qapp: QApplication) -> tuple[MazeGrider, QImage]:
    """Returns (grider, base_image) for rendering tests."""
    model = MazeFieldModel(
        rows=4,
        cols=4,
        vertical_walls=[[0, 0, 1, 1]] * 4,
        horizontal_walls=[[0, 1, 0, 1]] * 4,
    )
    grider = MazeGrider(model)
    image = MazeRender(grider).get_image()
    return grider, image


# ---------------------------------------------------------------------------
# reset / clear
# ---------------------------------------------------------------------------


class TestReset:
    """Tests for SolveManager.reset and SolveManager.clear."""

    def test_reset_clears_start_end_path(self, mgr: SolveManager) -> None:
        mgr.start = (0, 0)
        mgr.end = (3, 3)
        mgr.path = [(0, 0), (3, 3)]
        mgr.reset()
        assert mgr.start is None
        assert mgr.end is None
        assert mgr.path is None

    def test_reset_clears_agent_trained(self, mgr: SolveManager) -> None:
        mgr.agent_trained = True
        mgr.reset()
        assert mgr.agent_trained is False

    def test_reset_keeps_grider(self, mgr: SolveManager) -> None:
        mgr.grider = MagicMock()
        mgr.reset()
        assert mgr.grider is not None

    def test_reset_keeps_base_image(self, mgr: SolveManager) -> None:
        mgr.base_image = MagicMock()
        mgr.reset()
        assert mgr.base_image is not None

    def test_clear_also_removes_grider_and_image(
        self, mgr: SolveManager
    ) -> None:
        mgr.grider = MagicMock()
        mgr.base_image = MagicMock()
        mgr.start = (0, 0)
        mgr.clear()
        assert mgr.grider is None
        assert mgr.base_image is None
        assert mgr.start is None


# ---------------------------------------------------------------------------
# can_solve
# ---------------------------------------------------------------------------


class TestCanSolve:
    """Tests for SolveManager.can_solve."""

    def test_false_when_both_none(self, mgr: SolveManager) -> None:
        assert mgr.can_solve() is False

    def test_false_when_only_start(self, mgr: SolveManager) -> None:
        mgr.start = (0, 0)
        assert mgr.can_solve() is False

    def test_false_when_only_end(self, mgr: SolveManager) -> None:
        mgr.end = (3, 3)
        assert mgr.can_solve() is False

    def test_true_when_both_set(self, mgr: SolveManager) -> None:
        mgr.start = (0, 0)
        mgr.end = (3, 3)
        assert mgr.can_solve() is True


# ---------------------------------------------------------------------------
# get_hint
# ---------------------------------------------------------------------------


class TestGetHint:
    """Tests for SolveManager.get_hint."""

    def test_no_start_returns_start_hint(self, mgr: SolveManager) -> None:
        hint, ready = mgr.get_hint()
        assert "start" in hint.lower()
        assert ready is False

    def test_start_only_returns_finish_hint(self, mgr: SolveManager) -> None:
        mgr.start = (0, 0)
        hint, ready = mgr.get_hint()
        assert "end" in hint.lower()
        assert ready is False

    def test_start_and_end_returns_ready(self, mgr: SolveManager) -> None:
        mgr.start = (0, 0)
        mgr.end = (3, 3)
        hint, ready = mgr.get_hint()
        assert ready is True
        assert "(0, 0)" in hint
        assert "(3, 3)" in hint

    def test_agent_trained_with_end_returns_agent_hint(
        self, mgr: SolveManager
    ) -> None:
        mgr.agent_trained = True
        mgr.end = (2, 2)
        hint, ready = mgr.get_hint()
        assert "click any cell to set start" in hint
        assert ready is True

    def test_agent_trained_without_end_falls_through(
        self, mgr: SolveManager
    ) -> None:
        mgr.agent_trained = True
        mgr.end = None
        # end is None → agent branch does not trigger
        _, ready = mgr.get_hint()
        assert ready is False


# ---------------------------------------------------------------------------
# handle_regular_click
# ---------------------------------------------------------------------------


class TestHandleRegularClick:
    """Tests for SolveManager.handle_regular_click."""

    def test_first_click_sets_start(self, mgr: SolveManager) -> None:
        mgr.handle_regular_click((1, 2))
        assert mgr.start == (1, 2)
        assert mgr.end is None

    def test_first_click_clears_path(self, mgr: SolveManager) -> None:
        mgr.path = [(0, 0)]
        mgr.handle_regular_click((0, 0))
        assert mgr.path is None

    def test_second_click_sets_end(self, mgr: SolveManager) -> None:
        mgr.handle_regular_click((0, 0))
        mgr.handle_regular_click((3, 3))
        assert mgr.start == (0, 0)
        assert mgr.end == (3, 3)

    def test_third_click_resets_and_new_start(self, mgr: SolveManager) -> None:
        mgr.handle_regular_click((0, 0))
        mgr.handle_regular_click((1, 1))
        mgr.handle_regular_click((2, 2))
        assert mgr.start == (2, 2)
        assert mgr.end is None
        assert mgr.path is None


# ---------------------------------------------------------------------------
# render_overlay
# ---------------------------------------------------------------------------


class TestRenderOverlay:
    """Tests for SolveManager.render_overlay."""

    def test_returns_none_without_base_image(self, mgr: SolveManager) -> None:
        mgr.grider = MagicMock()
        assert mgr.render_overlay() is None

    def test_returns_none_without_grider(self, mgr: SolveManager) -> None:
        mgr.base_image = MagicMock()
        assert mgr.render_overlay() is None

    def test_returns_qimage_when_both_set(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        grider, image = grider_and_image
        mgr.grider = grider
        mgr.base_image = image
        result = mgr.render_overlay()
        assert isinstance(result, QImage)
        assert not result.isNull()

    def test_works_without_path(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        grider, image = grider_and_image
        mgr.grider = grider
        mgr.base_image = image
        mgr.path = None
        result = mgr.render_overlay()
        assert result is not None

    def test_works_with_path(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        grider, image = grider_and_image
        mgr.grider = grider
        mgr.base_image = image
        mgr.start = (0, 0)
        mgr.end = (3, 3)
        mgr.path = [(0, 0), (1, 0), (2, 0), (3, 0), (3, 1), (3, 2), (3, 3)]
        result = mgr.render_overlay()
        assert isinstance(result, QImage)


# ---------------------------------------------------------------------------
# pixel_to_cell
# ---------------------------------------------------------------------------


class TestPixelToCell:
    """Tests for SolveManager.pixel_to_cell."""

    def test_no_grider_returns_none(self, mgr: SolveManager) -> None:
        """Returns None when grider is not set."""
        assert mgr.pixel_to_cell(100, 100) is None

    def test_inside_first_cell(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click at the top-left corner of the grid → cell (0, 0)."""
        grider, _ = grider_and_image
        mgr.grider = grider
        x = grider.start_offset.x
        y = grider.start_offset.y
        assert mgr.pixel_to_cell(x, y) == (0, 0)

    def test_inside_last_cell(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click inside the bottom-right cell → cell (rows-1, cols-1)."""
        grider, _ = grider_and_image
        mgr.grider = grider
        step_x = grider.cell_size.width + grider.wall_thickness
        step_y = grider.cell_size.height + grider.wall_thickness
        x = grider.start_offset.x + (grider.cols - 1) * step_x
        y = grider.start_offset.y + (grider.rows - 1) * step_y
        assert mgr.pixel_to_cell(x, y) == (grider.rows - 1, grider.cols - 1)

    def test_outside_left_returns_none(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click to the left of the grid → None."""
        grider, _ = grider_and_image
        mgr.grider = grider
        x = grider.start_offset.x - 1
        y = grider.start_offset.y
        assert mgr.pixel_to_cell(x, y) is None

    def test_outside_top_returns_none(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click above the grid → None."""
        grider, _ = grider_and_image
        mgr.grider = grider
        x = grider.start_offset.x
        y = grider.start_offset.y - 1
        assert mgr.pixel_to_cell(x, y) is None

    def test_outside_right_returns_none(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click one full step beyond the last column → None."""
        grider, _ = grider_and_image
        mgr.grider = grider
        step_x = grider.cell_size.width + grider.wall_thickness
        x = grider.start_offset.x + grider.cols * step_x
        y = grider.start_offset.y
        assert mgr.pixel_to_cell(x, y) is None

    def test_outside_bottom_returns_none(
        self, mgr: SolveManager, grider_and_image: tuple[MazeGrider, QImage]
    ) -> None:
        """Click one full step beyond the last row → None."""
        grider, _ = grider_and_image
        mgr.grider = grider
        step_y = grider.cell_size.height + grider.wall_thickness
        x = grider.start_offset.x
        y = grider.start_offset.y + grider.rows * step_y
        assert mgr.pixel_to_cell(x, y) is None

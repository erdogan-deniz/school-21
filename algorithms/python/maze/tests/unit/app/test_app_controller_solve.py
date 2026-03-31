"""Tests for AppController: on_solve_maze, _reset_solve_state,
_emit_solve_ui, _render_solve_overlay."""

from unittest.mock import MagicMock

import pytest
from PyQt5.QtGui import QImage
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController
from app.render.maze_grider import MazeGrider
from app.render.render import MazeRender
from models.field import MazeFieldModel

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def maze_grider_and_image(qapp: QApplication) -> tuple[MazeGrider, QImage]:
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
# on_solve_maze
# ---------------------------------------------------------------------------


class TestOnSolveMaze:
    """Tests for AppController.on_solve_maze."""

    def test_returns_early_when_start_and_end_not_set(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 1: start/end not set → return, error_occurred is not emitted."""
        assert ctrl._solve.start is None
        assert ctrl._solve.end is None
        with qtbot.assertNotEmitted(ctrl.error_occurred):
            ctrl.on_solve_maze()
        ctrl.business_controller.solve_maze.assert_not_called()

    def test_returns_early_when_only_start_set(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """start is set, end is not → return."""
        ctrl._solve.start = (0, 0)
        with qtbot.assertNotEmitted(ctrl.error_occurred):
            ctrl.on_solve_maze()
        ctrl.business_controller.solve_maze.assert_not_called()

    def test_emits_error_when_path_is_none(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 2: start/end are set, solve_maze returns None
        → error_occurred."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (3, 3)
        ctrl.business_controller.solve_maze.return_value = None
        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_solve_maze()
        assert "not found" in blocker.args[0].lower()

    def test_sets_current_solve_path_when_path_found(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 3: start/end are set, path found → _solve.path is set."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (3, 3)
        path = [(0, 0), (0, 1), (1, 1), (3, 3)]
        ctrl.business_controller.solve_maze.return_value = path
        ctrl._render_solve_overlay = MagicMock()

        ctrl.on_solve_maze()

        assert ctrl._solve.path == path

    def test_calls_render_solve_overlay_when_path_found(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """When a path is found _render_solve_overlay is called."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (1, 1)
        ctrl.business_controller.solve_maze.return_value = [(0, 0), (1, 1)]
        ctrl._render_solve_overlay = MagicMock()

        ctrl.on_solve_maze()

        ctrl._render_solve_overlay.assert_called_once()


# ---------------------------------------------------------------------------
# _reset_solve_state
# ---------------------------------------------------------------------------


class TestResetSolveState:
    """Tests for AppController._reset_solve_state."""

    def test_clears_start_end_and_path(self, ctrl: AppController) -> None:
        """Test 4: after setting start/end → everything is cleared."""
        ctrl._solve.start = (1, 2)
        ctrl._solve.end = (3, 4)
        ctrl._solve.path = [(1, 2), (3, 4)]

        ctrl._reset_solve_state()

        assert ctrl._solve.start is None
        assert ctrl._solve.end is None
        assert ctrl._solve.path is None

    def test_resets_agent_trained_flag(self, ctrl: AppController) -> None:
        """Test 5: _solve.agent_trained is reset to False."""
        ctrl._solve.agent_trained = True

        ctrl._reset_solve_state()

        assert ctrl._solve.agent_trained is False

    def test_emits_solve_ui_updated(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """_reset_solve_state calls _emit_solve_ui →
        solve_ui_updated is emitted."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (1, 1)

        with qtbot.waitSignal(ctrl.solve_ui_updated, timeout=500):
            ctrl._reset_solve_state()


# ---------------------------------------------------------------------------
# _emit_solve_ui
# ---------------------------------------------------------------------------


class TestEmitSolveUi:
    """Tests for AppController._emit_solve_ui."""

    def test_start_is_none_hint_contains_start_and_ready_false(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 6: start is None → hint contains 'start', ready=False."""
        ctrl._solve.start = None
        ctrl._solve.end = None
        ctrl._solve.agent_trained = False

        with qtbot.waitSignal(ctrl.solve_ui_updated, timeout=500) as blocker:
            ctrl._emit_solve_ui()

        hint, ready = blocker.args
        assert "start" in hint.lower()
        assert ready is False

    def test_start_set_end_none_hint_contains_finish_and_ready_false(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 7: start is set, end is None → hint contains 'end',
        ready=False."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = None
        ctrl._solve.agent_trained = False

        with qtbot.waitSignal(ctrl.solve_ui_updated, timeout=500) as blocker:
            ctrl._emit_solve_ui()

        hint, ready = blocker.args
        assert "end" in hint.lower()
        assert ready is False

    def test_start_and_end_set_ready_true(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 8: start and end are both set → ready=True."""
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (3, 3)
        ctrl._solve.agent_trained = False

        with qtbot.waitSignal(ctrl.solve_ui_updated, timeout=500) as blocker:
            ctrl._emit_solve_ui()

        _, ready = blocker.args
        assert ready is True

    def test_agent_trained_with_end_ready_true_hint_contains_agent(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 9: agent_trained=True and end is not None →
        ready=True, hint prompts to set start."""
        ctrl._solve.agent_trained = True
        ctrl._solve.end = (2, 2)
        ctrl._solve.start = None

        with qtbot.waitSignal(ctrl.solve_ui_updated, timeout=500) as blocker:
            ctrl._emit_solve_ui()

        hint, ready = blocker.args
        assert "click any cell to set start" in hint
        assert ready is True


# ---------------------------------------------------------------------------
# _render_solve_overlay
# ---------------------------------------------------------------------------


class TestRenderSolveOverlay:
    """Tests for AppController._render_solve_overlay."""

    def test_returns_early_when_base_image_is_none(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 10: base_image is None → return,
        maze_rendered is not emitted."""
        ctrl._solve.base_image = None
        ctrl._solve.grider = MagicMock()

        with qtbot.assertNotEmitted(ctrl.maze_rendered):
            ctrl._render_solve_overlay()

    def test_returns_early_when_grider_is_none(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        maze_grider_and_image: tuple[MazeGrider, QImage],
    ) -> None:
        """_solve.grider is None → return, maze_rendered is not emitted."""
        _, image = maze_grider_and_image
        ctrl._solve.base_image = image
        ctrl._solve.grider = None

        with qtbot.assertNotEmitted(ctrl.maze_rendered):
            ctrl._render_solve_overlay()

    def test_emits_maze_rendered_when_both_set(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        maze_grider_and_image: tuple[MazeGrider, QImage],
    ) -> None:
        """Test 11: base_image and grider are both set →
        maze_rendered is emitted."""
        grider, image = maze_grider_and_image
        ctrl._solve.base_image = image
        ctrl._solve.grider = grider
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (3, 3)
        ctrl._solve.path = [(0, 0), (1, 0), (3, 3)]

        with qtbot.waitSignal(ctrl.maze_rendered, timeout=500) as blocker:
            ctrl._render_solve_overlay()

        emitted_image = blocker.args[0]
        assert isinstance(emitted_image, QImage)
        assert not emitted_image.isNull()

    def test_emits_maze_rendered_with_empty_path(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        maze_grider_and_image: tuple[MazeGrider, QImage],
    ) -> None:
        """_render_solve_overlay works without a path (_solve.path=None)."""
        grider, image = maze_grider_and_image
        ctrl._solve.base_image = image
        ctrl._solve.grider = grider
        ctrl._solve.path = None

        with qtbot.waitSignal(ctrl.maze_rendered, timeout=500) as blocker:
            ctrl._render_solve_overlay()

        assert isinstance(blocker.args[0], QImage)

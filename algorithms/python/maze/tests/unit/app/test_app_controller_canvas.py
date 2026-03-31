"""Tests for AppController: on_canvas_click and on_agent_solve."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController, AppMode
from app.render.maze_grider import MazeGrider
from app.render.render import MazeRender
from models.field import MazeFieldModel

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def ctrl_with_maze(qapp: QApplication) -> AppController:
    """AppController with a loaded maze for canvas_click tests."""
    with patch("app.controller.app_controller.BusinessController"):
        ac = AppController()
    ac.business_controller = MagicMock()
    model = MazeFieldModel(
        rows=4,
        cols=4,
        vertical_walls=[[0, 0, 1, 1]] * 4,
        horizontal_walls=[[0, 1, 0, 1]] * 4,
    )
    grider = MazeGrider(model)
    image = MazeRender(grider).get_image()
    ac._solve.grider = grider
    ac.current_field_model = model
    ac._solve.base_image = image
    ac._render_solve_overlay = MagicMock()  # skip actual rendering
    return ac


def _cell_coords(grider: MazeGrider, row: int, col: int) -> tuple[int, int]:
    """Returns pixel coordinates of the centre of cell (row, col)."""
    step_x = grider.cell_size.width + grider.wall_thickness
    step_y = grider.cell_size.height + grider.wall_thickness
    img_x = grider.start_offset.x + col * step_x + 1
    img_y = grider.start_offset.y + row * step_y + 1
    return img_x, img_y


# ---------------------------------------------------------------------------
# on_canvas_click
# ---------------------------------------------------------------------------


class TestOnCanvasClick:
    """Tests for AppController.on_canvas_click."""

    def test_cave_mode_returns_immediately(self, ctrl: AppController) -> None:
        """Test 1: In CAVE mode on_canvas_click does not change _solve.start."""
        ctrl.current_mode = AppMode.CAVE
        ctrl.on_canvas_click(100, 100)
        assert ctrl._solve.start is None

    def test_no_grider_returns_immediately(self, ctrl: AppController) -> None:
        """Test 2: Without a loaded grider on_canvas_click does nothing."""
        assert ctrl._solve.grider is None
        ctrl.on_canvas_click(100, 100)
        assert ctrl._solve.start is None

    def test_first_click_sets_solve_start(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 3: First click on a valid cell sets _solve.start."""
        ac = ctrl_with_maze
        img_x, img_y = _cell_coords(ac._solve.grider, 0, 0)
        ac.on_canvas_click(img_x, img_y)
        assert ac._solve.start == (0, 0)
        assert ac._solve.end is None

    def test_second_click_sets_solve_end(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 4: Second click on a different cell sets _solve.end."""
        ac = ctrl_with_maze
        x0, y0 = _cell_coords(ac._solve.grider, 0, 0)
        x1, y1 = _cell_coords(ac._solve.grider, 1, 1)
        ac.on_canvas_click(x0, y0)
        ac.on_canvas_click(x1, y1)
        assert ac._solve.start == (0, 0)
        assert ac._solve.end == (1, 1)

    def test_third_click_resets_and_updates_start(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 5: Third click resets _solve.end and updates _solve.start."""
        ac = ctrl_with_maze
        x0, y0 = _cell_coords(ac._solve.grider, 0, 0)
        x1, y1 = _cell_coords(ac._solve.grider, 1, 1)
        x2, y2 = _cell_coords(ac._solve.grider, 2, 2)
        ac.on_canvas_click(x0, y0)
        ac.on_canvas_click(x1, y1)
        ac.on_canvas_click(x2, y2)
        assert ac._solve.start == (2, 2)
        assert ac._solve.end is None
        assert ac._solve.path is None

    def test_out_of_bounds_click_returns_immediately(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 6: Click outside the maze changes nothing."""
        ac = ctrl_with_maze
        ac.on_canvas_click(9999, 9999)
        assert ac._solve.start is None
        assert ac._solve.end is None

    def test_agent_trained_click_calls_get_agent_path(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 7: When agent_trained=True a click calls get_agent_path."""
        ac = ctrl_with_maze
        ac._solve.agent_trained = True
        ac._solve.end = (3, 3)
        ac.business_controller.get_agent_path.return_value = [(0, 0), (1, 0)]
        img_x, img_y = _cell_coords(ac._solve.grider, 0, 0)
        ac.on_canvas_click(img_x, img_y)
        ac.business_controller.get_agent_path.assert_called_once_with((0, 0))

    def test_agent_trained_path_not_none_updates_solve_path(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 8: If the agent returned a path, _solve.path is updated."""
        ac = ctrl_with_maze
        ac._solve.agent_trained = True
        ac._solve.end = (3, 3)
        expected_path = [(0, 0), (1, 0), (2, 0)]
        ac.business_controller.get_agent_path.return_value = expected_path
        img_x, img_y = _cell_coords(ac._solve.grider, 0, 0)
        ac.on_canvas_click(img_x, img_y)
        assert ac._solve.path == expected_path

    def test_agent_trained_path_none_emits_error(
        self, qtbot: QtBot, ctrl_with_maze: AppController
    ) -> None:
        """Test 9: If the agent found no path, error_occurred is emitted."""
        ac = ctrl_with_maze
        ac._solve.agent_trained = True
        ac._solve.end = (3, 3)
        ac.business_controller.get_agent_path.return_value = None
        img_x, img_y = _cell_coords(ac._solve.grider, 0, 0)
        with qtbot.waitSignal(ac.error_occurred, timeout=500) as blocker:
            ac.on_canvas_click(img_x, img_y)
        assert blocker.args[0]  # error message is not empty
        assert ac._solve.path is None

    def test_agent_trained_path_none_resets_start(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 9b: If agent found no path, _solve.start is reset to None
        so the next click re-enters start-selection mode."""
        ac = ctrl_with_maze
        ac._solve.agent_trained = True
        ac._solve.end = (3, 3)
        ac.business_controller.get_agent_path.return_value = None
        img_x, img_y = _cell_coords(ac._solve.grider, 0, 0)
        ac.on_canvas_click(img_x, img_y)
        assert ac._solve.start is None


# ---------------------------------------------------------------------------
# on_agent_solve
# ---------------------------------------------------------------------------


class TestOnAgentSolve:
    """Tests for AppController.on_agent_solve."""

    def test_no_start_end_returns_immediately(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Test 10: Without _solve.start/_solve.end on_agent_solve
        does nothing."""
        with qtbot.assertNotEmitted(ctrl.agent_status_updated):
            ctrl.on_agent_solve(100)
        assert not ctrl._solve.agent_trained

    def test_path_found_sets_agent_trained(
        self, ctrl_with_maze: AppController
    ) -> None:
        """Test 11: If a path is found, agent_trained=True
        and _solve.path is set."""
        ac = ctrl_with_maze
        ac._solve.start = (0, 0)
        ac._solve.end = (3, 3)
        expected_path = [(0, 0), (1, 0), (2, 0), (3, 0), (3, 1), (3, 2), (3, 3)]
        ac.business_controller.run_agent.return_value = expected_path
        ac.on_agent_solve(500)
        assert ac._solve.agent_trained is True
        assert ac._solve.path == expected_path

    def test_path_none_emits_error(
        self, qtbot: QtBot, ctrl_with_maze: AppController
    ) -> None:
        """Test 12: If the agent found no path, error_occurred is emitted."""
        ac = ctrl_with_maze
        ac._solve.start = (0, 0)
        ac._solve.end = (3, 3)
        ac.business_controller.run_agent.return_value = None
        with qtbot.waitSignal(ac.error_occurred, timeout=500) as blocker:
            ac.on_agent_solve(100)
        assert blocker.args[0]  # message is not empty
        assert ac._solve.agent_trained is False

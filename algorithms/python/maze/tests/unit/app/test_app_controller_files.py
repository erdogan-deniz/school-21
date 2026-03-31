"""Tests for AppController: file loading/saving and maze clearing."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController
from models.field import CaveFieldModel, MazeFieldModel


@pytest.fixture
def ctrl(qapp: QApplication) -> AppController:
    """AppController with mocked business_controller,
    render_maze, and render_cave."""
    with patch("app.controller.app_controller.BusinessController"):
        ac = AppController()
    ac.business_controller = MagicMock()
    ac.render_maze = MagicMock()
    ac.render_cave = MagicMock()
    return ac


# ---------------------------------------------------------------------- helpers


def make_maze_model() -> MazeFieldModel:
    """Creates a minimal MazeFieldModel for tests."""
    return MazeFieldModel(
        rows=2,
        cols=2,
        vertical_walls=[[0, 1], [0, 1]],
        horizontal_walls=[[0, 0], [1, 1]],
    )


def make_cave_model() -> CaveFieldModel:
    """Creates a minimal CaveFieldModel for tests."""
    return CaveFieldModel(rows=2, cols=2, cells=[[True, False], [False, True]])


# -------------------------------------------------------- on_maze_file_selected


class TestOnMazeFileSelected:
    """Tests for AppController.on_maze_file_selected."""

    def test_delegates_to_load_and_render_maze(
        self, ctrl: AppController
    ) -> None:
        """on_maze_file_selected should call _load_and_render_maze."""
        ctrl._load_and_render_maze = MagicMock()
        ctrl.on_maze_file_selected("/some/maze.txt")
        ctrl._load_and_render_maze.assert_called_once_with("/some/maze.txt")


# -------------------------------------------------------- _load_and_render_maze


class TestLoadAndRenderMaze:
    """Tests for AppController._load_and_render_maze."""

    def test_success_calls_render_maze(self, ctrl: AppController) -> None:
        """On successful load, render_maze is called with the model
        from business_controller."""
        maze = make_maze_model()
        ctrl.business_controller.load_maze_from_file.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = maze

        ctrl._load_and_render_maze("/maze.txt")

        ctrl.render_maze.assert_called_once_with(maze)

    def test_failure_emits_error_occurred(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """On failed load, error_occurred is emitted with the
        expected message."""
        ctrl.business_controller.load_maze_from_file.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl._load_and_render_maze("/bad/path.txt")

        assert blocker.args == ["Failed to load maze."]

    def test_failure_does_not_call_render_maze(
        self, ctrl: AppController
    ) -> None:
        """On failed load, render_maze should not be called."""
        ctrl.business_controller.load_maze_from_file.return_value = False

        ctrl._load_and_render_maze("/bad/path.txt")

        ctrl.render_maze.assert_not_called()

    def test_success_but_no_model_skips_render(
        self, ctrl: AppController
    ) -> None:
        """If get_current_field_model returns None
        — render_maze is not called."""
        ctrl.business_controller.load_maze_from_file.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = None

        ctrl._load_and_render_maze("/maze.txt")

        ctrl.render_maze.assert_not_called()


# -------------------------------------------------------- _load_and_render_cave


class TestLoadAndRenderCave:
    """Tests for AppController._load_and_render_cave."""

    def test_success_calls_render_cave(self, ctrl: AppController) -> None:
        """On successful load, render_cave is called with the model
        from business_controller."""
        cave = make_cave_model()
        ctrl.business_controller.load_cave_from_file.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = cave

        ctrl._load_and_render_cave("/cave.txt")

        ctrl.render_cave.assert_called_once_with(cave)

    def test_failure_emits_error_occurred(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """On failed load, error_occurred is emitted with the
        expected message."""
        ctrl.business_controller.load_cave_from_file.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl._load_and_render_cave("/bad/cave.txt")

        assert blocker.args == ["Failed to load cave."]

    def test_failure_does_not_call_render_cave(
        self, ctrl: AppController
    ) -> None:
        """On failed load, render_cave should not be called."""
        ctrl.business_controller.load_cave_from_file.return_value = False

        ctrl._load_and_render_cave("/bad/cave.txt")

        ctrl.render_cave.assert_not_called()

    def test_success_but_no_model_skips_render(
        self, ctrl: AppController
    ) -> None:
        """If get_current_field_model returns None —
        render_cave is not called."""
        ctrl.business_controller.load_cave_from_file.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = None

        ctrl._load_and_render_cave("/cave.txt")

        ctrl.render_cave.assert_not_called()

    def test_syncs_birth_death_limits_from_loaded_model(
        self, ctrl: AppController
    ) -> None:
        """After loading, cave_birth_limit/cave_death_limit must match the
        loaded model so a subsequent Generate uses the correct values."""
        cave = make_cave_model()
        cave.birth_limit = 2
        cave.death_limit = 1
        ctrl.cave_birth_limit = 5
        ctrl.cave_death_limit = 6
        ctrl.business_controller.load_cave_from_file.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = cave

        ctrl._load_and_render_cave("/cave.txt")

        assert ctrl.cave_birth_limit == 2
        assert ctrl.cave_death_limit == 1


# -------------------------------------------------------- on_cave_file_selected


class TestOnCaveFileSelected:
    """Tests for AppController.on_cave_file_selected."""

    def test_delegates_to_load_and_render_cave(
        self, ctrl: AppController
    ) -> None:
        """on_cave_file_selected should call _load_and_render_cave."""
        ctrl._load_and_render_cave = MagicMock()
        ctrl.on_cave_file_selected("/some/cave.txt")
        ctrl._load_and_render_cave.assert_called_once_with("/some/cave.txt")


# ------------------------------------------------------- on_cave_save_requested


class TestOnCaveSaveRequested:
    """Tests for AppController.on_cave_save_requested."""

    def test_no_model_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """If current_field_model is not set — error_occurred is emitted."""
        ctrl.current_field_model = None

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_cave_save_requested("/out.txt")

        assert blocker.args == ["No cave loaded to save"]

    def test_wrong_model_type_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """If current_field_model is not a CaveFieldModel —
        error_occurred is emitted."""
        ctrl.current_field_model = MagicMock()  # not a CaveFieldModel

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_cave_save_requested("/out.txt")

        assert blocker.args == ["No cave loaded to save"]

    def test_save_success_no_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """On successful save, error_occurred should not be emitted."""
        ctrl.current_field_model = make_cave_model()
        ctrl.business_controller.save_cave_to_file.return_value = True

        with qtbot.assertNotEmitted(ctrl.error_occurred):
            ctrl.on_cave_save_requested("/out.txt")

        ctrl.business_controller.save_cave_to_file.assert_called_once_with(
            "/out.txt"
        )

    def test_save_failure_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """On failed save, error_occurred is emitted."""
        ctrl.current_field_model = make_cave_model()
        ctrl.business_controller.save_cave_to_file.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_cave_save_requested("/out.txt")

        assert blocker.args == ["Failed to save cave"]


# ----------------------------------------------------------------- on_save_maze


class TestOnSaveMaze:
    """Tests for AppController.on_save_maze."""

    def test_failure_emits_error_occurred(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """On failed maze save, error_occurred is emitted."""
        ctrl.business_controller.save_maze.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_save_maze("/maze_out.txt")

        assert blocker.args == ["Failed to save maze"]

    def test_success_no_error(self, qtbot: QtBot, ctrl: AppController) -> None:
        """On successful save, error_occurred should not be emitted."""
        ctrl.business_controller.save_maze.return_value = True

        with qtbot.assertNotEmitted(ctrl.error_occurred):
            ctrl.on_save_maze("/maze_out.txt")

        ctrl.business_controller.save_maze.assert_called_once_with(
            "/maze_out.txt"
        )

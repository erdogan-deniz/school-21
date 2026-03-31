"""Tests for AppController: on_generate_maze, on_generate_cave,
on_cave_next_step, on_auto_play_toggled, on_delay_changed."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController, AppMode
from core.cave import Cave
from models.field import CaveFieldModel, MazeFieldModel


@pytest.fixture
def real_cave_model() -> CaveFieldModel:
    """A minimal real CaveFieldModel that passes isinstance checks."""
    cave = Cave(rows=3, cols=3, birth_limit=4, death_limit=3)
    return CaveFieldModel.from_cave(cave)


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


# ------------------------------------------------------------- on_generate_maze


class TestOnGenerateMaze:
    """Tests for AppController.on_generate_maze."""

    def test_success_calls_render_maze(self, ctrl: AppController) -> None:
        """Successful generation → render_maze is called with the model."""
        maze = MazeFieldModel(
            rows=2,
            cols=2,
            vertical_walls=[[0, 1], [0, 1]],
            horizontal_walls=[[0, 0], [1, 1]],
        )
        ctrl.business_controller.generate_maze.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = maze

        ctrl.on_generate_maze()

        ctrl.render_maze.assert_called_once_with(maze)

    def test_failure_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Failed generation → error_occurred is emitted."""
        ctrl.business_controller.generate_maze.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_generate_maze()

        assert "Failed to generate maze" in blocker.args[0]
        ctrl.render_maze.assert_not_called()


# ------------------------------------------------------------- on_generate_cave


class TestOnGenerateCave:
    """Tests for AppController.on_generate_cave."""

    def test_success_calls_render_cave(
        self, ctrl: AppController, real_cave_model: CaveFieldModel
    ) -> None:
        """Successful cave generation → render_cave is called with the model."""
        ctrl.business_controller.generate_cave.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = (
            real_cave_model
        )

        ctrl.on_generate_cave()

        ctrl.render_cave.assert_called_once_with(real_cave_model)

    def test_failure_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Failed cave generation → error_occurred is emitted."""
        ctrl.business_controller.generate_cave.return_value = False

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_generate_cave()

        assert "Failed to generate cave" in blocker.args[0]
        ctrl.render_cave.assert_not_called()


# ------------------------------------------------------------ on_cave_next_step


class TestOnCaveNextStep:
    """Tests for AppController.on_cave_next_step."""

    def test_in_maze_mode_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Calling next_step in MAZE mode → error_occurred."""
        assert ctrl.current_mode == AppMode.MAZE

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_cave_next_step()

        assert "Not in cave mode" in blocker.args[0]
        ctrl.render_cave.assert_not_called()

    def test_in_cave_mode_renders_next_generation(
        self, ctrl: AppController, real_cave_model: CaveFieldModel
    ) -> None:
        """In CAVE mode with a successful next_cave_generation
        → render_cave is called."""
        ctrl.switch_mode("Cave")
        ctrl.business_controller.next_cave_generation.return_value = True
        ctrl.business_controller.get_current_field_model.return_value = (
            real_cave_model
        )

        ctrl.on_cave_next_step()

        ctrl.render_cave.assert_called_once_with(real_cave_model)


# --------------------------------------------------------- on_auto_play_toggled


class TestOnAutoPlayToggled:
    """Tests for AppController.on_auto_play_toggled."""

    def test_enable_in_maze_mode_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Enabling auto-play in MAZE mode → error_occurred."""
        assert ctrl.current_mode == AppMode.MAZE

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_auto_play_toggled(True)

        assert "Auto play only available in cave mode" in blocker.args[0]
        assert ctrl.auto_play_active is False

    def test_enable_in_cave_no_model_emits_error(
        self, qtbot: QtBot, ctrl: AppController
    ) -> None:
        """Enabling auto-play in CAVE mode without a loaded cave
        → error_occurred."""
        ctrl.switch_mode("Cave")
        ctrl.business_controller.get_current_field_model.return_value = None

        with qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker:
            ctrl.on_auto_play_toggled(True)

        assert "No cave loaded" in blocker.args[0]
        assert ctrl.auto_play_active is False

    def test_enable_in_cave_final_generation_sets_inactive(
        self, ctrl: AppController, real_cave_model: CaveFieldModel
    ) -> None:
        """Enabling auto-play when the cave is already at its final generation
        → auto_play_active=False."""
        ctrl.switch_mode("Cave")
        real_cave_model.is_final_generation = MagicMock(return_value=True)
        ctrl.business_controller.get_current_field_model.return_value = (
            real_cave_model
        )

        ctrl.on_auto_play_toggled(True)

        assert ctrl.auto_play_active is False

    def test_enable_in_cave_normal_sets_active(
        self, ctrl: AppController, real_cave_model: CaveFieldModel
    ) -> None:
        """Enabling auto-play with a normal cave → auto_play_active=True
        and the timer starts."""
        ctrl.switch_mode("Cave")
        real_cave_model.is_final_generation = MagicMock(return_value=False)
        ctrl.business_controller.get_current_field_model.return_value = (
            real_cave_model
        )

        # Mock _auto_play to avoid starting a real Qt timer
        ctrl._auto_play = MagicMock()

        ctrl.on_auto_play_toggled(True)

        assert ctrl.auto_play_active is True
        ctrl._auto_play.start.assert_called_once_with(ctrl.auto_play_delay)

    def test_disable_sets_inactive_and_stops_timer(
        self, ctrl: AppController
    ) -> None:
        """Disabling auto-play → auto_play_active=False and the timer stops."""
        ctrl.auto_play_active = True
        ctrl._auto_play = MagicMock()

        ctrl.on_auto_play_toggled(False)

        assert ctrl.auto_play_active is False
        ctrl._auto_play.stop.assert_called_once()


# ------------------------------------------------------------- on_delay_changed


class TestOnDelayChanged:
    """Tests for AppController.on_delay_changed."""

    def test_updates_auto_play_delay(self, ctrl: AppController) -> None:
        """on_delay_changed updates the auto_play_delay attribute."""
        ctrl.on_delay_changed(200)
        assert ctrl.auto_play_delay == 200

    def test_restarts_timer_when_auto_play_active(
        self, ctrl: AppController
    ) -> None:
        """When auto-play is active, on_delay_changed restarts the timer."""
        ctrl.auto_play_active = True
        ctrl._auto_play = MagicMock()

        ctrl.on_delay_changed(300)

        assert ctrl.auto_play_delay == 300
        ctrl._auto_play.start.assert_called_once_with(300)

    def test_does_not_restart_timer_when_inactive(
        self, ctrl: AppController
    ) -> None:
        """When auto-play is inactive, on_delay_changed does not
        touch the timer."""
        ctrl.auto_play_active = False
        ctrl._auto_play = MagicMock()

        ctrl.on_delay_changed(400)

        ctrl._auto_play.start.assert_not_called()

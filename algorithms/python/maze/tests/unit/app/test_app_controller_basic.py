"""Tests for AppController: switch_mode and simple setters."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController, AppMode


@pytest.fixture
def ctrl(qapp: QApplication) -> tuple[AppController, MagicMock]:
    with patch("app.controller.app_controller.BusinessController"):
        ac = AppController()
    mock_bc = MagicMock()
    ac.business_controller = mock_bc
    return ac, mock_bc


class TestSwitchMode:
    """Tests for AppController.switch_mode."""

    def test_switch_to_cave_changes_current_mode(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """switch_mode('Cave') sets current_mode to AppMode.CAVE."""
        ac, _ = ctrl
        ac.switch_mode("Cave")
        assert ac.current_mode == AppMode.CAVE

    def test_switch_to_cave_emits_size_changed(
        self, qtbot: QtBot, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """switch_mode('Cave') emits the size_changed signal."""
        ac, _ = ctrl
        with qtbot.waitSignal(ac.size_changed, timeout=500):
            ac.switch_mode("Cave")

    def test_switch_to_maze_from_cave(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """Switching back to 'Maze' restores AppMode.MAZE."""
        ac, _ = ctrl
        ac.switch_mode("Cave")
        ac.switch_mode("Maze")
        assert ac.current_mode == AppMode.MAZE

    def test_switch_same_mode_no_change(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """Switching to the already-active mode does not change current_mode."""
        ac, _ = ctrl
        ac.switch_mode("Cave")
        ac.switch_mode("Cave")
        assert ac.current_mode == AppMode.CAVE


class TestSimpleSetters:
    """Tests for AppController setter methods
    (init_chance, birth_limit, death_limit, size).
    """

    def test_on_init_chance_changed(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """on_init_chance_changed updates cave_init_chance."""
        ac, _ = ctrl
        ac.on_init_chance_changed(42)
        assert ac.cave_init_chance == 42

    def test_on_birth_limit_changed_updates_state(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """on_birth_limit_changed updates cave_birth_limit."""
        ac, mock_bc = ctrl
        ac.on_birth_limit_changed(5)
        assert ac.cave_birth_limit == 5

    def test_on_birth_limit_changed_calls_business_controller(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """on_birth_limit_changed delegates to
        business_controller.update_cave_birth_limit."""
        ac, mock_bc = ctrl
        ac.on_birth_limit_changed(5)
        mock_bc.update_cave_birth_limit.assert_called_once_with(5)

    def test_on_death_limit_changed_updates_state(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """on_death_limit_changed updates cave_death_limit."""
        ac, mock_bc = ctrl
        ac.on_death_limit_changed(3)
        assert ac.cave_death_limit == 3

    def test_on_death_limit_changed_calls_business_controller(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """on_death_limit_changed delegates to
        business_controller.update_cave_death_limit."""
        ac, mock_bc = ctrl
        ac.on_death_limit_changed(3)
        mock_bc.update_cave_death_limit.assert_called_once_with(3)

    def test_on_size_changed_maze_mode(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """In MAZE mode on_size_changed updates maze_rows and maze_cols."""
        ac, _ = ctrl
        assert ac.current_mode == AppMode.MAZE
        ac.on_size_changed(10, 12)
        assert ac.maze_rows == 10
        assert ac.maze_cols == 12

    def test_on_size_changed_cave_mode(
        self, ctrl: tuple[AppController, MagicMock]
    ) -> None:
        """In CAVE mode on_size_changed updates cave_rows and cave_cols."""
        ac, _ = ctrl
        ac.switch_mode("Cave")
        ac.on_size_changed(8, 9)
        assert ac.cave_rows == 8
        assert ac.cave_cols == 9

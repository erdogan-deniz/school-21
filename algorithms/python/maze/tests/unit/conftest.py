"""Shared fixtures for unit tests."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtWidgets import QApplication

from app.controller.app_controller import AppController
from models.field import MazeFieldModel


@pytest.fixture
def maze_model() -> MazeFieldModel:
    """4×4 maze with valid walls (used in griders, render, app_controller)."""
    return MazeFieldModel(
        rows=4,
        cols=4,
        vertical_walls=[[0, 0, 1, 1]] * 4,
        horizontal_walls=[[0, 1, 0, 1]] * 4,
    )


@pytest.fixture
def ctrl(qapp: QApplication) -> AppController:
    """AppController with a mocked BusinessController.

    Local fixtures in individual test files may override this fixture
    to add specific behaviour (e.g. mocking render_maze / render_cave
    or returning mock_bc to the caller).
    """
    with patch("app.controller.app_controller.BusinessController"):
        ac = AppController()
    ac.business_controller = MagicMock()
    return ac

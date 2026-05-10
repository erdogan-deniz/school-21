"""Tests for MazeApp in src/app/app.py."""

from unittest.mock import MagicMock, patch

import pytest


@pytest.fixture
def patched_app():
    """Patches all external dependencies of MazeApp."""
    with (
        patch("app.app.ctypes") as mock_ctypes,
        patch("app.app.QApplication"),
        patch("app.app.MainWindow"),
        patch("app.app.ProjectPaths") as mock_paths,
    ):
        mock_paths.get_assets_dir.return_value = MagicMock(
            __truediv__=lambda self, other: MagicMock(exists=lambda: False)
        )
        yield mock_ctypes


class TestMazeApp:
    """Tests for MazeApp initialization and the run method."""

    def test_init_creates_qapplication(self, patched_app: MagicMock) -> None:
        """MazeApp.__init__ creates a QApplication instance."""
        with patch("app.app.QApplication") as mock_qapp:
            from app.app import MazeApp

            MazeApp()
            mock_qapp.assert_called_once()

    def test_init_creates_main_window(self, patched_app: MagicMock) -> None:
        """MazeApp.__init__ creates a MainWindow instance."""
        with patch("app.app.MainWindow") as mock_win:
            from app.app import MazeApp

            MazeApp()
            mock_win.assert_called_once()

    def test_run_shows_window_and_returns_exit_code(
        self, patched_app: MagicMock
    ) -> None:
        """run() calls window.show() and returns the QApplication exit code."""
        from app.app import MazeApp

        app = MazeApp()
        app.app.exec_.return_value = 42
        result = app.run()
        app.window.show.assert_called_once()
        assert result == 42

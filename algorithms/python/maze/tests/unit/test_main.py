"""Tests for the main() function in src/main.py."""

from unittest.mock import MagicMock, patch


def test_main_returns_zero_on_success() -> None:
    """main() returns 0 when MazeApp.run() succeeds."""
    mock_app = MagicMock()
    mock_app.run.return_value = 0
    with patch("app.app.MazeApp", return_value=mock_app):
        from main import main

        assert main() == 0


def test_main_returns_one_on_exception() -> None:
    """main() returns 1 when MazeApp construction raises an exception."""
    with patch("app.app.MazeApp", side_effect=Exception("boom")):
        from main import main

        assert main() == 1

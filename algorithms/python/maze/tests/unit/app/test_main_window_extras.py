"""Tests for MainWindow: show_error and on_quit_clicked."""

from unittest.mock import patch

from PyQt5.QtWidgets import QMessageBox
from pytestqt.qtbot import QtBot

from app.widgets.main_window import MainWindow


class TestShowError:
    """Tests for MainWindow._show_error."""

    def test_show_error_calls_warning(self, qtbot: QtBot) -> None:
        """_show_error opens a QMessageBox warning with the given text."""
        win = MainWindow()
        qtbot.addWidget(win)
        with patch("app.widgets.main_window.QMessageBox.warning") as mock_warn:
            win._show_error("Test error")
            mock_warn.assert_called_once_with(win, "Error", "Test error")


class TestOnQuitClicked:
    """Tests for MainWindow.on_quit_clicked."""

    def test_quit_confirmed(self, qtbot: QtBot) -> None:
        """Confirming the quit dialog calls QApplication.quit."""
        win = MainWindow()
        qtbot.addWidget(win)
        with (
            patch(
                "app.widgets.main_window.QMessageBox.question",
                return_value=QMessageBox.Yes,
            ) as mock_q,
            patch("app.widgets.main_window.QApplication.quit") as mock_quit,
        ):
            win.on_quit_clicked()
            mock_q.assert_called_once()
            mock_quit.assert_called_once()

    def test_quit_cancelled(self, qtbot: QtBot) -> None:
        """Cancelling the quit dialog does not call QApplication.quit."""
        win = MainWindow()
        qtbot.addWidget(win)
        with (
            patch(
                "app.widgets.main_window.QMessageBox.question",
                return_value=QMessageBox.No,
            ),
            patch("app.widgets.main_window.QApplication.quit") as mock_quit,
        ):
            win.on_quit_clicked()
            mock_quit.assert_not_called()

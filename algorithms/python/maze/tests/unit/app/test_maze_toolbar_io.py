"""Tests for MazeToolbar I/O methods: on_load/save."""

from unittest.mock import patch

from pytestqt.qtbot import QtBot

from app.widgets.toolbar.maze_toolbar import MazeToolbar


class TestOnLoadClicked:
    """Tests for MazeToolbar.on_load_clicked."""

    def test_file_selected_emits_signal(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("/data/maze.txt", ""),
        ):
            with qtbot.waitSignal(tb.file_loaded, timeout=500) as blocker:
                tb.on_load_clicked()
            assert blocker.args == ["/data/maze.txt"]

    def test_file_selected_updates_path(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("/data/maze.txt", ""),
        ):
            tb.on_load_clicked()
        assert tb.current_file_path == "/data/maze.txt"

    def test_no_file_no_signal(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
                return_value=("", ""),
            ),
            qtbot.assertNotEmitted(tb.file_loaded),
        ):
            tb.on_load_clicked()


class TestOnSaveClicked:
    """Tests for MazeToolbar.on_save_clicked."""

    def test_file_selected_emits_saved(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getSaveFileName",
            return_value=("/data/out.txt", ""),
        ):
            with qtbot.waitSignal(tb.file_saved, timeout=500) as blocker:
                tb.on_save_clicked()
            assert blocker.args == ["/data/out.txt"]

    def test_no_file_no_signal(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getSaveFileName",
                return_value=("", ""),
            ),
            qtbot.assertNotEmitted(tb.file_saved),
        ):
            tb.on_save_clicked()

"""Tests for CaveToolbar I/O methods:
on_load/save/clear/generate + update_limits."""

from unittest.mock import patch

from pytestqt.qtbot import QtBot

from app.widgets.toolbar.cave_toolbar import CaveToolbar
from utils.config import DEFAULT_BIRTH_LIMIT, DEFAULT_DEATH_LIMIT


class TestOnLoadClicked:
    """Tests for CaveToolbar.on_load_clicked."""

    def test_file_selected_emits_file_loaded(self, qtbot: QtBot) -> None:
        """Selecting a file emits file_loaded with the path."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
                return_value=("/data/cave.txt", ""),
            ),
            qtbot.waitSignal(tb.file_loaded, timeout=500) as blocker,
        ):
            tb.on_load_clicked()
        assert blocker.args == ["/data/cave.txt"]

    def test_file_selected_resets_birth_limit(self, qtbot: QtBot) -> None:
        """After loading a file the birth-limit spinbox
        resets to the default."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("/data/cave.txt", ""),
        ):
            tb.on_load_clicked()
        assert tb.evolution_widget.birth_spin.value() == DEFAULT_BIRTH_LIMIT

    def test_file_selected_resets_death_limit(self, qtbot: QtBot) -> None:
        """After loading a file the death-limit spinbox
        resets to the default."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("/data/cave.txt", ""),
        ):
            tb.on_load_clicked()
        assert tb.evolution_widget.death_spin.value() == DEFAULT_DEATH_LIMIT

    def test_no_file_no_signal(self, qtbot: QtBot) -> None:
        """Cancelling the dialog emits no signal."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
                return_value=("", ""),
            ),
            qtbot.assertNotEmitted(tb.file_loaded),
        ):
            tb.on_load_clicked()

    def test_cancel_does_not_reset_birth_limit(self, qtbot: QtBot) -> None:
        """Cancelling the dialog must not reset birth-limit spinbox."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_birth_limit_display(6)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("", ""),
        ):
            tb.on_load_clicked()
        assert tb.evolution_widget.birth_spin.value() == 6

    def test_cancel_does_not_reset_death_limit(self, qtbot: QtBot) -> None:
        """Cancelling the dialog must not reset death-limit spinbox."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_death_limit_display(1)
        with patch(
            "app.widgets.toolbar.base_toolbar.QFileDialog.getOpenFileName",
            return_value=("", ""),
        ):
            tb.on_load_clicked()
        assert tb.evolution_widget.death_spin.value() == 1


class TestOnSaveClicked:
    """Tests for CaveToolbar.on_save_clicked."""

    def test_file_selected_emits_file_saved(self, qtbot: QtBot) -> None:
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getSaveFileName",
                return_value=("/data/out.txt", ""),
            ),
            qtbot.waitSignal(tb.file_saved, timeout=500) as blocker,
        ):
            tb.on_save_clicked()
        assert blocker.args == ["/data/out.txt"]

    def test_no_file_no_signal(self, qtbot: QtBot) -> None:
        """Cancelling the save dialog emits no signal."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with (
            patch(
                "app.widgets.toolbar.base_toolbar.QFileDialog.getSaveFileName",
                return_value=("", ""),
            ),
            qtbot.assertNotEmitted(tb.file_saved),
        ):
            tb.on_save_clicked()


class TestOnGenerateClicked:
    """Tests for CaveToolbar.on_generate_clicked."""

    def test_emits_generate_signal(self, qtbot: QtBot) -> None:
        """on_generate_clicked emits the generate signal."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with qtbot.waitSignal(tb.generate, timeout=500):
            tb.on_generate_clicked()

    def test_emits_auto_play_false(self, qtbot: QtBot) -> None:
        """on_generate_clicked emits auto_play_toggled(False)
        to stop any running auto-play."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        with qtbot.waitSignal(tb.auto_play_toggled, timeout=500) as blocker:
            tb.on_generate_clicked()
        assert blocker.args == [False]


class TestUpdateLimits:
    """Tests for CaveToolbar.update_birth_limit_display /
    update_death_limit_display."""

    def test_update_birth_limit_display(self, qtbot: QtBot) -> None:
        """update_birth_limit_display sets the birth spinbox
        to the given value."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_birth_limit_display(3)
        assert tb.evolution_widget.birth_spin.value() == 3

    def test_update_death_limit_display(self, qtbot: QtBot) -> None:
        """update_death_limit_display sets the death spinbox
        to the given value."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_death_limit_display(2)
        assert tb.evolution_widget.death_spin.value() == 2

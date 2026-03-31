"""Tests for widgets inside cave_toolbar:
CaveFieldWidget, EvolutionWidget, PlaybackWidget, FieldWidget."""

from pytestqt.qtbot import QtBot

from app.widgets.toolbar.base_toolbar import FieldWidget
from app.widgets.toolbar.cave_toolbar import (
    EvolutionWidget,
    PlaybackWidget,
)


class TestFieldWidget:
    """Tests for FieldWidget.set_field_size — silent spinbox update."""

    def test_set_field_size_updates_spinboxes(self, qtbot: QtBot) -> None:
        """set_field_size sets both spinboxes to the given values."""
        fw = FieldWidget()
        qtbot.addWidget(fw)
        fw.set_field_size(15, 20)
        assert fw.rows_spin.value() == 15
        assert fw.cols_spin.value() == 20

    def test_set_field_size_no_rows_signal(self, qtbot: QtBot) -> None:
        """set_field_size does not emit rows_changed."""
        fw = FieldWidget()
        qtbot.addWidget(fw)
        with qtbot.assertNotEmitted(fw.rows_changed):
            fw.set_field_size(10, 5)

    def test_set_field_size_no_cols_signal(self, qtbot: QtBot) -> None:
        """set_field_size does not emit cols_changed."""
        fw = FieldWidget()
        qtbot.addWidget(fw)
        with qtbot.assertNotEmitted(fw.cols_changed):
            fw.set_field_size(5, 10)


class TestEvolutionWidget:
    """Tests for EvolutionWidget — silent spinbox updates."""

    def test_update_birth_limit_silent(self, qtbot: QtBot) -> None:
        """update_birth_limit_silent sets the spinbox without
        emitting birth_limit_changed."""
        ew = EvolutionWidget()
        qtbot.addWidget(ew)
        with qtbot.assertNotEmitted(ew.birth_limit_changed):
            ew.update_birth_limit_silent(3)
        assert ew.birth_spin.value() == 3

    def test_update_death_limit_silent(self, qtbot: QtBot) -> None:
        """update_death_limit_silent sets the spinbox without
        emitting death_limit_changed."""
        ew = EvolutionWidget()
        qtbot.addWidget(ew)
        with qtbot.assertNotEmitted(ew.death_limit_changed):
            ew.update_death_limit_silent(2)
        assert ew.death_spin.value() == 2


class TestPlaybackWidget:
    """Tests for PlaybackWidget — auto-play button text toggling."""

    def test_on_auto_toggled_true_changes_text(self, qtbot: QtBot) -> None:
        """When auto-play is enabled the button label contains 'Stop'."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.on_auto_toggled(True)
        assert "Stop" in pw.auto_button.text()

    def test_on_auto_toggled_false_changes_text(self, qtbot: QtBot) -> None:
        """When auto-play is disabled the button label reverts
        to a play/run label."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.on_auto_toggled(True)
        pw.on_auto_toggled(False)
        assert "Play" in pw.auto_button.text() or "Run" in pw.auto_button.text()

    def test_reset_auto_button_resets_state(self, qtbot: QtBot) -> None:
        """reset_auto_button unchecks the button and sets text to 'Play'."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.on_auto_toggled(True)  # put into active state
        pw.reset_auto_button()
        assert not pw.auto_button.isChecked()
        assert "Play" in pw.auto_button.text()

    def test_reset_auto_button_does_not_emit_signal(self, qtbot: QtBot) -> None:
        """reset_auto_button must not emit auto_play_toggled
        (uses blockSignals to avoid re-entrancy)."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.on_auto_toggled(True)
        with qtbot.assertNotEmitted(pw.auto_play_toggled):
            pw.reset_auto_button()

    def test_set_playback_enabled_disables_both_buttons(
        self, qtbot: QtBot
    ) -> None:
        """set_playback_enabled(False) disables Next and Play buttons."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.set_playback_enabled(False)
        assert not pw.next_button.isEnabled()
        assert not pw.auto_button.isEnabled()

    def test_set_playback_enabled_enables_both_buttons(
        self, qtbot: QtBot
    ) -> None:
        """set_playback_enabled(True) enables Next and Play buttons."""
        pw = PlaybackWidget()
        qtbot.addWidget(pw)
        pw.set_playback_enabled(False)
        pw.set_playback_enabled(True)
        assert pw.next_button.isEnabled()
        assert pw.auto_button.isEnabled()

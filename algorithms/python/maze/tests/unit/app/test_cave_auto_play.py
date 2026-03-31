"""Tests for CaveAutoPlay — timer wrapper for cave auto-play."""

from unittest.mock import MagicMock

import pytest
from pytestqt.qtbot import QtBot

from app.controller.cave_auto_play import CaveAutoPlay


@pytest.fixture
def auto_play() -> CaveAutoPlay:
    return CaveAutoPlay()


class TestCaveAutoPlay:
    """Tests for CaveAutoPlay timer wrapper."""

    def test_start_calls_timer_with_delay(
        self, auto_play: CaveAutoPlay
    ) -> None:
        """start() passes the delay to the underlying QTimer."""
        auto_play._timer = MagicMock()
        auto_play.start(300)
        auto_play._timer.start.assert_called_once_with(300)

    def test_stop_calls_timer_stop(self, auto_play: CaveAutoPlay) -> None:
        """stop() delegates to the underlying QTimer."""
        auto_play._timer = MagicMock()
        auto_play.stop()
        auto_play._timer.stop.assert_called_once()

    def test_step_requested_emitted_on_timeout(
        self, auto_play: CaveAutoPlay, qtbot: QtBot
    ) -> None:
        """step_requested is emitted when the timer fires."""
        with qtbot.waitSignal(auto_play.step_requested, timeout=500):
            auto_play._timer.timeout.emit()

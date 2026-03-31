"""Cave auto-play timer wrapper."""

from PyQt5.QtCore import QObject, QTimer, pyqtSignal


class CaveAutoPlay(QObject):
    """Encapsulates the QTimer used for cave auto-play.

    Emits step_requested on each tick; the caller decides what to do.
    Keeps no state beyond the timer itself — active/delay flags stay
    on AppController so existing signal/slot contracts are unchanged.
    """

    step_requested = pyqtSignal()

    _timer: QTimer

    def __init__(self) -> None:
        """Creates and configures the repeating QTimer."""
        super().__init__()
        self._timer = QTimer()
        self._timer.setSingleShot(False)
        self._timer.timeout.connect(self.step_requested)

    def start(self, delay_ms: int) -> None:
        """Starts (or restarts) the timer with the given interval.

        Args:
            delay_ms: interval in milliseconds between steps.
        """
        self._timer.start(delay_ms)

    def stop(self) -> None:
        """Stops the timer."""
        self._timer.stop()

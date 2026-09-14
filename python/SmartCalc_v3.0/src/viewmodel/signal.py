"""Minimal pure-Python observer signal, used as a drop-in for pyqtSignal."""

import contextlib
import threading
from collections.abc import Callable
from typing import Any


class Signal:
    """Minimal observer signal — a pure-Python replacement for pyqtSignal.

    Usage mirrors Qt signals: call .connect(callback) to subscribe and
    .emit(*args) to notify all subscribers.  Thread-safe: connect,
    disconnect, and emit may be called concurrently from any thread.
    """

    def __init__(self) -> None:
        """Initialise with an empty subscriber list and a mutex."""
        self._callbacks: list[Callable[..., Any]] = []
        self._lock = threading.Lock()

    def connect(self, callback: Callable[..., Any]) -> None:
        """Register *callback* to be called on emit."""
        with self._lock:
            self._callbacks.append(callback)

    def disconnect(self, callback: Callable[..., Any] | None = None) -> None:
        """Remove *callback* from subscribers, or clear all if None."""
        with self._lock:
            if callback is None:
                self._callbacks.clear()
            else:
                with contextlib.suppress(ValueError):
                    self._callbacks.remove(callback)

    def emit(self, *args: Any) -> None:  # noqa: ANN401
        """Call all registered callbacks with *args*.

        Takes a snapshot of the subscriber list under the lock, then
        iterates outside the lock so that callbacks may call connect()
        or disconnect() without deadlocking.
        """
        with self._lock:
            snapshot = list(self._callbacks)
        for cb in snapshot:
            cb(*args)

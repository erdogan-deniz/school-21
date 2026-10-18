"""Application logger: one file per rotation period, task naming pattern."""

import logging
import os
import re
from collections.abc import Callable
from datetime import datetime
from typing import Final


_LOGS_DIR: Final[str] = os.path.join(
    os.path.dirname(__file__), "..", "..", "logs"
)

# Task requirement: files are named logs_dd-MM-yy-hh-mm-ss.
_NAME_FORMAT: Final[str] = "logs_%d-%m-%y-%H-%M-%S.log"
_NAME_PATTERN: Final[re.Pattern[str]] = re.compile(
    r"^logs_\d{2}-\d{2}-\d{2}-\d{2}-\d{2}-\d{2}\.log$"
)
_PERIODS: Final[frozenset[str]] = frozenset({"hour", "day", "month"})
_BACKUP_COUNT: Final[int] = 30


def _now() -> datetime:
    """Return the current local time with its time zone."""
    return datetime.now().astimezone()


def _period_key(moment: datetime, period: str) -> tuple[int, ...]:
    """Return the part of a timestamp that identifies its rotation period.

    Args:
        moment: Point in time.
        period: One of 'hour', 'day', or 'month'.

    Returns:
        Tuple that is equal for all moments of the same period.

    """
    if period == "hour":
        return (moment.year, moment.month, moment.day, moment.hour)
    if period == "month":
        return (moment.year, moment.month)
    return (moment.year, moment.month, moment.day)


def _parse_name(name: str) -> datetime | None:
    """Return the start time encoded in a log file name.

    Args:
        name: File name to check.

    Returns:
        Start time of the file, or None for names outside the pattern.

    """
    if not _NAME_PATTERN.match(name):
        return None
    try:
        return datetime.strptime(name, _NAME_FORMAT).astimezone()
    except ValueError:
        return None


class PeriodFileHandler(logging.FileHandler):
    """Write one log file per rotation period.

    The file is named after the moment its period started writing:
    ``logs_dd-MM-yy-hh-mm-ss.log``. A restart within the same period
    appends to that period's file; when the period changes, a new file
    is started and only the newest ``backup_count`` files are kept.
    """

    def __init__(
        self,
        logs_dir: str,
        period: str,
        backup_count: int = _BACKUP_COUNT,
        clock: Callable[[], datetime] = _now,
    ) -> None:
        """Open the file of the current period.

        Args:
            logs_dir: Directory for log files.
            period: 'hour', 'day', or 'month'; anything else means 'day'.
            backup_count: Number of newest log files to keep.
            clock: Source of the current time (replaceable in tests).

        """
        self.period: str = period if period in _PERIODS else "day"
        self._dir = logs_dir
        self._backup_count = backup_count
        self._clock = clock
        now = clock()
        self._key = _period_key(now, self.period)
        path = self._current_file(now) or self._path_for(now)
        super().__init__(path, encoding="utf-8", delay=True)

    def _path_for(self, moment: datetime) -> str:
        """Return the file path for a period starting at ``moment``."""
        return os.path.join(self._dir, moment.strftime(_NAME_FORMAT))

    def _own_files(self) -> list[tuple[datetime, str]]:
        """Return (start time, name) of log files in the directory."""
        files = []
        for name in os.listdir(self._dir):
            start = _parse_name(name)
            if start is not None:
                files.append((start, name))
        return sorted(files)

    def _current_file(self, now: datetime) -> str | None:
        """Return the existing file of the current period, if any."""
        for start, name in reversed(self._own_files()):
            if _period_key(start, self.period) == self._key and start <= now:
                return os.path.join(self._dir, name)
        return None

    def _prune(self) -> None:
        """Delete the oldest files so the new one keeps ``backup_count``."""
        files = self._own_files()
        keep = max(self._backup_count - 1, 0)
        for _, name in files[: max(len(files) - keep, 0)]:
            os.remove(os.path.join(self._dir, name))

    def emit(self, record: logging.LogRecord) -> None:
        """Switch to a new file when the period changes, then write.

        Args:
            record: Log record to write.

        """
        now = self._clock()
        key = _period_key(now, self.period)
        if key != self._key:
            self._key = key
            if self.stream:
                self.stream.close()
                self.stream = None  # type: ignore[assignment]
            self.baseFilename = os.path.abspath(self._path_for(now))
            self._prune()
        super().emit(record)


def setup_logger(rotation_period: str = "day") -> logging.Logger:
    """Configure and return the application logger.

    Log files are saved in the logs folder, one file per rotation
    period, named ``logs_dd-MM-yy-hh-mm-ss.log``.

    Args:
        rotation_period: One of 'hour', 'day', or 'month'.

    Returns:
        Configured Logger instance named 'smartcalc'.

    """
    os.makedirs(_LOGS_DIR, exist_ok=True)

    logger = logging.getLogger("smartcalc")
    logger.setLevel(logging.INFO)

    if not logger.handlers:
        handler = PeriodFileHandler(_LOGS_DIR, rotation_period)
        handler.setFormatter(
            logging.Formatter(
                fmt="%(asctime)s  %(levelname)-8s  %(message)s",
                datefmt="%d-%m-%Y %H:%M:%S",
            )
        )
        logger.addHandler(handler)

    return logger

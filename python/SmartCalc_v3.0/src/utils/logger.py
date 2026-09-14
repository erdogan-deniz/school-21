"""Application logger: timed rotating file handler with custom naming."""

import logging
import os
from datetime import UTC, datetime
from logging.handlers import TimedRotatingFileHandler
from typing import Any, Final


_LOG_FILENAME: Final[str] = "smartcalc.log"


_LOGS_DIR: Final[str] = os.path.join(
    os.path.dirname(__file__), "..", "..", "logs"
)

_ROTATION_PARAMS: Final[dict[str, dict[str, str | int]]] = {
    "hour": {"when": "H", "interval": 1},
    "day": {"when": "D", "interval": 1},
}


class _MonthlyRotatingFileHandler(TimedRotatingFileHandler):
    """Rotates the log file at the start of each calendar month."""

    def __init__(self, filename: str, **kwargs: Any) -> None:  # noqa: ANN401
        """Initialize the handler and record the current month.

        Args:
            filename: Path to the log file.
            **kwargs: Additional keyword arguments forwarded to
                TimedRotatingFileHandler.

        """
        super().__init__(filename, when="MIDNIGHT", interval=1, **kwargs)
        self._current_month: int = datetime.now(tz=UTC).month

    def shouldRollover(  # noqa: N802
        self, _record: logging.LogRecord
    ) -> int:
        """Return 1 if the month has changed since the last check, else 0."""
        now = datetime.now(tz=UTC)
        if now.month != self._current_month:
            self._current_month = now.month
            return 1
        return 0


def _date_namer(default_name: str) -> str:
    """Rename rotated log files from .log.<suffix> to <suffix>.log.

    Args:
        default_name: Default path assigned by TimedRotatingFileHandler,
            in the form ``<base>.log.<date-suffix>``.

    Returns:
        Absolute path to the renamed log file.

    """
    dir_name = os.path.dirname(default_name)
    suffix = default_name[default_name.rfind(".log.") + 5 :]
    return os.path.join(dir_name, f"{suffix}.log")


def setup_logger(rotation_period: str = "day") -> logging.Logger:
    """Configure and return the application logger.

    Log files are saved in logs/smartcalc.log. The handler appends
    a date/time suffix to rotated files automatically.

    Args:
        rotation_period: One of 'hour', 'day', or 'month'.

    Returns:
        Configured Logger instance named 'smartcalc'.

    """
    os.makedirs(_LOGS_DIR, exist_ok=True)

    log_filename = os.path.join(_LOGS_DIR, _LOG_FILENAME)

    logger = logging.getLogger("smartcalc")
    logger.setLevel(logging.INFO)

    if not logger.handlers:
        handler: logging.Handler
        if rotation_period == "month":
            handler = _MonthlyRotatingFileHandler(
                filename=log_filename,
                backupCount=30,
                encoding="utf-8",
            )
        else:
            params = _ROTATION_PARAMS.get(
                rotation_period, _ROTATION_PARAMS["day"]
            )
            handler = TimedRotatingFileHandler(
                filename=log_filename,
                when=str(params["when"]),
                interval=int(params["interval"]),
                backupCount=30,
                encoding="utf-8",
            )
        handler.namer = _date_namer
        handler.setFormatter(
            logging.Formatter(
                fmt="%(asctime)s  %(levelname)-8s  %(message)s",
                datefmt="%d-%m-%Y %H:%M:%S",
            )
        )
        logger.addHandler(handler)

    return logger

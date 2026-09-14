"""Configuration reader: loads settings from config.ini at startup."""

import configparser
import logging
import os
from typing import Final


_CONFIG_PATH: Final[str] = os.path.join(
    os.path.dirname(__file__), "..", "config.ini"
)

_DEFAULTS: Final[dict[str, dict[str, str]]] = {
    "display": {
        "theme": "light",
        "font_size": "14",
        "precision": "7",
    },
    "logging": {
        "rotation_period": "day",
    },
}

_VALID_THEMES: Final[frozenset[str]] = frozenset({"light", "dark"})
_VALID_PERIODS: Final[frozenset[str]] = frozenset({"hour", "day", "month"})

_logger = logging.getLogger("smartcalc")


class AppConfig:
    """Read and expose application configuration from config.ini.

    Supported parameters:
        [display]
            theme           - 'light' or 'dark'
            font_size       - integer font size in points, clamped to [6, 72]
            precision       - significant digits shown (1-15)

        [logging]
            rotation_period - 'hour', 'day', or 'month'
    """

    def __init__(self, config_path: str | None = None) -> None:
        """Load configuration, falling back to defaults for missing keys.

        Args:
            config_path: Path to the .ini file. Defaults to src/config.ini.

        """
        self._parser: configparser.ConfigParser = configparser.ConfigParser()
        self._parser.read_dict(_DEFAULTS)
        path = config_path or _CONFIG_PATH
        self._parser.read(path)

    @property
    def theme(self) -> str:
        """Visual theme: 'light' or 'dark'. Falls back to 'light' if unknown."""
        value = self._parser.get("display", "theme")
        if value not in _VALID_THEMES:
            _logger.warning(
                "config.ini: unknown theme=%r, using 'light'.", value
            )
            return "light"
        return value

    @property
    def font_size(self) -> int:
        """UI font size in points, clamped to [6, 72]."""
        try:
            value = self._parser.getint("display", "font_size")
        except ValueError:
            _logger.warning(
                "config.ini: font_size is not a valid integer, using 14."
            )
            return 14
        clamped = max(6, min(72, value))
        if clamped != value:
            _logger.warning(
                "config.ini: font_size=%d out of range [6, 72], using %d.",
                value, clamped,
            )
        return clamped

    @property
    def precision(self) -> int:
        """Significant digits ('g' format), clamped to [1, 15]."""
        try:
            value = self._parser.getint("display", "precision")
        except ValueError:
            _logger.warning(
                "config.ini: precision is not a valid integer, using 7."
            )
            return 7
        clamped = max(1, min(15, value))
        if clamped != value:
            _logger.warning(
                "config.ini: precision=%d out of range [1, 15], using %d.",
                value, clamped,
            )
        return clamped

    @property
    def rotation_period(self) -> str:
        """Log rotation period: 'hour', 'day', or 'month'. Default: 'day'."""
        value = self._parser.get("logging", "rotation_period")
        if value not in _VALID_PERIODS:
            _logger.warning(
                "config.ini: unknown rotation_period=%r, using 'day'.", value
            )
            return "day"
        return value

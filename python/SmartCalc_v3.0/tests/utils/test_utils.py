"""Unit tests for utils.config and utils.logger."""

import logging
import os
from pathlib import Path

import pytest

from utils.config import AppConfig
from utils.logger import setup_logger


class TestAppConfig:
    """Tests for AppConfig reading config.ini."""

    def test_defaults_without_file(self, tmp_path: Path) -> None:
        """Verifies fallback defaults when config.ini is absent."""
        # Passing a non-existent path triggers fallback to _DEFAULTS.
        cfg = AppConfig(config_path=str(tmp_path / "nonexistent.ini"))
        assert cfg.theme == "light"
        assert cfg.font_size == 14
        assert cfg.precision == 7
        assert cfg.rotation_period == "day"

    def test_reads_theme_from_file(self, tmp_path: Path) -> None:
        """Verify the theme property is read from the [display] section."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\ntheme = dark\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.theme == "dark"

    def test_reads_font_size_from_file(self, tmp_path: Path) -> None:
        """Verify the font_size property is read from the [display] section."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nfont_size = 18\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.font_size == 18

    def test_reads_precision_from_file(self, tmp_path: Path) -> None:
        """Verify the precision property is read from the [display] section."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nprecision = 10\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.precision == 10

    def test_reads_rotation_period_from_file(self, tmp_path: Path) -> None:
        """Verifies rotation_period is read from the [logging] section."""
        ini = tmp_path / "test.ini"
        ini.write_text("[logging]\nrotation_period = hour\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.rotation_period == "hour"

    def test_partial_override_keeps_defaults(self, tmp_path: Path) -> None:
        """Verifies that unspecified keys fall back to their default values."""
        # Only theme is set; other keys should stay at defaults.
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\ntheme = dark\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.theme == "dark"
        assert cfg.font_size == 14  # default

    def test_invalid_theme_falls_back_to_light(self, tmp_path: Path) -> None:
        """Verify unknown theme value falls back to 'light' with a warning."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\ntheme = midnight\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.theme == "light"

    def test_font_size_non_integer_falls_back(self, tmp_path: Path) -> None:
        """Verify non-integer font_size falls back to 14."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nfont_size = large\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.font_size == 14

    def test_precision_non_integer_falls_back(self, tmp_path: Path) -> None:
        """Verify non-integer precision falls back to 7."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nprecision = high\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.precision == 7

    def test_font_size_clamped_high(self, tmp_path: Path) -> None:
        """Verify font_size above 72 is clamped to 72."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nfont_size = 200\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.font_size == 72

    def test_font_size_clamped_low(self, tmp_path: Path) -> None:
        """Verify font_size below 6 is clamped to 6."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nfont_size = 2\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.font_size == 6

    def test_precision_clamped_high(self, tmp_path: Path) -> None:
        """Verify precision above 15 is clamped to 15."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nprecision = 20\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.precision == 15

    def test_precision_clamped_low(self, tmp_path: Path) -> None:
        """Verify precision below 1 is clamped to 1."""
        ini = tmp_path / "test.ini"
        ini.write_text("[display]\nprecision = 0\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.precision == 1

    def test_invalid_rotation_period_falls_back_to_day(
        self, tmp_path: Path
    ) -> None:
        """Verify unknown rotation_period falls back to 'day' with a warning."""
        ini = tmp_path / "test.ini"
        ini.write_text("[logging]\nrotation_period = weekly\n")
        cfg = AppConfig(config_path=str(ini))
        assert cfg.rotation_period == "day"

    def test_reads_real_config_ini(self) -> None:
        """Smoke test: read config.ini and validate known-good values."""
        real_ini = os.path.join(
            os.path.dirname(__file__), "..", "..", "src", "config.ini"
        )
        if not os.path.exists(real_ini):
            pytest.skip("config.ini not present")
        cfg = AppConfig(config_path=real_ini)
        assert cfg.theme in {"light", "dark"}
        assert cfg.font_size > 0
        assert cfg.precision > 0
        assert cfg.rotation_period in {"hour", "day", "month"}


class TestSetupLogger:
    """Tests for setup_logger with different rotation periods."""

    @pytest.fixture(autouse=True)
    def _patch_logs_dir(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Redirect log output to tmp_path and reset handlers before each."""
        import utils.logger as lg_mod

        monkeypatch.setattr(lg_mod, "_LOGS_DIR", str(tmp_path))
        logging.getLogger("smartcalc").handlers.clear()

    def test_returns_logger(self, tmp_path: Path) -> None:
        """Verifies setup_logger returns a Logger named 'smartcalc'."""
        logger = setup_logger("day")
        assert isinstance(logger, logging.Logger)
        assert logger.name == "smartcalc"

    def test_log_file_created(self, tmp_path: Path) -> None:
        """Verify a log file is created in the logs directory after setup."""
        setup_logger("day")
        files = list(tmp_path.iterdir())
        assert len(files) == 1
        assert files[0].name == "smartcalc.log"

    def test_log_file_name_pattern(self, tmp_path: Path) -> None:
        """Verify the log filename is the fixed name 'smartcalc.log'."""
        setup_logger("hour")
        files = list(tmp_path.iterdir())
        assert len(files) == 1
        assert files[0].name == "smartcalc.log"

    def test_unknown_period_falls_back_to_day(self, tmp_path: Path) -> None:
        """Verify graceful fallback to daily rotation for an unknown period."""
        logger = setup_logger("unknown_period")
        assert isinstance(logger, logging.Logger)

    def test_can_write_log_message(self, tmp_path: Path) -> None:
        """Verifies that a logged message appears verbatim in the log file."""
        logger = setup_logger("day")
        logger.info("test message")
        files = list(tmp_path.iterdir())
        content = files[0].read_text(encoding="utf-8")
        assert "test message" in content

    def test_month_rotation_creates_log_file(self, tmp_path: Path) -> None:
        """Verify setup_logger('month') creates the log file."""
        setup_logger("month")
        files = list(tmp_path.iterdir())
        assert len(files) == 1
        assert files[0].name == "smartcalc.log"

    def test_monthly_handler_should_rollover_on_month_change(
        self, tmp_path: Path
    ) -> None:
        """Verify _MonthlyRotatingFileHandler rolls over when month changes."""
        from utils.logger import _MonthlyRotatingFileHandler

        log_file = str(tmp_path / "smartcalc.log")
        handler = _MonthlyRotatingFileHandler(
            filename=log_file, backupCount=1, encoding="utf-8"
        )
        # Simulate a month change by forcing _current_month to a past month.
        cur = handler._current_month  # noqa: SLF001
        handler._current_month = cur % 12 + 1  # noqa: SLF001

        dummy = logging.LogRecord(
            name="test",
            level=logging.INFO,
            pathname="",
            lineno=0,
            msg="",
            args=(),
            exc_info=None,
        )
        assert handler.shouldRollover(dummy) == 1
        handler.close()

    def test_monthly_handler_no_rollover_same_month(
        self, tmp_path: Path
    ) -> None:
        """Verify _MonthlyRotatingFileHandler returns 0 in the same month."""
        from utils.logger import _MonthlyRotatingFileHandler

        log_file = str(tmp_path / "smartcalc.log")
        handler = _MonthlyRotatingFileHandler(
            filename=log_file, backupCount=1, encoding="utf-8"
        )
        dummy = logging.LogRecord(
            name="test",
            level=logging.INFO,
            pathname="",
            lineno=0,
            msg="",
            args=(),
            exc_info=None,
        )
        assert handler.shouldRollover(dummy) == 0
        handler.close()

    def test_date_namer_reorders_suffix(self) -> None:
        """Verify _date_namer reorders the rotation suffix.

        Converts ``path/smartcalc.log.SUFFIX`` to ``path/SUFFIX.log``.
        """
        from utils.logger import _date_namer

        result = _date_namer("/var/log/smartcalc.log.2024-01-15")
        assert result == os.path.join("/var/log", "2024-01-15.log")

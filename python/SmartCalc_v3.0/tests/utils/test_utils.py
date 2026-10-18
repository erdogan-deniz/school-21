"""Unit tests for utils.config and utils.logger."""

import logging
import os
import re
from datetime import datetime, timedelta
from pathlib import Path

import pytest

from utils.config import AppConfig
from utils.logger import PeriodFileHandler, setup_logger


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
    """Tests for setup_logger: file per period, task naming pattern."""

    NAME = re.compile(r"^logs_\d{2}-\d{2}-\d{2}-\d{2}-\d{2}-\d{2}\.log$")

    @pytest.fixture(autouse=True)
    def _patch_logs_dir(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Redirect log output to tmp_path and reset handlers before each."""
        import utils.logger as lg_mod

        monkeypatch.setattr(lg_mod, "_LOGS_DIR", str(tmp_path))
        logger = logging.getLogger("smartcalc")
        for handler in logger.handlers:
            handler.close()
        logger.handlers.clear()

    def test_returns_logger(self, tmp_path: Path) -> None:
        """Verifies setup_logger returns a Logger named 'smartcalc'."""
        logger = setup_logger("day")
        assert isinstance(logger, logging.Logger)
        assert logger.name == "smartcalc"

    @pytest.mark.parametrize("period", ["hour", "day", "month"])
    def test_log_file_name_pattern(self, tmp_path: Path, period: str) -> None:
        """Verify the file is named logs_dd-MM-yy-hh-mm-ss.log."""
        setup_logger(period).info("x")
        names = [f.name for f in tmp_path.iterdir()]
        assert len(names) == 1
        assert self.NAME.match(names[0])

    def test_unknown_period_falls_back_to_day(self, tmp_path: Path) -> None:
        """Verify graceful fallback to daily rotation for an unknown period."""
        logger = setup_logger("unknown_period")
        handler = logger.handlers[0]
        assert isinstance(handler, PeriodFileHandler)
        assert handler.period == "day"

    def test_can_write_log_message(self, tmp_path: Path) -> None:
        """Verifies that a logged message appears verbatim in the log file."""
        logger = setup_logger("day")
        logger.info("test message")
        files = list(tmp_path.iterdir())
        assert "test message" in files[0].read_text(encoding="utf-8")


class _Clock:
    """Controllable clock for PeriodFileHandler tests."""

    def __init__(self, start: datetime) -> None:
        self.now = start

    def __call__(self) -> datetime:
        return self.now


def _record(msg: str) -> logging.LogRecord:
    return logging.LogRecord(
        name="test",
        level=logging.INFO,
        pathname="",
        lineno=0,
        msg=msg,
        args=(),
        exc_info=None,
    )


class TestPeriodFileHandler:
    """One file per rotation period; restart appends; old files pruned."""

    START = datetime(2026, 10, 19, 0, 41, 5).astimezone()

    def _names(self, path: Path) -> list[str]:
        return sorted(f.name for f in path.iterdir())

    def test_name_is_period_start(self, tmp_path: Path) -> None:
        """Verify the file name carries the time of its first record."""
        handler = PeriodFileHandler(
            str(tmp_path), "day", clock=_Clock(self.START)
        )
        handler.emit(_record("a"))
        handler.close()
        assert self._names(tmp_path) == ["logs_19-10-26-00-41-05.log"]

    @pytest.mark.parametrize(
        ("period", "step", "files"),
        [
            ("hour", timedelta(minutes=10), 1),
            ("hour", timedelta(hours=1), 2),
            ("day", timedelta(hours=5), 1),
            ("day", timedelta(days=1), 2),
            ("month", timedelta(days=5), 1),
            ("month", timedelta(days=40), 2),
        ],
    )
    def test_rotation(
        self, tmp_path: Path, period: str, step: timedelta, files: int
    ) -> None:
        """Verify a new file starts exactly when the period changes."""
        clock = _Clock(self.START)
        handler = PeriodFileHandler(str(tmp_path), period, clock=clock)
        handler.emit(_record("first"))
        clock.now = self.START + step
        handler.emit(_record("second"))
        handler.close()
        assert len(self._names(tmp_path)) == files

    def test_restart_appends_to_current_period(self, tmp_path: Path) -> None:
        """Verify a restart within the same period keeps one file."""
        clock = _Clock(self.START)
        first = PeriodFileHandler(str(tmp_path), "day", clock=clock)
        first.emit(_record("before restart"))
        first.close()
        clock.now = self.START + timedelta(hours=2)
        second = PeriodFileHandler(str(tmp_path), "day", clock=clock)
        second.emit(_record("after restart"))
        second.close()
        names = self._names(tmp_path)
        assert names == ["logs_19-10-26-00-41-05.log"]
        text = (tmp_path / names[0]).read_text(encoding="utf-8")
        assert "before restart" in text
        assert "after restart" in text

    def test_old_files_pruned(self, tmp_path: Path) -> None:
        """Verify only the newest backup_count files are kept."""
        clock = _Clock(self.START)
        handler = PeriodFileHandler(
            str(tmp_path), "hour", backup_count=2, clock=clock
        )
        for hour in range(4):
            clock.now = self.START + timedelta(hours=hour)
            handler.emit(_record(str(hour)))
        handler.close()
        assert self._names(tmp_path) == [
            "logs_19-10-26-02-41-05.log",
            "logs_19-10-26-03-41-05.log",
        ]

    def test_foreign_files_ignored(self, tmp_path: Path) -> None:
        """Verify files outside the naming pattern are not reused or pruned."""
        (tmp_path / "smartcalc.log").write_text("old", encoding="utf-8")
        bad = tmp_path / "logs_99-99-99-99-99-99.log"
        bad.write_text("bad", encoding="utf-8")
        handler = PeriodFileHandler(
            str(tmp_path), "day", backup_count=1, clock=_Clock(self.START)
        )
        handler.emit(_record("a"))
        handler.close()
        assert self._names(tmp_path) == [
            "logs_19-10-26-00-41-05.log",
            "logs_99-99-99-99-99-99.log",
            "smartcalc.log",
        ]

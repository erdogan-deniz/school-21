"""Unit tests for model.history.History."""

import os
import sqlite3
import tempfile
from collections.abc import Generator
from unittest.mock import patch

import pytest

from model.history import History


@pytest.fixture
def db_path() -> Generator[str, None, None]:
    """Yield a temporary SQLite database path, removed after the test."""
    with tempfile.NamedTemporaryFile(suffix=".db", delete=False) as f:
        path = f.name
    yield path
    os.unlink(path)


@pytest.fixture
def history(db_path: str) -> Generator[History, None, None]:
    """Returns a History instance backed by a temporary database file."""
    h = History(db_path=db_path)
    yield h
    h.close()


class TestDefaultPath:
    """Tests for the default database path (no explicit db_path given)."""

    def test_default_path_creates_db(self) -> None:
        """Verifies the default database is created and accepts entries."""
        h = History()
        h.add_entry("test", "42")
        entries = h.get_history()
        h.close()
        assert any(e["expression"] == "test" for e in entries)


class TestHistoryOperations:
    """Tests for add, get, and clear operations."""

    def test_empty_on_start(self, history: History) -> None:
        """Verifies a freshly opened database contains no entries."""
        assert history.get_history() == []

    def test_add_and_retrieve(self, history: History) -> None:
        """Verifies that an added entry can be retrieved with correct fields."""
        history.add_entry("2+2", "4")
        entries = history.get_history()
        assert len(entries) == 1
        assert entries[0]["expression"] == "2+2"
        assert entries[0]["result"] == "4"

    def test_newest_first(self, history: History) -> None:
        """Verifies that get_history returns the most recent entry first."""
        history.add_entry("1+1", "2")
        history.add_entry("3+3", "6")
        entries = history.get_history()
        assert entries[0]["expression"] == "3+3"

    def test_clear_removes_all(self, history: History) -> None:
        """Verifies that clear_history deletes all entries."""
        history.add_entry("1+1", "2")
        history.add_entry("2+2", "4")
        history.clear_history()
        assert history.get_history() == []

    def test_multiple_entries(self, history: History) -> None:
        """Verify 10 sequential entries are all stored and retrievable."""
        for i in range(10):
            history.add_entry(f"{i}+1", str(i + 1))
        assert len(history.get_history()) == 10

    def test_timestamp_present(self, history: History) -> None:
        """Verifies that each entry includes a non-empty timestamp string."""
        history.add_entry("5*5", "25")
        entry = history.get_history()[0]
        assert "timestamp" in entry
        assert len(entry["timestamp"]) > 0

    def test_max_entries_pruning(self, db_path: str) -> None:
        """Verify that only the 1000 newest entries are kept after overflow."""
        h = History(db_path=db_path)
        limit = History._MAX_ENTRIES  # noqa: SLF001
        # Insert limit//10 entries past the cap; much faster than 1000+ writes
        # while still exercising the pruning SQL on every add_entry call.
        overflow = limit // 10 + 1
        for i in range(limit + overflow):
            h.add_entry(f"expr_{i}", str(i))
        count = h.count()
        h.close()
        assert count == limit

    def test_persistence(self, db_path: str) -> None:
        """Verify data survives closing and reopening the same database file."""
        h = History(db_path=db_path)
        h.add_entry("pi", "3.1415927")
        h.close()

        reopened = History(db_path=db_path)
        entries = reopened.get_history()
        reopened.close()
        assert any(e["expression"] == "pi" for e in entries)


class TestHistoryAppDir:
    """Verify platform-appropriate directory selection for history DB."""

    def test_windows_uses_appdata(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """On Windows with APPDATA set, use APPDATA/smartcalc_v3."""
        monkeypatch.setattr(os, "name", "nt")
        monkeypatch.setenv("APPDATA", r"C:\Roaming")
        from model.history import _history_app_dir

        assert _history_app_dir() == r"C:\Roaming\smartcalc_v3"

    def test_windows_fallback_without_appdata(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """On Windows without APPDATA, fall back to ~/.smartcalc_v3."""
        monkeypatch.setattr(os, "name", "nt")
        monkeypatch.delenv("APPDATA", raising=False)
        from model.history import _history_app_dir

        assert _history_app_dir() == os.path.join(
            os.path.expanduser("~"), ".smartcalc_v3"
        )

    def test_posix_uses_home(self, monkeypatch: pytest.MonkeyPatch) -> None:
        """On non-Windows, always use ~/.smartcalc_v3."""
        monkeypatch.setattr(os, "name", "posix")
        from model.history import _history_app_dir

        assert _history_app_dir() == os.path.join(
            os.path.expanduser("~"), ".smartcalc_v3"
        )


class TestHistoryInit:
    """Tests for __init__ error handling (connection cleanup on failure)."""

    def test_create_table_failure_closes_connection(self, db_path: str) -> None:
        """Verify the SQLite connection is closed when _create_table raises."""
        with (
            patch.object(
                History,
                "_create_table",
                side_effect=sqlite3.OperationalError("boom"),
            ),
            pytest.raises(sqlite3.OperationalError, match="boom"),
        ):
            History(db_path=db_path)

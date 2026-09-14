"""History model: persistent operation history using SQLite."""

import os
import sqlite3
from datetime import UTC, datetime
from typing import ClassVar

from model.results import HistoryEntry


def _history_app_dir() -> str:
    """Return the platform-appropriate directory for the history database.

    Returns:
        ``%APPDATA%/smartcalc_v3`` on Windows when APPDATA is set,
        ``~/.smartcalc_v3`` everywhere else.

    """
    if os.name == "nt":
        appdata = os.environ.get("APPDATA")
        if appdata:
            return os.path.join(appdata, "smartcalc_v3")
    return os.path.join(os.path.expanduser("~"), ".smartcalc_v3")


class History:
    """Store and retrieve calculator history in a local SQLite database.

    The database file is created at ~/.smartcalc_v3/history.db so it
    persists between application runs.
    """

    _DB_FILENAME: ClassVar[str] = "history.db"
    _APP_DIR: ClassVar[str] = _history_app_dir()
    _MAX_ENTRIES: ClassVar[int] = 1000  # oldest rows pruned after each insert
    _MAX_DISPLAY: ClassVar[int] = 100  # rows returned by get_history()

    def __init__(self, db_path: str | None = None) -> None:
        """Open the database and create the history table if absent.

        Args:
            db_path: Optional custom path to the SQLite database file.
                Defaults to ~/.smartcalc_v3/history.db.

        Raises:
            sqlite3.Error: If the history table cannot be created.

        """
        if db_path is None:
            os.makedirs(self._APP_DIR, exist_ok=True)
            db_path = os.path.join(self._APP_DIR, self._DB_FILENAME)

        self._conn: sqlite3.Connection = sqlite3.connect(db_path)
        self._conn.row_factory = sqlite3.Row
        try:
            self._create_table()
        except sqlite3.Error:
            self._conn.close()
            raise

    def _create_table(self) -> None:
        """Create the history table if it does not exist."""
        self._conn.execute(
            """
            CREATE TABLE IF NOT EXISTS history (
                id        INTEGER PRIMARY KEY AUTOINCREMENT,
                expression TEXT    NOT NULL,
                result     TEXT    NOT NULL,
                timestamp  TEXT    NOT NULL
            )
            """
        )
        self._conn.commit()

    def add_entry(self, expression: str, result: str) -> None:
        """Append a calculation to the history.

        Args:
            expression: The evaluated expression string.
            result: The result string.

        """
        self._conn.execute(
            "INSERT INTO history (expression, result, timestamp) "
            "VALUES (?, ?, ?)",
            (
                expression,
                result,
                datetime.now(tz=UTC).isoformat(timespec="seconds"),
            ),
        )
        self._conn.execute(
            "DELETE FROM history WHERE id NOT IN "
            "(SELECT id FROM history ORDER BY id DESC LIMIT ?)",
            (self._MAX_ENTRIES,),
        )
        self._conn.commit()

    def get_history(self) -> list[HistoryEntry]:
        """Return up to _MAX_DISPLAY most recent entries, newest first.

        Returns:
            List of dicts with keys 'expression', 'result', 'timestamp'.

        """
        cursor = self._conn.execute(
            "SELECT expression, result, timestamp FROM history "
            "ORDER BY id DESC LIMIT ?",
            (self._MAX_DISPLAY,),
        )
        return [
            HistoryEntry(
                expression=row["expression"],
                result=row["result"],
                timestamp=row["timestamp"],
            )
            for row in cursor.fetchall()
        ]

    def count(self) -> int:
        """Return the total number of entries stored in the database."""
        cursor = self._conn.execute("SELECT COUNT(*) FROM history")
        return int(cursor.fetchone()[0])

    def clear_history(self) -> None:
        """Delete all entries from the history table."""
        self._conn.execute("DELETE FROM history")
        self._conn.commit()

    def close(self) -> None:
        """Close the database connection."""
        self._conn.close()

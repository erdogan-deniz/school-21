"""Tests for BaseToolbar and FieldWidget from base_toolbar.py."""

from pytestqt.qtbot import QtBot

from app.widgets.toolbar.base_toolbar import FieldWidget
from app.widgets.toolbar.cave_toolbar import CaveToolbar


class TestCreateGenerateSection:
    """Tests for BaseToolbar.create_generate_section."""

    def test_none_widgets_defaults_to_empty(self, qtbot: QtBot) -> None:
        """Calling create_generate_section without widgets
        covers the widgets=None branch."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        # Calling create_generate_section without widgets
        # → covers the widgets=None branch
        section = tb.create_generate_section("Test Section")
        assert section.title() == "Test Section"


class TestUpdateFilePath:
    """Tests for BaseToolbar.update_file_path."""

    def test_set_real_path(self, qtbot: QtBot) -> None:
        """Setting a real path stores it and shows the filename in the label."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_file_path("/some/dir/maze.txt")
        assert tb.current_file_path == "/some/dir/maze.txt"
        assert "maze.txt" in tb.file_path_label.text()

    def test_clear_path(self, qtbot: QtBot) -> None:
        """Passing an empty string resets current_file_path
        and shows placeholder text."""
        tb = CaveToolbar()
        qtbot.addWidget(tb)
        tb.update_file_path("/some/dir/maze.txt")
        tb.update_file_path("")
        assert tb.current_file_path is None
        assert tb.file_path_label.text() == "No file"


class TestFieldWidget:
    """Tests for FieldWidget — default row/column spinbox values."""

    def test_get_rows_default(self, qtbot: QtBot) -> None:
        """Default row count is at least 1."""
        fw = FieldWidget()
        qtbot.addWidget(fw)
        assert fw.get_rows() >= 1

    def test_get_cols_default(self, qtbot: QtBot) -> None:
        """Default column count is at least 1."""
        fw = FieldWidget()
        qtbot.addWidget(fw)
        assert fw.get_cols() >= 1

"""Tests for Qt widgets: canvas, tabs, containers, and the main window."""

import pytest
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QImage
from PyQt5.QtWidgets import QApplication
from pytestqt.qtbot import QtBot

from app.render.maze_grider import MazeGrider
from app.render.render import MazeRender
from app.widgets.content.cave_canvas import CaveCanvas
from app.widgets.content.cave_tab import CaveTab
from app.widgets.content.content_container import ContentContainer
from app.widgets.content.maze_canvas import MazeCanvas
from app.widgets.content.maze_tab import MazeTab
from app.widgets.main_window import MainWindow
from app.widgets.toolbar.maze_toolbar import MazeToolbar
from app.widgets.toolbar.toolbar_container import ToolbarContainer
from models.field import MazeFieldModel

# ---------------------------------------------------------------------------
# Helper fixture — a real QImage for tests
# ---------------------------------------------------------------------------


@pytest.fixture
def maze_image(qapp: QApplication) -> QImage:
    """Real QImage rendered from a 4×4 MazeFieldModel for display tests."""
    model = MazeFieldModel(
        rows=4,
        cols=4,
        vertical_walls=[[0, 0, 1, 1]] * 4,
        horizontal_walls=[[0, 1, 0, 1]] * 4,
    )
    return MazeRender(MazeGrider(model)).get_image()


# ---------------------------------------------------------------------------
# MazeCanvas
# ---------------------------------------------------------------------------


class TestMazeCanvas:
    """Tests for MazeCanvas — placeholder text, image display,
    and click signals."""

    def test_initial_text(self, qtbot: QtBot) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        assert "No maze" in canvas.text()

    def test_no_image_initially(self, qtbot: QtBot) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        assert canvas.current_image is None

    def test_show_image_sets_pixmap(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        assert canvas.pixmap() is not None
        assert not canvas.pixmap().isNull()

    def test_show_image_clears_text(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        assert canvas.text() == ""

    def test_show_image_stores_reference(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        assert canvas.current_image is maze_image

    def test_click_without_image_no_signal(self, qtbot: QtBot) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show()
        with qtbot.assertNotEmitted(canvas.cell_clicked):
            qtbot.mouseClick(canvas, Qt.LeftButton)

    def test_click_with_image_emits_signal(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show()
        canvas.resize(600, 600)
        canvas.show_image(maze_image)
        with qtbot.waitSignal(canvas.cell_clicked, timeout=500):
            qtbot.mouseClick(canvas, Qt.LeftButton, pos=canvas.rect().center())

    def test_right_click_no_signal(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show()
        canvas.show_image(maze_image)
        with qtbot.assertNotEmitted(canvas.cell_clicked):
            qtbot.mouseClick(canvas, Qt.RightButton)

    def test_resize_with_image_rescales_pixmap(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        from PyQt5.QtCore import QSize
        from PyQt5.QtGui import QResizeEvent

        canvas = MazeCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        canvas.resizeEvent(
            QResizeEvent(QSize(200, 200), canvas.size())
        )
        assert canvas.pixmap() is not None
        assert not canvas.pixmap().isNull()


# ---------------------------------------------------------------------------
# CaveCanvas
# ---------------------------------------------------------------------------


class TestCaveCanvas:
    """Tests for CaveCanvas — placeholder text and image display."""

    def test_initial_text(self, qtbot: QtBot) -> None:
        canvas = CaveCanvas()
        qtbot.addWidget(canvas)
        assert "No cave" in canvas.text()

    def test_no_image_initially(self, qtbot: QtBot) -> None:
        canvas = CaveCanvas()
        qtbot.addWidget(canvas)
        assert canvas.current_image is None

    def test_show_image_sets_pixmap(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = CaveCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        assert canvas.pixmap() is not None
        assert not canvas.pixmap().isNull()

    def test_show_image_clears_text(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        canvas = CaveCanvas()
        qtbot.addWidget(canvas)
        canvas.show_image(maze_image)
        assert canvas.text() == ""


# ---------------------------------------------------------------------------
# MazeTab / CaveTab
# ---------------------------------------------------------------------------


class TestMazeTab:
    """Tests for MazeTab — canvas creation and image delegation."""

    def test_creates_canvas(self, qtbot: QtBot) -> None:
        tab = MazeTab()
        qtbot.addWidget(tab)
        assert isinstance(tab.canvas, MazeCanvas)

    def test_on_maze_rendered_shows_image(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        tab = MazeTab()
        qtbot.addWidget(tab)
        tab.on_maze_rendered(maze_image)
        assert tab.canvas.current_image is maze_image


class TestCaveTab:
    """Tests for CaveTab — canvas creation and image delegation."""

    def test_creates_canvas(self, qtbot: QtBot) -> None:
        tab = CaveTab()
        qtbot.addWidget(tab)
        assert isinstance(tab.canvas, CaveCanvas)

    def test_on_cave_rendered_shows_image(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        tab = CaveTab()
        qtbot.addWidget(tab)
        tab.on_cave_rendered(maze_image)
        assert tab.canvas.current_image is maze_image


# ---------------------------------------------------------------------------
# ContentContainer
# ---------------------------------------------------------------------------


class TestContentContainer:
    """Tests for ContentContainer — tab count, names, and image delegation."""

    def test_has_two_tabs(self, qtbot: QtBot) -> None:
        cc = ContentContainer()
        qtbot.addWidget(cc)
        assert cc.tab_widget.count() == 2

    def test_tab_names(self, qtbot: QtBot) -> None:
        cc = ContentContainer()
        qtbot.addWidget(cc)
        names = [cc.tab_widget.tabText(i) for i in range(cc.tab_widget.count())]
        assert "Maze" in names
        assert "Cave" in names

    def test_on_maze_rendered_delegates(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        cc = ContentContainer()
        qtbot.addWidget(cc)
        cc.on_maze_rendered(maze_image)
        assert cc.maze_tab.canvas.current_image is maze_image

    def test_on_cave_rendered_delegates(
        self, qtbot: QtBot, maze_image: QImage
    ) -> None:
        cc = ContentContainer()
        qtbot.addWidget(cc)
        cc.on_cave_rendered(maze_image)
        assert cc.cave_tab.canvas.current_image is maze_image


# ---------------------------------------------------------------------------
# ToolbarContainer
# ---------------------------------------------------------------------------


class TestToolbarContainer:
    """Tests for ToolbarContainer — toolbar visibility switching and UI sync."""

    def test_maze_toolbar_visible_initially(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        # isHidden() checks the explicit hidden state,
        # ignoring parent visibility
        assert not tc.maze_toolbar.isHidden()

    def test_cave_toolbar_hidden_initially(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        assert tc.cave_toolbar.isHidden()

    def test_switch_to_cave(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.on_tab_changed("Cave")
        assert not tc.cave_toolbar.isHidden()
        assert tc.maze_toolbar.isHidden()

    def test_switch_to_maze(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.on_tab_changed("Cave")
        tc.on_tab_changed("Maze")
        assert not tc.maze_toolbar.isHidden()
        assert tc.cave_toolbar.isHidden()

    def test_unknown_tab_does_not_crash(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        index_before = tc.stack.currentIndex()
        tc.on_tab_changed("UnknownTab")
        assert tc.stack.currentIndex() == index_before

    def test_update_solve_ui(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.update_solve_ui("Click a cell", True)
        assert tc.maze_toolbar.solve_button.isEnabled()

    def test_on_init_chance_sync(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.on_init_chance_sync(70)
        assert tc.cave_toolbar.field_widget.chance_spin.value() == 70

    def test_quit_button_emits_signal(self, qtbot: QtBot) -> None:
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        with qtbot.waitSignal(tc.quit_requested, timeout=500):
            qtbot.mouseClick(tc.maze_toolbar.quit_btn, Qt.LeftButton)

    def test_set_maze_field_size(self, qtbot: QtBot) -> None:
        """set_maze_field_size proxies to maze_toolbar spinboxes."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.set_maze_field_size(12, 8)
        assert tc.maze_toolbar.field_widget.rows_spin.value() == 12
        assert tc.maze_toolbar.field_widget.cols_spin.value() == 8

    def test_set_cave_field_size(self, qtbot: QtBot) -> None:
        """set_cave_field_size proxies to cave_toolbar spinboxes."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.set_cave_field_size(7, 11)
        assert tc.cave_toolbar.field_widget.rows_spin.value() == 7
        assert tc.cave_toolbar.field_widget.cols_spin.value() == 11

    def test_on_cave_auto_play_stopped_resets_button(
        self, qtbot: QtBot
    ) -> None:
        """on_cave_auto_play_stopped resets cave toolbar auto-play button."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.cave_toolbar.playback_widget.on_auto_toggled(True)
        tc.on_cave_auto_play_stopped()
        assert not tc.cave_toolbar.playback_widget.auto_button.isChecked()

    def test_set_cave_playback_enabled(self, qtbot: QtBot) -> None:
        """set_cave_playback_enabled enables/disables cave playback buttons."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.set_cave_playback_enabled(False)
        assert not tc.cave_toolbar.playback_widget.next_button.isEnabled()
        tc.set_cave_playback_enabled(True)
        assert tc.cave_toolbar.playback_widget.next_button.isEnabled()

    def test_update_maze_agent_status(self, qtbot: QtBot) -> None:
        """update_maze_agent_status proxies to maze_toolbar agent label."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.update_maze_agent_status("Training (500 episodes)…")
        assert "Training" in tc.maze_toolbar.agent_status.text()

    def test_set_maze_save_enabled(self, qtbot: QtBot) -> None:
        """set_maze_save_enabled enables/disables maze Save button."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.set_maze_save_enabled(True)
        assert tc.maze_toolbar.save_button.isEnabled()
        tc.set_maze_save_enabled(False)
        assert not tc.maze_toolbar.save_button.isEnabled()

    def test_set_cave_save_enabled(self, qtbot: QtBot) -> None:
        """set_cave_save_enabled enables/disables cave Save button."""
        tc = ToolbarContainer()
        qtbot.addWidget(tc)
        tc.set_cave_save_enabled(True)
        assert tc.cave_toolbar.save_button.isEnabled()
        tc.set_cave_save_enabled(False)
        assert not tc.cave_toolbar.save_button.isEnabled()


# ---------------------------------------------------------------------------
# MazeToolbar
# ---------------------------------------------------------------------------


class TestMazeToolbar:
    """Tests for MazeToolbar — solve/agent button states,
    hint label, and signals."""

    def test_set_solve_ready_enables_buttons(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        tb.set_solve_ready(True)
        assert tb.solve_button.isEnabled()
        assert tb.agent_button.isEnabled()

    def test_set_solve_ready_false_disables(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        tb.set_solve_ready(True)
        tb.set_solve_ready(False)
        assert not tb.solve_button.isEnabled()
        assert not tb.agent_button.isEnabled()

    def test_update_solve_hint(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        tb.update_solve_hint("Choose start")
        assert tb.status_label.text() == "Choose start"

    def test_update_agent_status(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        tb.update_agent_status("Training…")
        assert tb.agent_status.text() == "Training…"

    def test_solve_signal_on_click(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        tb.set_solve_ready(True)
        with qtbot.waitSignal(tb.solve, timeout=500):
            qtbot.mouseClick(tb.solve_button, Qt.LeftButton)

    def test_generate_signal_on_click(self, qtbot: QtBot) -> None:
        tb = MazeToolbar()
        qtbot.addWidget(tb)
        with qtbot.waitSignal(tb.generate, timeout=500):
            qtbot.mouseClick(tb.field_widget.generate_button, Qt.LeftButton)


# ---------------------------------------------------------------------------
# MainWindow
# ---------------------------------------------------------------------------


class TestMainWindow:
    """Tests for MainWindow — construction, title, and layout areas."""

    def test_creates_without_crash(self, qtbot: QtBot) -> None:
        win = MainWindow()
        qtbot.addWidget(win)

    def test_window_title(self, qtbot: QtBot) -> None:
        win = MainWindow()
        qtbot.addWidget(win)
        assert win.windowTitle() == "Maze"

    def test_has_content_area(self, qtbot: QtBot) -> None:
        win = MainWindow()
        qtbot.addWidget(win)
        assert isinstance(win.content_area, ContentContainer)

    def test_has_toolbar_area(self, qtbot: QtBot) -> None:
        win = MainWindow()
        qtbot.addWidget(win)
        assert isinstance(win.toolbar_area, ToolbarContainer)

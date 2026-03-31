"""Container that combines the maze and cave toolbars
into a single widget."""

import logging

from PyQt5.QtCore import Qt, pyqtSignal, pyqtSlot
from PyQt5.QtWidgets import (
    QStackedWidget,
    QVBoxLayout,
    QWidget,
)

from .cave_toolbar import CaveToolbar
from .maze_toolbar import MazeToolbar

logger: logging.Logger = logging.getLogger(__name__)


class ToolbarContainer(QWidget):
    """Container widget that displays MazeToolbar or CaveToolbar
    depending on the active mode."""

    quit_requested = pyqtSignal()

    maze_toolbar: MazeToolbar
    cave_toolbar: CaveToolbar
    stack: QStackedWidget

    # Maze signals
    maze_file_loaded = pyqtSignal(str)

    maze_size_changed = pyqtSignal(int, int)
    maze_generate = pyqtSignal()
    maze_solve = pyqtSignal()
    maze_agent_solve = pyqtSignal(int)
    maze_save = pyqtSignal(str)

    # Cave signals
    cave_file_loaded = pyqtSignal(str)
    cave_file_saved = pyqtSignal(str)

    cave_size_changed = pyqtSignal(int, int)
    cave_init_chance_changed = pyqtSignal(int)
    cave_generate = pyqtSignal()

    cave_birth_limit_changed = pyqtSignal(int)
    cave_death_limit_changed = pyqtSignal(int)

    cave_next_step_requested = pyqtSignal()
    cave_auto_play_toggled = pyqtSignal(bool)
    cave_delay_changed = pyqtSignal(int)

    def __init__(self) -> None:
        """Creates the child toolbars, builds the interface,
        and connects their signals."""
        super().__init__()
        self.maze_toolbar = MazeToolbar()
        self.cave_toolbar = CaveToolbar()
        self.init_ui()
        self.connect_toolbar_signals()

    def init_ui(self) -> None:
        """Builds the vertical layout: title, MazeToolbar,
        CaveToolbar (hidden), and the quit button."""
        layout = QVBoxLayout(self)
        layout.setAlignment(Qt.AlignTop)

        self.stack = QStackedWidget()
        self.stack.addWidget(self.maze_toolbar)  # index 0
        self.stack.addWidget(self.cave_toolbar)  # index 1
        layout.addWidget(self.stack)

    def connect_toolbar_signals(self) -> None:
        """Connects signals from the concrete toolbars."""
        # Quit
        self.maze_toolbar.quit_clicked.connect(self.quit_requested.emit)
        self.cave_toolbar.quit_clicked.connect(self.quit_requested.emit)

        # Maze signals
        self.maze_toolbar.file_loaded.connect(self.maze_file_loaded.emit)
        self.maze_toolbar.generate.connect(self.maze_generate.emit)
        self.maze_toolbar.solve.connect(self.maze_solve.emit)
        self.maze_toolbar.agent_solve.connect(self.maze_agent_solve.emit)
        self.maze_toolbar.file_saved.connect(self.maze_save.emit)
        self.maze_toolbar.size_changed.connect(self.maze_size_changed.emit)

        # Cave signals
        self.cave_toolbar.file_loaded.connect(self.cave_file_loaded.emit)
        self.cave_toolbar.file_saved.connect(self.cave_file_saved.emit)
        self.cave_toolbar.size_changed.connect(self.cave_size_changed.emit)
        self.cave_toolbar.init_chance_changed.connect(
            self.cave_init_chance_changed.emit
        )
        self.cave_toolbar.generate.connect(self.cave_generate.emit)
        self.cave_toolbar.birth_limit_changed.connect(
            self.cave_birth_limit_changed.emit
        )
        self.cave_toolbar.death_limit_changed.connect(
            self.cave_death_limit_changed.emit
        )
        self.cave_toolbar.next_step_requested.connect(
            self.cave_next_step_requested.emit
        )
        self.cave_toolbar.auto_play_toggled.connect(
            self.cave_auto_play_toggled.emit
        )
        self.cave_toolbar.delay_changed.connect(self.cave_delay_changed.emit)

    def on_tab_changed(self, tab_name: str) -> None:
        """Tab change handler."""
        if "maze" in tab_name.lower():
            self.stack.setCurrentIndex(0)
        elif "cave" in tab_name.lower():
            self.stack.setCurrentIndex(1)
        else:
            logger.warning(f"Unknown tab: {tab_name}")

    @pyqtSlot(int)
    def on_init_chance_sync(self, value: int) -> None:
        """Synchronizes the Init chance with the widget."""
        self.cave_toolbar.set_init_chance(value)

    def update_solve_ui(self, hint: str, ready: bool) -> None:
        """Updates the Solve section state in the maze toolbar."""
        self.maze_toolbar.update_solve_hint(hint)
        self.maze_toolbar.set_solve_ready(ready)

    def set_maze_field_size(self, rows: int, cols: int) -> None:
        """Updates the maze field spinboxes."""
        self.maze_toolbar.set_field_size(rows, cols)

    def set_cave_field_size(self, rows: int, cols: int) -> None:
        """Updates the cave field spinboxes."""
        self.cave_toolbar.set_field_size(rows, cols)

    def on_cave_auto_play_stopped(self) -> None:
        """Resets the Auto Play button when auto play stops automatically."""
        self.cave_toolbar.reset_auto_play()

    def set_cave_playback_enabled(self, enabled: bool) -> None:
        """Enables or disables the cave playback buttons."""
        self.cave_toolbar.set_playback_enabled(enabled)

    def update_maze_agent_status(self, text: str) -> None:
        """Updates the agent training status label in the maze toolbar."""
        self.maze_toolbar.update_agent_status(text)

    def set_maze_save_enabled(self, enabled: bool) -> None:
        """Enables or disables the Save Maze button."""
        self.maze_toolbar.set_save_enabled(enabled)

    def set_cave_save_enabled(self, enabled: bool) -> None:
        """Enables or disables the Save Cave button."""
        self.cave_toolbar.set_save_enabled(enabled)

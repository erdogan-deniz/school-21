"""Main application window — layout of the toolbar, content area, and status
bar."""

from PyQt5.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QMessageBox,
    QWidget,
)

from ..controller.app_controller import AppController
from .content.content_container import ContentContainer
from .toolbar.toolbar_container import ToolbarContainer


class MainWindow(QMainWindow):
    """Main application window.

    Combines the toolbar and the content area.
    """

    app_controller: AppController
    content_area: ContentContainer
    toolbar_area: ToolbarContainer

    def __init__(self) -> None:
        """Initializes the controller, UI, and connects all signals."""
        super().__init__()
        self.app_controller = AppController()
        self.init_ui()
        self.connect_signals()

    def init_ui(self) -> None:
        """UI initialization."""
        self.setWindowTitle("Maze")
        self.resize(1000, 500)
        primary = QApplication.primaryScreen()
        if primary is not None:
            geo = primary.availableGeometry()
            self.move(
                geo.x() + (geo.width() - self.width()) // 2,
                geo.y() + (geo.height() - self.height()) // 2,
            )

        central_widget = QWidget()
        central_widget.setStyleSheet("background-color: #FAF6F0;")
        self.setCentralWidget(central_widget)
        main_layout = QHBoxLayout(central_widget)

        self.content_area = ContentContainer()
        self.toolbar_area = ToolbarContainer()
        main_layout.addWidget(self.content_area, 2)
        main_layout.addWidget(self.toolbar_area, 2)

    def connect_signals(self) -> None:
        """Connects all signals through the central controller."""
        self._connect_mode_signals()
        self._connect_maze_signals()
        self._connect_cave_signals()
        self._connect_app_signals()

    def _connect_mode_signals(self) -> None:
        """Tab switching ↔ controller ↔ toolbar panel."""
        self.content_area.tab_changed.connect(self.app_controller.switch_mode)
        self.app_controller.show_maze_toolbar.connect(
            lambda: self.toolbar_area.on_tab_changed("Maze")
        )
        self.app_controller.show_cave_toolbar.connect(
            lambda: self.toolbar_area.on_tab_changed("Cave")
        )

    def _connect_maze_signals(self) -> None:
        """Maze toolbar, rendering, save, and solve connections."""
        self.toolbar_area.maze_file_loaded.connect(
            self.app_controller.on_maze_file_selected
        )
        self.app_controller.size_changed.connect(
            self.toolbar_area.set_maze_field_size
        )
        self.toolbar_area.maze_size_changed.connect(
            self.app_controller.on_size_changed
        )
        self.toolbar_area.maze_generate.connect(
            self.app_controller.on_generate_maze
        )
        self.app_controller.maze_rendered.connect(
            self.content_area.on_maze_rendered
        )
        self.app_controller.maze_rendered.connect(
            lambda _: self.toolbar_area.set_maze_save_enabled(True)
        )
        self.toolbar_area.maze_save.connect(self.app_controller.on_save_maze)
        self.content_area.canvas_cell_clicked.connect(
            self.app_controller.on_canvas_click
        )
        self.toolbar_area.maze_solve.connect(self.app_controller.on_solve_maze)
        self.toolbar_area.maze_agent_solve.connect(
            self.app_controller.on_agent_solve
        )
        self.app_controller.agent_status_updated.connect(
            self.toolbar_area.update_maze_agent_status
        )
        self.app_controller.solve_ui_updated.connect(
            self.toolbar_area.update_solve_ui
        )

    def _connect_cave_signals(self) -> None:
        """Cave toolbar, rendering, and playback connections."""
        self.toolbar_area.cave_file_loaded.connect(
            self.app_controller.on_cave_file_selected
        )
        self.toolbar_area.cave_file_saved.connect(
            self.app_controller.on_cave_save_requested
        )
        self.app_controller.cave_size_changed.connect(
            self.toolbar_area.set_cave_field_size
        )
        self.toolbar_area.cave_size_changed.connect(
            self.app_controller.on_size_changed
        )
        self.toolbar_area.cave_generate.connect(
            self.app_controller.on_generate_cave
        )
        self.toolbar_area.cave_init_chance_changed.connect(
            self.app_controller.on_init_chance_changed
        )
        self.app_controller.init_chance_changed.connect(
            self.toolbar_area.on_init_chance_sync
        )
        self.toolbar_area.cave_birth_limit_changed.connect(
            self.app_controller.on_birth_limit_changed
        )
        self.toolbar_area.cave_death_limit_changed.connect(
            self.app_controller.on_death_limit_changed
        )
        self.toolbar_area.cave_next_step_requested.connect(
            self.app_controller.on_cave_next_step
        )
        self.toolbar_area.cave_auto_play_toggled.connect(
            self.app_controller.on_auto_play_toggled
        )
        self.toolbar_area.cave_delay_changed.connect(
            self.app_controller.on_delay_changed
        )
        self.app_controller.cave_auto_play_stopped.connect(
            self.toolbar_area.on_cave_auto_play_stopped
        )
        self.app_controller.cave_playback_enabled.connect(
            self.toolbar_area.set_cave_playback_enabled
        )
        self.app_controller.cave_rendered.connect(
            self.content_area.on_cave_rendered
        )
        self.app_controller.cave_rendered.connect(
            lambda _: self.toolbar_area.set_cave_save_enabled(True)
        )

    def _connect_app_signals(self) -> None:
        """Application-level signals: errors and quit."""
        self.app_controller.error_occurred.connect(self._show_error)
        self.toolbar_area.quit_requested.connect(self.on_quit_clicked)

    def _show_error(self, message: str) -> None:
        """Displays a dialog box with an error message.

        Args:
            message: Error text to be shown to the user.
        """
        QMessageBox.warning(self, "Error", message)

    def on_quit_clicked(self) -> None:
        """Shows a confirmation dialog; calls QApplication.quit() if
        confirmed."""
        reply = QMessageBox.question(
            self,
            "Quit",
            "Are you sure you want to quit?",
            QMessageBox.Yes | QMessageBox.No,
            QMessageBox.No,
        )
        if reply == QMessageBox.Yes:
            QApplication.quit()

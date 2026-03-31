"""Content area container with maze and cave tabs."""

import logging

from PyQt5.QtCore import pyqtSignal, pyqtSlot
from PyQt5.QtGui import QImage
from PyQt5.QtWidgets import QTabWidget, QVBoxLayout, QWidget

from .cave_tab import CaveTab
from .maze_tab import MazeTab

logger: logging.Logger = logging.getLogger(__name__)


class ContentContainer(QWidget):
    """Content area with tabs."""

    tab_changed = pyqtSignal(str)  # emitted with tab name on switch
    canvas_cell_clicked = pyqtSignal(int, int)  # forwarded from MazeCanvas

    maze_tab: MazeTab
    cave_tab: CaveTab
    tab_widget: QTabWidget

    def __init__(self) -> None:
        """Creates the maze and cave tabs, then builds the UI."""
        super().__init__()
        self.maze_tab = MazeTab()
        self.cave_tab = CaveTab()
        self.init_ui()

    def init_ui(self) -> None:
        """Assembles the layout: creates QTabWidget and adds the tabs."""
        layout = QVBoxLayout(self)

        self.tab_widget = QTabWidget()
        self.tab_widget.addTab(self.maze_tab, "Maze")
        self.tab_widget.addTab(self.cave_tab, "Cave")
        self.tab_widget.currentChanged.connect(
            lambda index: self.tab_changed.emit(self.tab_widget.tabText(index))
        )

        layout.addWidget(self.tab_widget)

        self.maze_tab.canvas.cell_clicked.connect(self.canvas_cell_clicked)

    @pyqtSlot(QImage)
    def on_maze_rendered(self, image: QImage) -> None:
        """Receives the finished maze image."""
        logger.debug("Maze rendered")
        self.maze_tab.on_maze_rendered(image)

    @pyqtSlot(QImage)
    def on_cave_rendered(self, image: QImage) -> None:
        """Receives the finished cave image."""
        logger.debug("Cave rendered")
        self.cave_tab.on_cave_rendered(image)

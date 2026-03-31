"""Maze tab — places MazeCanvas in the centre of the layout."""

from PyQt5.QtCore import pyqtSlot
from PyQt5.QtGui import QImage
from PyQt5.QtWidgets import QVBoxLayout, QWidget

from .maze_canvas import MazeCanvas


class MazeTab(QWidget):
    """Tab for working with mazes."""

    canvas: MazeCanvas

    def __init__(self) -> None:
        """Creates the tab and initializes the UI with the maze canvas."""
        super().__init__()
        self.init_ui()

    def init_ui(self) -> None:
        """Creates a vertical layout and places MazeCanvas in the centre."""
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)

        self.canvas = MazeCanvas()
        layout.addWidget(self.canvas)

    @pyqtSlot(QImage)
    def on_maze_rendered(self, image: QImage) -> None:
        """Displays the finished image."""
        self.canvas.show_image(image)

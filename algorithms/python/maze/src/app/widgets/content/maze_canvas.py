"""Canvas widget for displaying the maze with mouse-click support."""

from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5.QtGui import QMouseEvent
from PyQt5.QtWidgets import QWidget

from app.widgets.content.base_canvas import BaseCanvas


class MazeCanvas(BaseCanvas):
    """
    Widget for displaying the maze.
    Supports mouse clicks: emits pixel coordinates in the
    coordinate system of the source image (500×500).
    """

    cell_clicked = pyqtSignal(int, int)  # img_x, img_y

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__("No maze", parent)
        self.setCursor(Qt.CrossCursor)

    def mousePressEvent(self, event: "QMouseEvent | None") -> None:
        """Handles a left mouse click and emits a signal with coordinates.

        Converts screen click coordinates into pixel coordinates of the
        source image and emits the ``cell_clicked(img_x, img_y)`` signal.
        Clicks outside the displayed pixmap are ignored.

        Args:
            event: Mouse button press event.
        """
        if (
            event is None
            or event.button() != Qt.LeftButton
            or self.current_image is None
        ):
            return
        pm = self.pixmap()
        if pm is None:
            return  # pragma: no cover

        # Pixmap offset inside QLabel (AlignCenter)
        offset_x = (self.width() - pm.width()) / 2
        offset_y = (self.height() - pm.height()) / 2

        pm_x = event.x() - offset_x
        pm_y = event.y() - offset_y

        if not (0 <= pm_x < pm.width() and 0 <= pm_y < pm.height()):
            return  # pragma: no cover

        # From pixmap coordinates to source image coordinates
        img_x = int(pm_x * self.current_image.width() / pm.width())
        img_y = int(pm_y * self.current_image.height() / pm.height())
        self.cell_clicked.emit(img_x, img_y)

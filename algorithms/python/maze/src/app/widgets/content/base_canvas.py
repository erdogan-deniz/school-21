"""Base canvas widget for displaying field images."""

from PyQt5.QtCore import QSize, Qt
from PyQt5.QtGui import QImage, QPixmap, QResizeEvent
from PyQt5.QtWidgets import QLabel, QWidget

from utils.config import CANVAS_HEIGHT, CANVAS_WIDTH


class BaseCanvas(QLabel):
    """Base widget for displaying a field image (maze or cave).

    Handles image display, scaling on resize, and placeholder text.
    Subclasses add interaction (e.g. mouse clicks).
    """

    current_image: QImage | None

    def __init__(self, placeholder: str, parent: QWidget | None = None) -> None:
        """Initializes the canvas with alignment, minimum size,
        and placeholder text.

        Args:
            placeholder: Text shown when no image is loaded.
            parent: Parent Qt widget.
        """
        super().__init__(parent)
        self.setAlignment(Qt.AlignCenter)
        self.setMinimumSize(QSize(CANVAS_WIDTH, CANVAS_HEIGHT))
        self.setSizePolicy(
            self.sizePolicy().Expanding,
            self.sizePolicy().Expanding,
        )
        self.current_image: QImage | None = None
        self.setText(placeholder)

    def show_image(self, image: QImage) -> None:
        """Displays the field image."""
        self.current_image = image
        self._update_pixmap()
        self.setText("")

    def resizeEvent(self, event: QResizeEvent | None) -> None:
        """Rescales the image when the widget is resized."""
        if event is not None:
            super().resizeEvent(event)
        if self.current_image is not None:
            self._update_pixmap()

    def _update_pixmap(self) -> None:
        """Scales the current image to fit the widget size."""
        assert self.current_image is not None
        pixmap = QPixmap.fromImage(self.current_image)
        scaled_pixmap = pixmap.scaled(
            self.width(),
            self.height(),
            Qt.KeepAspectRatio,
            Qt.SmoothTransformation,
        )
        self.setPixmap(scaled_pixmap)

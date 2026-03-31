"""Canvas widget for displaying the cave map."""

from PyQt5.QtWidgets import QWidget

from app.widgets.content.base_canvas import BaseCanvas


class CaveCanvas(BaseCanvas):
    """Widget for displaying the cave."""

    def __init__(self, parent: QWidget | None = None) -> None:
        super().__init__("No cave", parent)

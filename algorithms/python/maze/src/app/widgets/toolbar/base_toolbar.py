"""Base classes for toolbars: BaseToolbar and FieldWidget."""

import logging
import os

from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5.QtWidgets import (
    QFileDialog,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QSpinBox,
    QVBoxLayout,
    QWidget,
)

from utils.config import DEFAULT_N_COLS, DEFAULT_N_ROWS, MAX_COLS, MAX_ROWS
from utils.paths import ProjectPaths

logger: logging.Logger = logging.getLogger(__name__)


def create_group_box_section(title: str, widgets: list[QWidget]) -> QGroupBox:
    """Creates a titled QGroupBox with a vertical layout containing ``widgets``.

    Args:
        title: Title text shown on the group box border.
        widgets: Widgets to place inside the group, top to bottom.

    Returns:
        A fully assembled QGroupBox ready to be added to a parent layout.
    """
    group = QGroupBox(title)
    layout = QVBoxLayout(group)
    for widget in widgets:
        layout.addWidget(widget)
    return group


class BaseToolbar(QWidget):
    """Base class for Maze or Cave control panels."""

    # Signals for file load/save
    file_loaded = pyqtSignal(str)  # passes the file path
    file_saved = pyqtSignal(str)
    quit_clicked = pyqtSignal()

    layout: QVBoxLayout  # type: ignore[assignment]
    title_label: QLabel
    quit_btn: QPushButton
    load_button: QPushButton
    save_button: QPushButton
    file_path_label: QLabel
    current_file_path: str | None

    def __init__(self, parent: QWidget | None = None) -> None:
        """Initializes the base toolbar: layout, title label, init_ui().

        Args:
            parent: Parent Qt widget.
        """
        super().__init__(parent)
        self.current_file_path: str | None = None
        self.layout = QVBoxLayout(self)
        self.layout.setAlignment(Qt.AlignTop)

        self.title_label = QLabel(self.get_title())
        self.title_label.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.title_label)

        self.init_ui()

        self.quit_btn = QPushButton("Quit")
        self.quit_btn.clicked.connect(self.quit_clicked.emit)
        self.layout.addWidget(self.quit_btn)

    def get_title(self) -> str:
        """Returns the panel title (can be overridden)."""
        return "Toolbar"  # pragma: no cover

    def init_ui(self) -> None:  # pragma: no cover
        """UI initialization (must be overridden)."""
        raise NotImplementedError("Subclasses must implement init_ui()")

    def create_file_section(
        self,
        load_text: str = "Load",
        save_text: str = "Save",
        section_title: str = "File",
    ) -> QGroupBox:
        """Creates a section with Load and Save buttons."""
        group = QGroupBox(section_title)
        layout = QVBoxLayout(group)
        buttons_layout = QHBoxLayout()

        self.load_button = QPushButton(load_text)
        buttons_layout.addWidget(self.load_button)

        self.save_button = QPushButton(save_text)
        buttons_layout.addWidget(self.save_button)

        self.file_path_label = QLabel("No file")
        self.file_path_label.setWordWrap(True)

        layout.addLayout(buttons_layout)
        layout.addWidget(self.file_path_label)

        return group

    def create_generate_section(
        self,
        section_title: str = "Generate",
        widgets: list[QWidget] | None = None,
    ) -> QGroupBox:
        """Creates a generation section — a QGroupBox with widgets.

        Args:
            section_title: Group box title.
            widgets: List of widgets added to the group vertically.

        Returns:
            A ready QGroupBox with the widgets placed inside.
        """
        if widgets is None:
            widgets = []
        return create_group_box_section(section_title, widgets)

    # ------------------------------------------------------------------
    # Template methods — overridden in subclasses
    # ------------------------------------------------------------------

    def _get_default_dir(self) -> str:
        """Returns the default directory for file dialogs."""
        return str(ProjectPaths().get_maze_data_dir())  # pragma: no cover

    def _get_load_title(self) -> str:
        """Returns the title of the file load dialog."""
        return "Select File"  # pragma: no cover

    def _get_save_title(self) -> str:
        """Returns the title of the file save dialog."""
        return "Save File As"  # pragma: no cover

    def _on_after_load(self, file_path: str) -> None:
        """Hook called after the load dialog is closed.

        Overridden in subclasses to add type-specific logic.

        Args:
            file_path: selected path (empty string if nothing was selected).
        """

    # ------------------------------------------------------------------
    # Common file operation handlers
    # ------------------------------------------------------------------

    def on_load_clicked(self) -> None:
        """Opens the file load dialog and emits file_loaded."""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            self._get_load_title(),
            self._get_default_dir(),
            "Text files (*.txt);;All files (*.*)",
        )
        if file_path:
            self.update_file_path(file_path)
            logger.debug("Load from: %s", file_path)
            self.file_loaded.emit(file_path)
        self._on_after_load(file_path)

    def on_save_clicked(self) -> None:
        """Opens the file save dialog and emits file_saved."""
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            self._get_save_title(),
            self._get_default_dir(),
            "Text files (*.txt);;All files (*.*)",
        )
        if file_path:
            self.update_file_path(file_path)
            logger.debug("Save to: %s", file_path)
            self.file_saved.emit(file_path)

    def update_file_path(self, file_path: str) -> None:
        """Updates the displayed file path."""
        if hasattr(self, "file_path_label"):
            if file_path:
                filename = os.path.basename(file_path)
                self.file_path_label.setText(filename)
                self.file_path_label.setToolTip(file_path)
                self.current_file_path = file_path
            else:
                self.file_path_label.setText("No file")
                self.file_path_label.setToolTip("")
                self.current_file_path = None


class FieldWidget(QGroupBox):
    """Widget for configuring the field dimensions."""

    rows_changed = pyqtSignal(int)
    cols_changed = pyqtSignal(int)

    main_layout: QVBoxLayout
    rows_layout: QHBoxLayout
    rows_label: QLabel
    rows_spin: QSpinBox
    cols_layout: QHBoxLayout
    cols_label: QLabel
    cols_spin: QSpinBox
    generate_button: QPushButton

    def __init__(
        self, title: str = "Size", parent: QWidget | None = None
    ) -> None:
        """Initializes the field size widget and builds the interface.

        Args:
            title: Group box title.
            parent: Parent Qt widget.
        """
        super().__init__(title, parent)
        self.init_ui()

    def init_ui(self) -> None:
        """Creates the rows and columns spinboxes and places them in the
        layout."""
        self.main_layout = QVBoxLayout(self)

        self.rows_layout = QHBoxLayout()
        self.rows_label = QLabel("Rows:")
        self.rows_spin = QSpinBox()
        self.rows_spin.setRange(1, MAX_ROWS)
        self.rows_spin.setValue(DEFAULT_N_ROWS)
        self.rows_spin.valueChanged.connect(self.rows_changed.emit)

        self.rows_layout.addWidget(self.rows_label)
        self.rows_layout.addWidget(self.rows_spin)

        self.cols_layout = QHBoxLayout()
        self.cols_label = QLabel("Columns:")
        self.cols_spin = QSpinBox()
        self.cols_spin.setRange(1, MAX_COLS)
        self.cols_spin.setValue(DEFAULT_N_COLS)
        self.cols_spin.valueChanged.connect(self.cols_changed.emit)

        self.cols_layout.addWidget(self.cols_label)
        self.cols_layout.addWidget(self.cols_spin)

        self.main_layout.addLayout(self.rows_layout)
        self.main_layout.addLayout(self.cols_layout)

    def add_generate_button(self) -> None:
        """Adds a 'Generate' button."""
        self.generate_button = QPushButton("Generate")
        self.main_layout.addWidget(self.generate_button)

    def set_field_size(self, rows: int, cols: int) -> None:
        """Sets rows/cols spinbox values without triggering signals.

        Args:
            rows: New row count.
            cols: New column count.
        """
        self.rows_spin.blockSignals(True)
        self.cols_spin.blockSignals(True)
        self.rows_spin.setValue(rows)
        self.cols_spin.setValue(cols)
        self.rows_spin.blockSignals(False)
        self.cols_spin.blockSignals(False)

    def get_rows(self) -> int:
        """Returns the current number of rows."""
        return self.rows_spin.value()

    def get_cols(self) -> int:
        """Returns the current number of columns."""
        return self.cols_spin.value()

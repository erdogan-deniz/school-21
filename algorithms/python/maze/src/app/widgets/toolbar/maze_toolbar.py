"""Toolbar for working with the maze:
generation, load/save, and solving."""

import logging

from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5.QtWidgets import QHBoxLayout, QLabel, QPushButton, QSpinBox, QWidget

from app.widgets.toolbar.base_toolbar import FieldWidget
from utils.paths import ProjectPaths

from .base_toolbar import BaseToolbar

logger: logging.Logger = logging.getLogger(__name__)


class MazeToolbar(BaseToolbar):
    """Toolbar for mazes."""

    size_changed = pyqtSignal(int, int)
    generate = pyqtSignal()
    solve = pyqtSignal()
    agent_solve = pyqtSignal(int)  # episodes

    field_widget: "MazeFieldWidget"
    status_label: QLabel
    solve_button: QPushButton
    episodes_spin: QSpinBox
    agent_button: QPushButton
    agent_status: QLabel

    def get_title(self) -> str:
        """Returns the maze panel title."""
        return "Menu"

    def _get_default_dir(self) -> str:
        """Directory containing maze files."""
        return str(ProjectPaths().get_maze_data_dir())

    def _get_load_title(self) -> str:
        """Title for the maze file open dialog."""
        return "Select Maze File"

    def _get_save_title(self) -> str:
        """Title for the maze file save dialog."""
        return "Save Maze As"

    def init_ui(self) -> None:
        """Builds the interface: file section, generation section,
        solution (BFS) section, and agent (Q-learning) section."""
        file_section = self.create_file_section(
            load_text="Load Maze",
            save_text="Save Maze",
            section_title="File",
        )
        self.load_button.clicked.connect(self.on_load_clicked)
        self.save_button.clicked.connect(self.on_save_clicked)
        self.save_button.setEnabled(False)
        self.layout.addWidget(file_section)

        self.field_widget = MazeFieldWidget(title="Field")
        self.field_widget.generate_button.clicked.connect(
            self.on_generate_clicked
        )
        self.layout.addWidget(self.field_widget)

        self.connect_generation_signals()

        self.status_label = QLabel("Load or generate field")
        self.status_label.setWordWrap(True)
        self.status_label.setAlignment(Qt.AlignCenter)
        self.status_label.setStyleSheet(
            "border: 1px solid #222222; border-radius: 4px; padding: 4px;"
            "font-weight: bold; text-transform: uppercase; letter-spacing: 1px;"
        )
        self.layout.addWidget(self.status_label)

        self.solve_button = QPushButton("Solve")
        self.solve_button.setEnabled(False)
        solve_section = self.create_generate_section(
            "Algorithm", [self.solve_button]
        )
        self.solve_button.clicked.connect(self.solve.emit)
        self.layout.addWidget(solve_section)

        self.episodes_spin = QSpinBox()
        self.episodes_spin.setRange(100, 20000)
        self.episodes_spin.setSingleStep(500)
        self.episodes_spin.setValue(1000)
        episodes_row = QWidget()
        episodes_layout = QHBoxLayout(episodes_row)
        episodes_layout.setContentsMargins(0, 0, 0, 0)
        episodes_layout.addWidget(QLabel("Episodes:"))
        episodes_layout.addWidget(self.episodes_spin)
        self.agent_button = QPushButton("Solve")
        self.agent_button.setEnabled(False)
        self.agent_status = QLabel("")
        self.agent_status.setWordWrap(True)
        self.agent_status.hide()
        agent_section = self.create_generate_section(
            "Agent",
            [episodes_row, self.agent_button, self.agent_status],
        )
        self.agent_button.clicked.connect(
            lambda: self.agent_solve.emit(self.episodes_spin.value())
        )
        self.layout.addWidget(agent_section)

        self.layout.addStretch()

    def connect_generation_signals(self) -> None:
        """All signals from the generation widget."""
        self.field_widget.rows_changed.connect(
            lambda v: self.size_changed.emit(v, self.field_widget.get_cols())
        )
        self.field_widget.cols_changed.connect(
            lambda v: self.size_changed.emit(self.field_widget.get_rows(), v)
        )

    def _on_after_load(self, file_path: str) -> None:
        """Clears the agent status label after a maze file is loaded."""
        if file_path:
            self.update_agent_status("")

    def on_generate_clicked(self) -> None:
        """Generate button handler."""
        logger.debug("Generate maze clicked")
        self.update_file_path("")
        self.update_agent_status("")
        self.generate.emit()

    def set_field_size(self, rows: int, cols: int) -> None:
        """Updates the spinboxes without triggering size_changed signal."""
        self.field_widget.set_field_size(rows, cols)

    def set_save_enabled(self, enabled: bool) -> None:
        """Enables or disables the Save Maze button."""
        self.save_button.setEnabled(enabled)

    def set_solve_ready(self, ready: bool) -> None:
        """Enables or disables the «Solve (BFS)» and
        «Train & Solve (Agent)» buttons.

        Args:
            ready: If True, the buttons become active.
        """
        self.solve_button.setEnabled(ready)
        self.agent_button.setEnabled(ready)

    def update_solve_hint(self, text: str) -> None:
        """Updates the shared status hint text."""
        self.status_label.setText(text)

    def update_agent_status(self, text: str) -> None:
        """Updates the agent status text."""
        self.agent_status.setText(text)
        self.agent_status.setVisible(bool(text))


class MazeFieldWidget(FieldWidget):
    """Maze field size configuration widget with a Generate button."""

    def __init__(
        self, title: str = "Maze Field", parent: QWidget | None = None
    ) -> None:
        """Initializes the widget and adds a «Generate» button.

        Args:
            title: Group box title.
            parent: Parent Qt widget.
        """
        super().__init__(title, parent)
        self.add_generate_button()

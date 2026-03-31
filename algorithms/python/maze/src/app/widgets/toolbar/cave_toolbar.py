"""Toolbar for working with the cave: generation,
cellular automaton evolution, and step-by-step playback."""

import logging

from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import (
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QSpinBox,
    QVBoxLayout,
    QWidget,
)

from utils.config import (
    DEFAULT_BIRTH_LIMIT,
    DEFAULT_DEATH_LIMIT,
    DEFAULT_INIT_CHANCE,
)
from utils.paths import ProjectPaths

from .base_toolbar import BaseToolbar, FieldWidget

logger: logging.Logger = logging.getLogger(__name__)


class CaveToolbar(BaseToolbar):
    """Toolbar for caves."""

    size_changed = pyqtSignal(int, int)
    field_widget: "CaveFieldWidget"
    evolution_widget: "EvolutionWidget"
    playback_widget: "PlaybackWidget"
    init_chance_changed = pyqtSignal(int)
    generate = pyqtSignal()

    birth_limit_changed = pyqtSignal(int)
    death_limit_changed = pyqtSignal(int)

    next_step_requested = pyqtSignal()
    auto_play_toggled = pyqtSignal(bool)
    delay_changed = pyqtSignal(int)

    def get_title(self) -> str:
        """Returns the cave panel title."""
        return "Menu"

    def _get_default_dir(self) -> str:
        """Directory containing cave files."""
        return str(ProjectPaths().get_cave_data_dir())

    def _get_load_title(self) -> str:
        """Title for the cave file open dialog."""
        return "Select Cave File"

    def _get_save_title(self) -> str:
        """Title for the cave file save dialog."""
        return "Save Cave As"

    def _on_after_load(self, file_path: str) -> None:
        """Resets the displayed evolution limits after loading a file."""
        if not file_path:
            return
        self.update_birth_limit_display(DEFAULT_BIRTH_LIMIT)
        self.update_death_limit_display(DEFAULT_DEATH_LIMIT)

    def init_ui(self) -> None:
        """Builds the interface: file section, field section,
        evolution parameters section, and playback section."""
        file_section = self.create_file_section(
            load_text="Load Cave",
            save_text="Save Cave",
            section_title="File",
        )
        self.load_button.clicked.connect(self.on_load_clicked)
        self.save_button.clicked.connect(self.on_save_clicked)
        self.save_button.setEnabled(False)
        self.layout.addWidget(file_section)

        self.field_widget = CaveFieldWidget(title="Field")
        self.field_widget.generate_button.clicked.connect(
            self.on_generate_clicked
        )
        self.layout.addWidget(self.field_widget)

        self.evolution_widget = EvolutionWidget("Evolution")
        self.layout.addWidget(self.evolution_widget)

        self.playback_widget = PlaybackWidget("Animation")
        self.layout.addWidget(self.playback_widget)

        self.connect_generation_signals()

        self.layout.addStretch()

    def connect_generation_signals(self) -> None:
        """Connects signals from child widgets: field size,
        init chance, evolution limits, and playback."""
        self.field_widget.rows_changed.connect(
            lambda v: self.size_changed.emit(v, self.field_widget.get_cols())
        )
        self.field_widget.cols_changed.connect(
            lambda v: self.size_changed.emit(self.field_widget.get_rows(), v)
        )
        self.field_widget.init_chance_changed.connect(
            self.init_chance_changed.emit
        )

        self.evolution_widget.birth_limit_changed.connect(
            self.birth_limit_changed.emit
        )
        self.evolution_widget.death_limit_changed.connect(
            self.death_limit_changed.emit
        )

        self.playback_widget.next_step_clicked.connect(
            self.next_step_requested.emit
        )
        self.playback_widget.auto_play_toggled.connect(
            self.auto_play_toggled.emit
        )
        self.playback_widget.delay_changed.connect(self.delay_changed.emit)

    def on_generate_clicked(self) -> None:
        """Generate button handler."""
        logger.debug("Generate cave clicked")
        self.update_file_path("")
        self.auto_play_toggled.emit(False)
        self.generate.emit()

    def reset_auto_play(self) -> None:
        """Resets the playback widget to stopped state."""
        self.playback_widget.reset_auto_button()

    def set_playback_enabled(self, enabled: bool) -> None:
        """Enables or disables playback controls."""
        self.playback_widget.set_playback_enabled(enabled)

    def set_field_size(self, rows: int, cols: int) -> None:
        """Updates the spinboxes without triggering size_changed signal."""
        self.field_widget.set_field_size(rows, cols)

    def set_save_enabled(self, enabled: bool) -> None:
        """Enables or disables the Save Cave button."""
        self.save_button.setEnabled(enabled)

    def set_init_chance(self, value: int) -> None:
        """Sets the Init chance value in the widget."""
        if self.field_widget:
            self.field_widget.set_init_chance(value)

    def update_birth_limit_display(self, value: int) -> None:
        """Updates the Birth limit display without emitting a signal."""
        if self.evolution_widget:
            self.evolution_widget.update_birth_limit_silent(value)

    def update_death_limit_display(self, value: int) -> None:
        """Updates the Death limit display without emitting a signal."""
        if self.evolution_widget:
            self.evolution_widget.update_death_limit_silent(value)


class CaveFieldWidget(FieldWidget):
    """Widget for configuring the cave field."""

    init_chance_changed = pyqtSignal(int)

    chance_layout: QHBoxLayout
    chance_label: QLabel
    chance_spin: QSpinBox

    def __init__(
        self, title: str = "Cave Field", parent: QWidget | None = None
    ) -> None:
        """Initializes the cave field widget, adds a spinbox
        for the init chance, and a Generate button.

        Args:
            title: Group box title.
            parent: Parent Qt widget.
        """
        super().__init__(title, parent)
        self.init_init_chance()
        super().add_generate_button()

    def init_init_chance(self) -> None:
        """Creates the «Init chance %» spinbox (0–100)
        and adds it to the main layout."""
        self.chance_layout = QHBoxLayout()
        self.chance_label = QLabel("Initialization chance:")
        self.chance_spin = QSpinBox()
        self.chance_spin.setRange(0, 100)
        self.chance_spin.setValue(DEFAULT_INIT_CHANCE)
        self.chance_spin.setSuffix(" %")
        self.chance_spin.valueChanged.connect(self.init_chance_changed.emit)

        self.chance_layout.addWidget(self.chance_label)
        self.chance_layout.addWidget(self.chance_spin)

        self.main_layout.addLayout(self.chance_layout)

    def set_init_chance(self, value: int) -> None:
        """Sets the value of the Init chance spinbox."""
        self.chance_spin.setValue(value)


class EvolutionWidget(QGroupBox):
    """Widget for configuring cellular automaton evolution parameters."""

    birth_limit_changed = pyqtSignal(int)
    death_limit_changed = pyqtSignal(int)

    main_layout: QVBoxLayout
    birth_layout: QHBoxLayout
    birth_label: QLabel
    birth_spin: QSpinBox
    death_layout: QHBoxLayout
    death_label: QLabel
    death_spin: QSpinBox

    def __init__(
        self, title: str = "Evolution", parent: QWidget | None = None
    ) -> None:
        """Initializes the evolution parameters widget and builds the interface.

        Args:
            title: Group box title.
            parent: Parent Qt widget.
        """
        super().__init__(title, parent)
        self.init_ui()

    def init_ui(self) -> None:
        """Creates the «Birth limit» and «Death limit» spinboxes
        and places them in the layout."""
        self.main_layout = QVBoxLayout(self)

        self.birth_layout = QHBoxLayout()
        self.birth_label = QLabel("Birth limit:")
        self.birth_spin = QSpinBox()
        self.birth_spin.setRange(0, 7)
        self.birth_spin.setValue(DEFAULT_BIRTH_LIMIT)
        self.birth_spin.valueChanged.connect(self.birth_limit_changed.emit)

        self.birth_layout.addWidget(self.birth_label)
        self.birth_layout.addWidget(self.birth_spin)

        self.death_layout = QHBoxLayout()
        self.death_label = QLabel("Death limit:")
        self.death_spin = QSpinBox()
        self.death_spin.setRange(0, 7)
        self.death_spin.setValue(DEFAULT_DEATH_LIMIT)
        self.death_spin.valueChanged.connect(self.death_limit_changed.emit)

        self.death_layout.addWidget(self.death_label)
        self.death_layout.addWidget(self.death_spin)

        self.main_layout.addLayout(self.birth_layout)
        self.main_layout.addLayout(self.death_layout)

    def update_birth_limit_silent(self, value: int) -> None:
        """Updates Birth limit without emitting a signal.
        Used when loading a cave from file."""
        self.birth_spin.blockSignals(True)
        self.birth_spin.setValue(value)
        self.birth_spin.blockSignals(False)

    def update_death_limit_silent(self, value: int) -> None:
        """Updates Death limit without emitting a signal.
        Used when loading a cave from file."""
        self.death_spin.blockSignals(True)
        self.death_spin.setValue(value)
        self.death_spin.blockSignals(False)


class PlaybackWidget(QGroupBox):
    """Widget for controlling step-by-step mode
    and automatic playback."""

    next_step_clicked = pyqtSignal()
    auto_play_toggled = pyqtSignal(bool)
    delay_changed = pyqtSignal(int)

    main_layout: QVBoxLayout
    delay_label: QLabel
    delay_spin: QSpinBox
    next_button: QPushButton
    auto_button: QPushButton

    def __init__(
        self, title: str = "Next step", parent: QWidget | None = None
    ) -> None:
        """Initializes the playback control widget and builds the interface.

        Args:
            title: Group box title.
            parent: Parent Qt widget.
        """
        super().__init__(title, parent)
        self.init_ui()

    def init_ui(self) -> None:
        """Creates the «Next», «Play» buttons and the delay spinbox,
        and arranges them horizontally."""
        self.main_layout = QVBoxLayout(self)

        delay_row = QHBoxLayout()
        self.delay_label = QLabel("Delay:")
        self.delay_spin = QSpinBox()
        self.delay_spin.setRange(50, 500)
        self.delay_spin.setValue(500)
        self.delay_spin.setSingleStep(50)
        self.delay_spin.setSuffix(" ms")
        self.delay_spin.valueChanged.connect(self.delay_changed.emit)
        delay_row.addWidget(self.delay_label)
        delay_row.addWidget(self.delay_spin)
        self.main_layout.addLayout(delay_row)

        buttons_row = QHBoxLayout()
        self.next_button = QPushButton("Next")
        self.next_button.clicked.connect(self.next_step_clicked.emit)
        self.auto_button = QPushButton("Run")
        self.auto_button.setCheckable(True)
        self.auto_button.toggled.connect(self.on_auto_toggled)
        buttons_row.addWidget(self.next_button)
        buttons_row.addWidget(self.auto_button)
        self.main_layout.addLayout(buttons_row)

    def on_auto_toggled(self, checked: bool) -> None:
        """Auto-play toggle handler."""
        if checked:
            self.auto_button.setText("Stop")
        else:
            self.auto_button.setText("Play")
        self.auto_play_toggled.emit(checked)

    def reset_auto_button(self) -> None:
        """Resets the Run button to its initial state without emitting
        signals."""
        self.auto_button.blockSignals(True)
        self.auto_button.setChecked(False)
        self.auto_button.setText("Play")
        self.auto_button.blockSignals(False)

    def set_playback_enabled(self, enabled: bool) -> None:
        """Enables or disables the Next and Play buttons."""
        self.next_button.setEnabled(enabled)
        self.auto_button.setEnabled(enabled)

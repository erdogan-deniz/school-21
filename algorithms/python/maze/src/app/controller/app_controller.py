"""Application controller — coordinates business logic with widgets."""

import logging
from enum import Enum

from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot
from PyQt5.QtGui import QColor, QImage

from app.controller.cave_auto_play import CaveAutoPlay
from app.controller.solve_manager import SolveManager
from app.render.cave_grider import CaveGrider
from app.render.maze_grider import MazeGrider
from app.render.render import CaveRender, MazeRender, MazeSolutionRender
from controller.controller import Controller as BusinessController
from models.field import CaveFieldModel, FieldModel, MazeFieldModel
from utils.config import (
    DEFAULT_BIRTH_LIMIT,
    DEFAULT_DEATH_LIMIT,
    DEFAULT_INIT_CHANCE,
    DEFAULT_N_COLS,
    DEFAULT_N_ROWS,
)

logger: logging.Logger = logging.getLogger(__name__)


class AppMode(Enum):
    """Application operating modes."""

    MAZE = "maze"
    CAVE = "cave"


class AppController(QObject):
    """Application controller.

    Coordinates rendering and display in widgets.
    Coordinates interaction between ContentContainer and ToolbarContainer.
    Solver state is delegated to SolveManager (self._solve).
    """

    # Tab-switching signals
    show_maze_toolbar = pyqtSignal()
    show_cave_toolbar = pyqtSignal()

    # Rendering signals
    maze_rendered = pyqtSignal(QImage)
    cave_rendered = pyqtSignal(QImage)

    # Toolbar signals
    size_changed = pyqtSignal(int, int)
    init_chance_changed = pyqtSignal(int)
    # Error signal
    error_occurred = pyqtSignal(str)

    # Agent status
    agent_status_updated = pyqtSignal(str)

    # Solver UI update signal
    solve_ui_updated = pyqtSignal(str, bool)  # hint, solve_button_enabled

    # Cave field size sync
    cave_size_changed = pyqtSignal(int, int)

    # Emitted when auto play stops automatically (not by user)
    cave_auto_play_stopped = pyqtSignal()

    # Emitted to enable/disable Next and Auto Play buttons
    cave_playback_enabled = pyqtSignal(bool)

    current_mode: AppMode
    business_controller: BusinessController
    current_field_model: FieldModel | None
    maze_rows: int
    maze_cols: int
    cave_rows: int
    cave_cols: int
    cave_init_chance: int
    cave_birth_limit: int
    cave_death_limit: int
    auto_play_delay: int
    auto_play_active: bool
    _auto_play: CaveAutoPlay
    _solve: SolveManager

    def __init__(self) -> None:
        """Initializes the controller: creates the business
        controller, maze/cave parameters, auto-play timer, and SolveManager."""
        super().__init__()
        self.current_mode = AppMode.MAZE
        self.business_controller = BusinessController()
        self.current_field_model: FieldModel | None = None

        self.maze_rows = DEFAULT_N_ROWS
        self.maze_cols = DEFAULT_N_COLS

        self.cave_rows = DEFAULT_N_ROWS
        self.cave_cols = DEFAULT_N_COLS
        self.cave_init_chance = DEFAULT_INIT_CHANCE
        self.cave_birth_limit = DEFAULT_BIRTH_LIMIT
        self.cave_death_limit = DEFAULT_DEATH_LIMIT

        self.auto_play_delay = 500  # ms default
        self.auto_play_active = False
        self._auto_play = CaveAutoPlay()
        self._auto_play.step_requested.connect(self.on_cave_next_step)

        self._solve = SolveManager()

    # ------------------------------------------------------------------ mode

    @pyqtSlot(str)
    def switch_mode(self, tab_name: str) -> None:
        """Handles tab switching."""
        mode_str = tab_name.lower()

        if mode_str == "maze" and self.current_mode != AppMode.MAZE:
            self.current_mode = AppMode.MAZE
            self.show_maze_toolbar.emit()
            self.size_changed.emit(self.maze_rows, self.maze_cols)

        elif mode_str == "cave" and self.current_mode != AppMode.CAVE:
            self.current_mode = AppMode.CAVE
            self.show_cave_toolbar.emit()
            self.size_changed.emit(self.cave_rows, self.cave_cols)

    # ------------------------------------------------------------------ render

    def render_maze(self, maze_model: MazeFieldModel) -> None:
        """Renders the maze to an image and emits the signal."""
        try:
            grider = MazeGrider(maze_model)
            renderer = MazeRender(grider)
            image = renderer.get_image()

            if not image or image.isNull():  # pragma: no cover
                logger.warning("Image is null or empty")
                return

            self.current_field_model = maze_model
            self.maze_rows = maze_model.rows
            self.maze_cols = maze_model.cols
            self._solve.grider = grider
            self._solve.base_image = image.copy()
            self._reset_solve_state()
            self.maze_rendered.emit(image)
            self.size_changed.emit(self.maze_rows, self.maze_cols)

        except Exception as e:
            logger.error(f"Rendering error: {e}")
            self.error_occurred.emit(f"Maze rendering error: {str(e)}")

    def render_cave(self, cave_model: CaveFieldModel) -> None:
        """Renders the cave and emits the signal."""
        try:
            grider = CaveGrider(cave_model)
            renderer = CaveRender(grider)
            image = renderer.get_image()

            if not image or image.isNull():  # pragma: no cover
                logger.warning("Cave image is null")
                return

            self.current_field_model = cave_model
            self.cave_rows = cave_model.rows
            self.cave_cols = cave_model.cols
            self.cave_rendered.emit(image)
            self.cave_size_changed.emit(self.cave_rows, self.cave_cols)

            cave_loaded = not cave_model.is_empty()

            if not cave_loaded:
                self.init_chance_changed.emit(self.cave_init_chance)

            cave = cave_model.get_cave()
            is_final = cave.is_final_generation()
            if self.auto_play_active and is_final:
                self.on_auto_play_toggled(False)
                self.cave_auto_play_stopped.emit()
            self.cave_playback_enabled.emit(not is_final)

        except Exception as e:
            logger.error(f"Cave rendering error: {e}")
            self.error_occurred.emit(f"Cave rendering error: {str(e)}")

    # --------------------------------------------------------------- file I/O

    @pyqtSlot(str)
    def on_maze_file_selected(self, file_path: str) -> None:
        """Handles maze file selection."""
        self._load_and_render_maze(file_path)

    @pyqtSlot(str)
    def on_cave_file_selected(self, file_path: str) -> None:
        """Handles cave file selection."""
        self._load_and_render_cave(file_path)

    def _load_and_render_maze(self, file_path: str) -> None:
        """Loads the maze and renders it."""
        success = self.business_controller.load_maze_from_file(file_path)
        if not success:
            self.error_occurred.emit("Failed to load maze.")
            return

        maze = self.business_controller.get_current_field_model()
        if isinstance(maze, MazeFieldModel):
            self.render_maze(maze)

    def _load_and_render_cave(self, file_path: str) -> None:
        """Loads the cave and renders it."""
        success = self.business_controller.load_cave_from_file(file_path)
        if not success:
            self.error_occurred.emit("Failed to load cave.")
            return

        cave = self.business_controller.get_current_field_model()
        if isinstance(cave, CaveFieldModel):
            self.cave_birth_limit = cave.birth_limit
            self.cave_death_limit = cave.death_limit
            self.render_cave(cave)

    @pyqtSlot(str)
    def on_cave_save_requested(self, file_path: str) -> None:
        """Handles a request to save the cave."""
        if not self.current_field_model or not isinstance(
            self.current_field_model, CaveFieldModel
        ):
            self.error_occurred.emit("No cave loaded to save")
            return

        success = self.business_controller.save_cave_to_file(file_path)
        if success:
            logger.info(f"Cave saved to {file_path}")
        else:
            self.error_occurred.emit("Failed to save cave")

    @pyqtSlot(str)
    def on_save_maze(self, filepath: str) -> None:
        """Saves the current maze to a file."""
        if not self.business_controller.save_maze(filepath):
            self.error_occurred.emit("Failed to save maze")

    # ------------------------------------------------------------- generate

    def on_generate_maze(self) -> None:
        """Generate a maze and render it."""
        success = self.business_controller.generate_maze(
            rows=self.maze_rows, cols=self.maze_cols
        )
        if not success:
            self.error_occurred.emit("Failed to generate maze")
            return

        maze = self.business_controller.get_current_field_model()
        if isinstance(maze, MazeFieldModel):
            self.render_maze(maze)

    def on_generate_cave(self) -> None:
        """Generate a cave and render it."""
        success = self.business_controller.generate_cave(
            rows=self.cave_rows,
            cols=self.cave_cols,
            init_chance=self.cave_init_chance,
            birth_limit=self.cave_birth_limit,
            death_limit=self.cave_death_limit,
        )
        if not success:
            self.error_occurred.emit("Failed to generate cave")
            return

        cave = self.business_controller.get_current_field_model()
        if isinstance(cave, CaveFieldModel):
            self.render_cave(cave)

    # ---------------------------------------------------------- cave params

    @pyqtSlot(int)
    def on_init_chance_changed(self, value: int) -> None:
        """Saves the new cave fill percentage used at initialization."""
        self.cave_init_chance = value

    @pyqtSlot(int)
    def on_birth_limit_changed(self, value: int) -> None:
        """Updates the cell birth threshold and passes it to the business
        controller."""
        self.cave_birth_limit = value
        self.business_controller.update_cave_birth_limit(value)

    @pyqtSlot(int)
    def on_death_limit_changed(self, value: int) -> None:
        """Updates the cell death threshold and passes it to the business
        controller."""
        self.cave_death_limit = value
        self.business_controller.update_cave_death_limit(value)

    @pyqtSlot(int, int)
    def on_size_changed(self, rows: int, cols: int) -> None:
        """Saves the new field dimensions for the current mode."""
        logger.info(f"Size changed: {rows=}, {cols=}")
        if self.current_mode == AppMode.MAZE:
            self.maze_rows = rows
            self.maze_cols = cols
        else:
            self.cave_rows = rows
            self.cave_cols = cols

    # ------------------------------------------------------- cave evolution

    @pyqtSlot()
    def on_cave_next_step(self) -> None:
        """Handles the Next Step button press for the cave."""
        if self.current_mode != AppMode.CAVE:
            self.error_occurred.emit("Not in cave mode")
            return

        if self.business_controller.next_cave_generation():
            cave = self.business_controller.get_current_field_model()
            if isinstance(cave, CaveFieldModel):
                self.render_cave(cave)

    # ------------------------------------------------------------ auto play

    @pyqtSlot(bool)
    def on_auto_play_toggled(self, enabled: bool) -> None:
        """Handles toggling of auto-play mode."""
        if enabled:
            if self.current_mode != AppMode.CAVE:
                self.error_occurred.emit(
                    "Auto play only available in cave mode"
                )
                return

            cave_model = self.business_controller.get_current_field_model()
            if not isinstance(cave_model, CaveFieldModel):
                self.error_occurred.emit("No cave loaded")
                return

            if cave_model.is_final_generation():
                self.auto_play_active = False
                self.cave_auto_play_stopped.emit()
                self.cave_playback_enabled.emit(False)
                return

            self.auto_play_active = True
            self._auto_play.start(self.auto_play_delay)
            logger.info(
                f"Auto play started with delay {self.auto_play_delay}ms"
            )
        else:
            self.auto_play_active = False
            self._auto_play.stop()
            logger.info("Auto play stopped")

    @pyqtSlot(int)
    def on_delay_changed(self, delay_ms: int) -> None:
        """Handles a change in the auto-play delay."""
        self.auto_play_delay = delay_ms
        if self.auto_play_active:
            self._auto_play.start(self.auto_play_delay)
        logger.info(f"Auto play delay changed to {delay_ms}ms")

    # ------------------------------------------------------------------ solve

    @pyqtSlot(int, int)
    def on_canvas_click(self, img_x: int, img_y: int) -> None:
        """Converts pixel → cell and updates start/end points."""
        if self.current_mode != AppMode.MAZE:
            return

        cell = self._solve.pixel_to_cell(img_x, img_y)
        if cell is None:
            return

        if self._solve.agent_trained and self._solve.end is not None:
            # Agent is trained — endpoint is fixed, click sets a new start
            self._solve.start = cell
            path = self.business_controller.get_agent_path(cell)
            self._solve.path = path
            self._emit_solve_ui()
            if path is not None:
                self._render_solve_overlay(
                    path_color=MazeSolutionRender.AGENT_COLOR
                )
            else:
                self._solve.start = None
                self._render_solve_overlay()
                self.error_occurred.emit("Agent can not find a path from cell.")
            return

        self._solve.handle_regular_click(cell)
        self._emit_solve_ui()
        self._render_solve_overlay()

    @pyqtSlot(int)
    def on_agent_solve(self, episodes: int) -> None:
        """Trains the Q-learning agent and displays the found path."""
        if not self._solve.can_solve():
            return
        assert self._solve.start is not None
        assert self._solve.end is not None
        self.agent_status_updated.emit(f"Training ({episodes} episodes)…")
        path = self.business_controller.run_agent(
            self._solve.start, self._solve.end, episodes
        )
        if path is None:
            self.agent_status_updated.emit("Path not found")
            self.error_occurred.emit("Agent can not find a path.")
            return
        self._solve.agent_trained = True
        self._solve.path = path
        self.agent_status_updated.emit(f"Agent trained: {len(path)} steps")
        self._render_solve_overlay(path_color=MazeSolutionRender.AGENT_COLOR)
        self._emit_solve_ui()

    @pyqtSlot()
    def on_solve_maze(self) -> None:
        """Starts solving the maze."""
        if not self._solve.can_solve():
            return
        assert self._solve.start is not None
        assert self._solve.end is not None
        path = self.business_controller.solve_maze(
            self._solve.start, self._solve.end
        )
        if path is None:
            self.error_occurred.emit("Path not found")
            return
        self._solve.agent_trained = False
        self._solve.path = path
        self._render_solve_overlay()
        self._emit_solve_ui()

    def _reset_solve_state(self) -> None:
        """Resets the solver state and updates the UI."""
        self._solve.reset()
        self._emit_solve_ui()

    def _emit_solve_ui(self) -> None:
        """Emits the solve_ui_updated signal with the current hint."""
        hint, ready = self._solve.get_hint()
        self.solve_ui_updated.emit(hint, ready)

    def _render_solve_overlay(self, path_color: QColor | None = None) -> None:
        """Renders the path overlay and emits the maze_rendered signal."""
        image = self._solve.render_overlay(path_color)
        if image is not None:
            self.maze_rendered.emit(image)

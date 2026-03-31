"""Business logic facade: delegates operations to services
and handles errors."""

import logging

from controller.cave_service import CaveService
from controller.maze_service import MazeService
from models.field import CaveFieldModel, FieldModel, MazeFieldModel

logger: logging.Logger = logging.getLogger(__name__)


class Controller:
    """Business controller: a thin facade over MazeService and CaveService.

    Responsible for:
    - storing the current field model (current_field_model);
    - catching exceptions from services and returning bool/None to the caller;
    - logging errors.

    Attributes:
        current_field_model: current model (maze or cave) or None.
    """

    current_field_model: FieldModel | None
    _maze: MazeService
    _cave: CaveService

    def __init__(self) -> None:
        self.current_field_model: FieldModel | None = None
        self._maze = MazeService()
        self._cave = CaveService()

    def get_current_field_model(self) -> FieldModel | None:
        """Returns the current field model or None."""
        return self.current_field_model

    # ------------------------------------------------------------------ maze

    def load_maze_from_file(self, filepath: str) -> bool:
        """Loads a maze from a file."""
        try:
            self.current_field_model = self._maze.load(filepath)
            return True
        except Exception as e:
            logger.error("Error loading maze: %s", e)
            return False

    def generate_maze(self, rows: int, cols: int) -> bool:
        """Generates a new maze of the given size."""
        try:
            self.current_field_model = self._maze.generate(rows, cols)
            return True
        except Exception as e:
            logger.error("Error generating maze: %s", e)
            return False

    def save_maze(self, filepath: str) -> bool:
        """Saves the current maze to a file."""
        model = self._require_maze_model()
        if model is None:
            return False
        try:
            self._maze.save(model, filepath)
            return True
        except Exception as e:
            logger.error("Error saving maze: %s", e)
            return False

    def solve_maze(
        self, start: tuple[int, int], end: tuple[int, int]
    ) -> list[tuple[int, int]] | None:
        """Finds the shortest path in the current maze."""
        model = self._require_maze_model()
        if model is None:
            return None
        try:
            return self._maze.solve(model, start, end)
        except Exception as e:
            logger.error("Error solving maze: %s", e)
            return None

    # ------------------------------------------------------------------ agent

    def run_agent(
        self,
        start: tuple[int, int],
        end: tuple[int, int],
        episodes: int = 1000,
    ) -> list[tuple[int, int]] | None:
        """Trains the Q-learning agent and returns the path from start."""
        model = self._require_maze_model()
        if model is None:
            return None
        try:
            return self._maze.run_agent(model, start, end, episodes)
        except Exception as e:
            logger.error("Agent error: %s", e)
            return None

    def get_agent_path(
        self, start: tuple[int, int]
    ) -> list[tuple[int, int]] | None:
        """Builds a path using the trained agent from start
        to the fixed end point."""
        model = self._require_maze_model()
        if model is None:
            return None
        try:
            return self._maze.get_agent_path(model, start)
        except Exception as e:
            logger.error("Agent path error: %s", e)
            return None

    def get_trained_end(self) -> tuple[int, int] | None:
        """Returns the end point of the last agent training run."""
        return self._maze.get_trained_end()

    # ------------------------------------------------------------------ cave

    def load_cave_from_file(self, filepath: str) -> bool:
        """Loads a cave from a file."""
        try:
            self.current_field_model = self._cave.load(filepath)
            self._maze.reset_agent()
            return True
        except Exception as e:
            logger.error("Error loading cave: %s", e)
            return False

    def generate_cave(
        self,
        rows: int,
        cols: int,
        init_chance: int,
        birth_limit: int,
        death_limit: int,
    ) -> bool:
        """Generates a new cave with the given parameters."""
        try:
            self.current_field_model = self._cave.generate(
                rows, cols, init_chance, birth_limit, death_limit
            )
            return True
        except Exception as e:
            logger.error("Error generating cave: %s", e)
            return False

    def save_cave_to_file(self, filepath: str) -> bool:
        """Saves the current cave to a file."""
        model = self._require_cave_model()
        if model is None:
            return False
        try:
            self._cave.save(model, filepath)
            return True
        except Exception as e:
            logger.error("Error saving cave: %s", e)
            return False

    def update_cave_birth_limit(self, birth_limit: int) -> bool:
        """Updates the cell birth threshold in the current cave."""
        model = self._require_cave_model()
        if model is None:
            return False
        try:
            self._cave.update_birth_limit(model, birth_limit)
            return True
        except Exception as e:
            logger.error("Error updating birth limit: %s", e)
            return False

    def update_cave_death_limit(self, death_limit: int) -> bool:
        """Updates the cell death threshold in the current cave."""
        model = self._require_cave_model()
        if model is None:
            return False
        try:
            self._cave.update_death_limit(model, death_limit)
            return True
        except Exception as e:
            logger.error("Error updating death limit: %s", e)
            return False

    def next_cave_generation(self) -> bool:
        """Computes the next cave generation."""
        model = self._require_cave_model()
        if model is None:
            return False
        self.current_field_model = self._cave.next_generation(model)
        return True

    # ------------------------------------------------------------------ misc

    def clear(self) -> None:
        """Resets the current field model and agent state."""
        self.current_field_model = None
        self._maze.reset_agent()

    # ------------------------------------------------------------------ private

    def _require_maze_model(self) -> MazeFieldModel | None:
        """Returns the current MazeFieldModel or None (with logging)."""
        if not self.current_field_model:
            logger.warning("No field model loaded")
            return None
        if not isinstance(self.current_field_model, MazeFieldModel):
            logger.warning("Current model is not a maze")
            return None
        return self.current_field_model

    def _require_cave_model(self) -> CaveFieldModel | None:
        """Returns the current CaveFieldModel or None (with logging)."""
        if not self.current_field_model:
            logger.warning("No field model loaded")
            return None
        if not isinstance(self.current_field_model, CaveFieldModel):
            logger.warning("Current model is not a cave")
            return None
        return self.current_field_model

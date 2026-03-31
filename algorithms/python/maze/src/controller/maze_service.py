"""Maze service: generation, loading,
saving, solving, and agent."""

from core.maze_agent import QLearningAgent
from core.maze_generator import MazeGenerator, MazeGeneratorImpl
from core.maze_solver import MazeSolver
from handlers.file_handler import MazeFileHandler
from models.field import MazeFieldModel


class MazeService:
    """Encapsulates maze operations and the trained agent state.

    Methods do not handle exceptions — on error they propagate upward.
    The Controller facade is responsible for catching and logging them.

    Attributes:
        maze_generator: maze generator (replaceable in tests).
        _trained_agent: trained Q-learning agent or None.
        _trained_end: end point of the last training run or None.
    """

    maze_generator: MazeGenerator
    _trained_agent: QLearningAgent | None
    _trained_end: tuple[int, int] | None

    def __init__(self) -> None:
        self.maze_generator: MazeGenerator = MazeGeneratorImpl()
        self._trained_agent: QLearningAgent | None = None
        self._trained_end: tuple[int, int] | None = None

    def reset_agent(self) -> None:
        """Resets the trained agent state."""
        self._trained_agent = None
        self._trained_end = None

    def load(self, filepath: str) -> MazeFieldModel:
        """Loads a maze from a file.

        Raises:
            Exception: on file read error.
        """
        maze = MazeFileHandler.read_from_file(filepath)
        self.reset_agent()
        return MazeFieldModel.from_maze(maze)

    def generate(self, rows: int, cols: int) -> MazeFieldModel:
        """Generates a maze of the given size.

        Raises:
            Exception: on generation error.
        """
        maze = self.maze_generator.generate(rows, cols)
        self.reset_agent()
        return MazeFieldModel.from_maze(maze)

    def save(self, model: MazeFieldModel, filepath: str) -> None:
        """Saves the maze to a file.

        Raises:
            Exception: on write error.
        """
        MazeFileHandler.save_to_file(model.get_maze(), filepath)

    def solve(
        self,
        model: MazeFieldModel,
        start: tuple[int, int],
        end: tuple[int, int],
    ) -> list[tuple[int, int]] | None:
        """Finds the shortest path in the maze."""
        return MazeSolver(model.get_maze()).solve(start, end)

    def run_agent(
        self,
        model: MazeFieldModel,
        start: tuple[int, int],
        end: tuple[int, int],
        episodes: int,
    ) -> list[tuple[int, int]] | None:
        """Trains the agent and returns the path from start to end.

        Raises:
            Exception: on training error.
        """
        agent = QLearningAgent()
        agent.train(model.get_maze(), start, end, episodes=episodes)
        self._trained_agent = agent
        self._trained_end = end
        return agent.get_path(model.get_maze(), start, end)

    def get_agent_path(
        self,
        model: MazeFieldModel,
        start: tuple[int, int],
    ) -> list[tuple[int, int]] | None:
        """Builds a path using the trained agent.

        Returns:
            List of path cells, or None if the agent has not been trained.

        Raises:
            Exception: on path-building error.
        """
        if self._trained_agent is None or self._trained_end is None:
            return None
        return self._trained_agent.get_path(
            model.get_maze(), start, self._trained_end
        )

    def get_trained_end(self) -> tuple[int, int] | None:
        """Returns the end point of the last training run."""
        return self._trained_end

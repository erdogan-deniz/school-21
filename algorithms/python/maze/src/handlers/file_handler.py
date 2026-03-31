"""File handlers for saving and loading maze and cave models."""

import os
from abc import ABC, abstractmethod

from core.cave import Cave
from core.maze import Maze
from utils.config import DEFAULT_BIRTH_LIMIT, DEFAULT_DEATH_LIMIT


class FileHandler[T](ABC):
    """Abstract base class for file handlers."""

    @classmethod
    def read_from_file(cls, filepath: str) -> T:
        """
        Reads data from a file and returns a model object.

        Args:
            filepath: path to the file

        Returns:
            A model object (Maze or Cave)
        """

        cls._validate_file_exists(filepath)

        with open(filepath) as f:
            content = [line.strip() for line in f if line.strip() != ""]

        parsed_data = cls._parse_content(content, filepath)

        return cls._create_model_from_data(parsed_data)

    @classmethod
    def save_to_file(cls, model: T, filepath: str) -> None:
        """
        Saves a model object to a file.

        Args:
            model: model object to save
            filepath: path to save the file to
        """

        data_to_save = cls._prepare_data_for_saving(model)

        os.makedirs(os.path.dirname(os.path.abspath(filepath)), exist_ok=True)

        with open(filepath, "w") as f:
            f.write(data_to_save)

    @staticmethod
    def _validate_file_exists(filepath: str) -> None:
        """Checks that the file exists."""
        if not os.path.exists(filepath):
            raise FileNotFoundError(f"File not found: {filepath}")

    @staticmethod
    def _parse_content(content: list[str], filepath: str) -> list[list[int]]:
        """
        Parses the file content.
        Maze and Cave models require subclass-specific handling
        because they contain a different number of matrices.

        Args:
            content: file content split into lines
            filepath: path to the file (used in error messages)

        Returns:
            Lines converted to arrays of integers.
            Extra whitespace has been removed.
        """

        result = []
        for line in content:
            try:
                row = list(map(int, line.split()))
            except ValueError as err:
                raise ValueError(f"Bad content in file {filepath}") from err
            result.append(row)

        return result

    @classmethod
    @abstractmethod
    def _create_model_from_data(  # pragma: no cover
        cls,
        data: list[list[int]],
    ) -> T:
        """
        Creates a model object from the parsed data.

        Args:
            data: parsed data rows

        Returns:
            Model object
        """
        ...

    @classmethod
    @abstractmethod
    def _prepare_data_for_saving(  # pragma: no cover
        cls,
        model: T,
    ) -> str:
        """
        Prepares model data for writing to a file.

        Args:
            model: model object

        Returns:
            String to write to the file
        """
        ...


class MazeFileHandler(FileHandler[Maze]):
    """File handler for mazes."""

    @classmethod
    def _create_model_from_data(cls, data: list[list[int]]) -> Maze:
        """Builds a Maze object from the parsed file rows.

        Args:
            data: list of rows; the first row is [rows, cols],
                  the next ``rows`` rows are the vertical wall matrix,
                  the remaining rows are the horizontal wall matrix.

        Returns:
            Initialised Maze object.
        """
        if not data or len(data[0]) != 2:
            raise ValueError("Invalid maze file: missing or malformed header")
        rows, cols = data[0]
        vertical_walls = data[1 : rows + 1]
        horizontal_walls = data[rows + 1 :]

        maze = Maze(rows, cols, vertical_walls, horizontal_walls)

        return maze

    @classmethod
    def _prepare_data_for_saving(cls, maze: Maze) -> str:
        """Prepares Maze data for saving."""
        result = []

        result.append(f"{maze.rows} {maze.cols}")

        for row in maze.get_vertical_walls():
            result.append(" ".join(map(str, row)))

        result.append("")

        for row in maze.get_horizontal_walls():
            result.append(" ".join(map(str, row)))

        return "\n".join(result)


class CaveFileHandler(FileHandler[Cave]):
    """File handler for caves."""

    @classmethod
    def _create_model_from_data(cls, data: list[list[int]]) -> Cave:
        """Builds a Cave object from the parsed file rows.

        Args:
            data: list of rows; the first row is [rows, cols],
                  the remaining rows are the cave cell matrix (0/1).

        Returns:
            Initialised Cave object with default parameters.
        """
        if not data or len(data[0]) != 2:
            raise ValueError("Invalid cave file: missing or malformed header")
        rows, cols = data[0]
        field = data[1:]

        cave = Cave(
            rows=rows,
            cols=cols,
            field_mtx=field,
            birth_limit=DEFAULT_BIRTH_LIMIT,
            death_limit=DEFAULT_DEATH_LIMIT,
        )

        return cave

    @classmethod
    def _prepare_data_for_saving(cls, cave: Cave) -> str:
        """Prepares Cave data for saving."""
        result = []

        result.append(f"{cave.rows} {cave.cols}")

        for row in cave.get_field():
            result.append(" ".join(map(str, row)))

        return "\n".join(result)

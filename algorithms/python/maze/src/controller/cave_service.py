"""Cave service: generation, loading, saving, and evolution."""

from core.cave import Cave
from handlers.file_handler import CaveFileHandler
from models.field import CaveFieldModel
from utils.config import BIRTH_DEATH_LIMITS


class CaveService:
    """Encapsulates cave operations.

    Stateless — all methods receive the model as an argument.
    Methods do not handle exceptions — they propagate to the Controller facade.
    """

    def load(self, filepath: str) -> CaveFieldModel:
        """Loads a cave from a file.

        Raises:
            Exception: on file read error.
        """
        cave = CaveFileHandler.read_from_file(filepath)
        return CaveFieldModel.from_cave(cave)

    def generate(
        self,
        rows: int,
        cols: int,
        init_chance: int,
        birth_limit: int,
        death_limit: int,
    ) -> CaveFieldModel:
        """Generates a new cave with the given parameters.

        Raises:
            Exception: on generation error.
        """
        cave = Cave(
            rows=rows,
            cols=cols,
            init_chance=init_chance,
            birth_limit=birth_limit,
            death_limit=death_limit,
        )
        return CaveFieldModel.from_cave(cave)

    def save(self, model: CaveFieldModel, filepath: str) -> None:
        """Saves the cave to a file.

        Raises:
            Exception: on write error.
        """
        CaveFileHandler.save_to_file(model.get_cave(), filepath)

    @staticmethod
    def update_birth_limit(model: CaveFieldModel, value: int) -> None:
        """Sets the cell birth threshold in the model.

        Raises:
            ValueError: if value is outside the allowed range (0–7).
        """
        if value not in BIRTH_DEATH_LIMITS:
            raise ValueError(f"Birth limit {value} is invalid")
        model.birth_limit = value

    @staticmethod
    def update_death_limit(model: CaveFieldModel, value: int) -> None:
        """Sets the cell death threshold in the model.

        Raises:
            ValueError: if value is outside the allowed range (0–7).
        """
        if value not in BIRTH_DEATH_LIMITS:
            raise ValueError(f"Death limit {value} is invalid")
        model.death_limit = value

    @staticmethod
    def next_generation(model: CaveFieldModel) -> CaveFieldModel:
        """Computes the next cave generation.

        Returns:
            A new model for the next generation, or the same model
            if already final.
        """
        cave = model.get_cave()
        next_cave = cave.next_generation()
        if cave.field == next_cave.field:
            return model
        return CaveFieldModel.from_cave(next_cave)

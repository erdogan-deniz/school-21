"""
Utilities for working with project paths.
"""

from pathlib import Path


class ProjectPaths:
    """Utility class for working with project paths."""

    _project_root: Path | None = None

    @classmethod
    def get_project_root(cls) -> Path:
        """
        Returns the path to the package root directory (src/ or install dir).
        paths.py is always located at <root>/utils/paths.py.
        """
        if cls._project_root is not None:
            return cls._project_root

        cls._project_root = Path(__file__).resolve().parent.parent
        return cls._project_root

    @classmethod
    def get_data_dir(cls) -> Path:
        """Returns the path to the data directory.

        Dev mode: data/ sits next to src/ → root.parent/data
        Installed: data/ is inside the install dir → root/data
        """
        root = cls.get_project_root()
        candidate = root.parent / "data"
        if candidate.is_dir():
            return candidate
        return root / "data"  # pragma: no cover

    @classmethod
    def get_maze_data_dir(cls) -> Path:
        """Returns the path to the data/maze directory."""
        return cls.get_data_dir() / "maze"

    @classmethod
    def get_cave_data_dir(cls) -> Path:
        """Returns the path to the data/cave directory."""
        return cls.get_data_dir() / "cave"

    @classmethod
    def get_assets_dir(cls) -> Path:
        """Returns the path to the assets/ directory."""
        root = cls.get_project_root()
        candidate = root.parent / "assets"
        if candidate.is_dir():
            return candidate
        return root / "assets"  # pragma: no cover

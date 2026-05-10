"""Tests for utils.paths.ProjectPaths."""

from pathlib import Path
from unittest.mock import patch

from utils.paths import ProjectPaths


class TestGetAssetsDir:
    """Tests for ProjectPaths.get_assets_dir."""

    def test_returns_candidate_when_exists(self, tmp_path: Path) -> None:
        """Returns root.parent/assets when that directory exists."""
        fake_root = tmp_path / "src"
        assets = tmp_path / "assets"
        assets.mkdir()
        with patch.object(
            ProjectPaths, "get_project_root", return_value=fake_root
        ):
            result = ProjectPaths.get_assets_dir()
        assert result == assets

    def test_falls_back_to_root_assets_when_candidate_missing(
        self, tmp_path: Path
    ) -> None:
        """Falls back to root/assets when root.parent/assets does not exist."""
        with patch.object(
            ProjectPaths, "get_project_root", return_value=tmp_path
        ):
            result = ProjectPaths.get_assets_dir()
        assert result == tmp_path / "assets"

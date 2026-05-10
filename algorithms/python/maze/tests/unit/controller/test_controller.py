"""Tests for Controller — the business-logic facade over
MazeService and CaveService."""

# python3 -m pytest tests/unit/test_controller.py -v

from pathlib import Path
from unittest.mock import patch

import pytest

from controller.controller import Controller
from core.cave import Cave
from models.field import CaveFieldModel
from utils.paths import ProjectPaths

MAZE_4X4 = str(ProjectPaths().get_maze_data_dir() / "4x4.txt")
CAVE_4X4 = str(ProjectPaths().get_cave_data_dir() / "4x4.txt")


# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def ctrl() -> Controller:
    return Controller()


@pytest.fixture
def ctrl_with_maze(ctrl: Controller) -> Controller:
    ctrl.load_maze_from_file(MAZE_4X4)
    return ctrl


@pytest.fixture
def maze_file(tmp_path: Path) -> str:
    """Minimal 2×2 maze file."""
    content = "2 2\n0 1\n0 1\n\n0 0\n1 1\n"
    p = tmp_path / "maze.txt"
    p.write_text(content)
    return str(p)


@pytest.fixture
def cave_file(tmp_path: Path) -> str:
    """2×2 cave file with live cells."""
    content = "2 2\n1 1\n1 1\n"
    p = tmp_path / "cave.txt"
    p.write_text(content)
    return str(p)


# ---------------------------------------------------------------------------
# load_maze_from_file — exception branch
# ---------------------------------------------------------------------------


class TestLoadMazeFromFile:
    """Tests for Controller.load_maze_from_file exception branch."""

    def test_exception_returns_false(self, ctrl: Controller) -> None:
        """An I/O exception during load is caught and False is returned."""
        with patch.object(
            ctrl._maze,
            "load",
            side_effect=OSError("not found"),
        ):
            assert ctrl.load_maze_from_file("/bad/path.txt") is False

    def test_model_unchanged_on_error(self, ctrl_with_maze: Controller) -> None:
        """The current field model is unchanged when an exception occurs."""
        old_model = ctrl_with_maze.get_current_field_model()
        with patch.object(
            ctrl_with_maze._maze,
            "load",
            side_effect=OSError("fail"),
        ):
            ctrl_with_maze.load_maze_from_file("/bad/path.txt")
        assert ctrl_with_maze.get_current_field_model() is old_model


# ---------------------------------------------------------------------------
# generate_maze — success branch
# ---------------------------------------------------------------------------


class TestGenerateMaze:
    """Tests for Controller.generate_maze success path."""

    def test_success_returns_true(self, ctrl: Controller) -> None:
        """Successful maze generation returns True."""
        assert ctrl.generate_maze(5, 5) is True

    def test_success_sets_maze_model(self, ctrl: Controller) -> None:
        """After generation, get_current_field_model returns a model."""
        from models.field import MazeFieldModel

        ctrl.generate_maze(4, 4)
        assert isinstance(ctrl.get_current_field_model(), MazeFieldModel)


# ---------------------------------------------------------------------------
# load_cave_from_file
# ---------------------------------------------------------------------------


class TestLoadCaveFromFile:
    """Tests for Controller.load_cave_from_file."""

    def test_success_returns_true(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Loading a valid cave file returns True."""
        assert ctrl.load_cave_from_file(cave_file) is True

    def test_success_sets_cave_model(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """After loading, get_current_field_model returns a CaveFieldModel."""
        ctrl.load_cave_from_file(cave_file)
        assert isinstance(ctrl.get_current_field_model(), CaveFieldModel)

    def test_real_cave_file_loads(self, ctrl: Controller) -> None:
        """The bundled 4×4 cave sample file loads without error."""
        assert ctrl.load_cave_from_file(CAVE_4X4) is True

    def test_missing_file_returns_false(self, ctrl: Controller) -> None:
        """Loading a non-existent file returns False."""
        assert ctrl.load_cave_from_file("nonexistent_cave.txt") is False

    def test_invalid_content_returns_false(
        self, ctrl: Controller, tmp_path: Path
    ) -> None:
        """Loading a file with invalid content returns False."""
        bad_file = tmp_path / "bad.txt"
        bad_file.write_text("not a cave\n")
        assert ctrl.load_cave_from_file(str(bad_file)) is False


# ---------------------------------------------------------------------------
# generate_maze — error branch
# ---------------------------------------------------------------------------


class TestGenerateMazeError:
    """Tests for Controller.generate_maze error branches."""

    def test_exception_returns_false(self, ctrl: Controller) -> None:
        """An exception during generation is caught and False is returned."""
        with patch.object(
            ctrl._maze.maze_generator,
            "generate",
            side_effect=RuntimeError("boom"),
        ):
            assert ctrl.generate_maze(5, 5) is False

    def test_model_unchanged_on_error(self, ctrl_with_maze: Controller) -> None:
        """The current field model is unchanged when an exception occurs."""
        old_model = ctrl_with_maze.get_current_field_model()
        with patch.object(
            ctrl_with_maze._maze.maze_generator,
            "generate",
            side_effect=RuntimeError,
        ):
            ctrl_with_maze.generate_maze(5, 5)
        # Model unchanged (exception raised before assignment)
        assert ctrl_with_maze.get_current_field_model() is old_model


# ---------------------------------------------------------------------------
# save_maze
# ---------------------------------------------------------------------------


class TestSaveMaze:
    """Tests for Controller.save_maze."""

    def test_no_maze_returns_false(
        self, ctrl: Controller, tmp_path: Path
    ) -> None:
        """save_maze returns False when no maze is loaded."""
        assert ctrl.save_maze(str(tmp_path / "out.txt")) is False

    def test_success_returns_true(
        self, ctrl_with_maze: Controller, tmp_path: Path
    ) -> None:
        """save_maze returns True on success."""
        out = tmp_path / "out.txt"
        assert ctrl_with_maze.save_maze(str(out)) is True

    def test_saved_file_exists(
        self, ctrl_with_maze: Controller, tmp_path: Path
    ) -> None:
        """save_maze creates the output file."""
        out = tmp_path / "out.txt"
        ctrl_with_maze.save_maze(str(out))
        assert out.exists()

    def test_exception_returns_false(
        self, ctrl_with_maze: Controller, tmp_path: Path
    ) -> None:
        """An I/O exception during save is caught and False is returned."""
        with patch(
            "controller.maze_service.MazeFileHandler.save_to_file",
            side_effect=OSError("disk full"),
        ):
            assert ctrl_with_maze.save_maze(str(tmp_path / "out.txt")) is False


# ---------------------------------------------------------------------------
# solve_maze
# ---------------------------------------------------------------------------


class TestSolveMaze:
    """Tests for Controller.solve_maze — BFS path finding."""

    def test_no_maze_returns_none(self, ctrl: Controller) -> None:
        """solve_maze returns None when no maze is loaded."""
        assert ctrl.solve_maze((0, 0), (3, 3)) is None

    def test_finds_path(self, ctrl_with_maze: Controller) -> None:
        """solve_maze returns a valid path from start to end."""
        path = ctrl_with_maze.solve_maze((0, 0), (3, 3))
        assert path is not None
        assert path[0] == (0, 0)
        assert path[-1] == (3, 3)

    def test_exception_returns_none(self, ctrl_with_maze: Controller) -> None:
        """An exception in the solver is caught and None is returned."""
        with patch(
            "controller.maze_service.MazeSolver",
            side_effect=RuntimeError("solver broke"),
        ):
            assert ctrl_with_maze.solve_maze((0, 0), (3, 3)) is None


# ---------------------------------------------------------------------------
# run_agent
# ---------------------------------------------------------------------------


class TestRunAgent:
    """Tests for Controller.run_agent —
    Q-learning training and path extraction."""

    def test_no_maze_returns_none(self, ctrl: Controller) -> None:
        """run_agent returns None when no maze is loaded."""
        assert ctrl.run_agent((0, 0), (3, 3)) is None

    def test_finds_path_on_simple_maze(self, maze_file: str) -> None:
        """After training, run_agent returns a path
        on a simple 2×2 open maze."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        # 2×2 open maze — the agent should find a path
        path = c.run_agent((0, 0), (1, 1), episodes=500)
        assert path is not None

    def test_exception_returns_none(self, ctrl_with_maze: Controller) -> None:
        """An exception during agent construction is caught
        and None is returned."""
        with patch(
            "controller.maze_service.QLearningAgent",
            side_effect=RuntimeError("agent broke"),
        ):
            assert ctrl_with_maze.run_agent((0, 0), (3, 3)) is None


# ---------------------------------------------------------------------------
# get_agent_path / get_trained_end
# ---------------------------------------------------------------------------


class TestGetAgentPath:
    """Tests for Controller.get_agent_path —
    greedy path from a trained agent."""

    def test_no_trained_agent_returns_none(
        self, ctrl_with_maze: Controller
    ) -> None:
        """Returns None when the agent has not been trained yet."""
        assert ctrl_with_maze.get_agent_path((0, 0)) is None

    def test_returns_path_after_run_agent(self, maze_file: str) -> None:
        """Returns a path after run_agent has been called."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=500)
        path = c.get_agent_path((0, 0))
        assert path is not None

    def test_cleared_on_load_new_maze(self, maze_file: str) -> None:
        """Reloading a maze clears the trained agent."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=500)
        c.load_maze_from_file(maze_file)  # reload — agent should be reset
        assert c.get_agent_path((0, 0)) is None

    def test_cleared_on_clear(self, maze_file: str) -> None:
        """Calling clear() removes the trained agent."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=500)
        c.clear()
        assert c.get_agent_path((0, 0)) is None

    def test_no_maze_returns_none(self, ctrl: Controller) -> None:
        """Returns None when no maze is loaded."""
        assert ctrl.get_agent_path((0, 0)) is None


class TestGetTrainedEnd:
    """Tests for Controller.get_trained_end —
    retrieves the endpoint the agent was trained for."""

    def test_no_agent_returns_none(self, ctrl: Controller) -> None:
        """Returns None when no agent has been trained."""
        assert ctrl.get_trained_end() is None

    def test_returns_end_after_run_agent(self, maze_file: str) -> None:
        """Returns the endpoint used during training."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=100)
        assert c.get_trained_end() == (1, 1)

    def test_cleared_on_load(self, maze_file: str) -> None:
        """Reloading a maze clears the trained endpoint."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=100)
        c.load_maze_from_file(maze_file)
        assert c.get_trained_end() is None


# ---------------------------------------------------------------------------
# save_cave_to_file
# ---------------------------------------------------------------------------


class TestSaveCaveToFile:
    """Tests for Controller.save_cave_to_file."""

    def test_no_model_returns_false(
        self, ctrl: Controller, tmp_path: Path
    ) -> None:
        """Returns False when no field model is loaded."""
        assert ctrl.save_cave_to_file(str(tmp_path / "out.txt")) is False

    def test_maze_model_returns_false(
        self, ctrl_with_maze: Controller, tmp_path: Path
    ) -> None:
        """Returns False when the current model is a maze, not a cave."""
        assert (
            ctrl_with_maze.save_cave_to_file(str(tmp_path / "out.txt")) is False
        )

    def test_success_returns_true(
        self, ctrl: Controller, cave_file: str, tmp_path: Path
    ) -> None:
        """Returns True after successfully saving a loaded cave."""
        ctrl.load_cave_from_file(cave_file)
        out = tmp_path / "out.txt"
        assert ctrl.save_cave_to_file(str(out)) is True

    def test_saved_file_exists(
        self, ctrl: Controller, cave_file: str, tmp_path: Path
    ) -> None:
        """The saved file is created on disk."""
        ctrl.load_cave_from_file(cave_file)
        out = tmp_path / "out.txt"
        ctrl.save_cave_to_file(str(out))
        assert out.exists()

    def test_exception_returns_false(
        self, ctrl: Controller, cave_file: str, tmp_path: Path
    ) -> None:
        """An I/O exception during save is caught and False is returned."""
        ctrl.load_cave_from_file(cave_file)
        with patch(
            "controller.cave_service.CaveFileHandler.save_to_file",
            side_effect=OSError("disk full"),
        ):
            assert ctrl.save_cave_to_file(str(tmp_path / "out.txt")) is False


# ---------------------------------------------------------------------------
# generate_cave
# ---------------------------------------------------------------------------


class TestGenerateCave:
    """Tests for Controller.generate_cave."""

    def test_success_returns_true(self, ctrl: Controller) -> None:
        """generate_cave returns True on success."""
        assert ctrl.generate_cave(5, 5, 50, 3, 3) is True

    def test_success_sets_cave_model(self, ctrl: Controller) -> None:
        """After generation, get_current_field_model
        returns a CaveFieldModel."""
        ctrl.generate_cave(5, 5, 50, 3, 3)
        assert isinstance(ctrl.get_current_field_model(), CaveFieldModel)

    def test_exception_returns_false(self, ctrl: Controller) -> None:
        """An exception during Cave construction is caught
        and False is returned."""
        with patch(
            "controller.cave_service.Cave", side_effect=RuntimeError("boom")
        ):
            assert ctrl.generate_cave(5, 5, 50, 3, 3) is False


# ---------------------------------------------------------------------------
# update_cave_birth_limit / update_cave_death_limit
# ---------------------------------------------------------------------------


class TestUpdateCaveLimits:
    """Tests for Controller.update_cave_birth_limit
    and update_cave_death_limit."""

    def test_birth_no_model_returns_false(self, ctrl: Controller) -> None:
        """Returns False when no field model is loaded."""
        assert ctrl.update_cave_birth_limit(4) is False

    def test_birth_maze_model_returns_false(
        self, ctrl_with_maze: Controller
    ) -> None:
        """Returns False when the current model is a maze, not a cave."""
        assert ctrl_with_maze.update_cave_birth_limit(4) is False

    def test_birth_success_returns_true(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Returns True after successfully updating the birth limit."""
        ctrl.load_cave_from_file(cave_file)
        assert ctrl.update_cave_birth_limit(4) is True

    def test_birth_value_updated(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """The cave model's birth_limit is updated to the new value."""
        ctrl.load_cave_from_file(cave_file)
        ctrl.update_cave_birth_limit(4)
        assert ctrl.get_current_field_model().birth_limit == 4

    def test_death_no_model_returns_false(self, ctrl: Controller) -> None:
        """Returns False when no field model is loaded."""
        assert ctrl.update_cave_death_limit(2) is False

    def test_death_maze_model_returns_false(
        self, ctrl_with_maze: Controller
    ) -> None:
        """Returns False when the current model is a maze, not a cave."""
        assert ctrl_with_maze.update_cave_death_limit(2) is False

    def test_death_success_returns_true(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Returns True after successfully updating the death limit."""
        ctrl.load_cave_from_file(cave_file)
        assert ctrl.update_cave_death_limit(2) is True

    def test_death_value_updated(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """The cave model's death_limit is updated to the new value."""
        ctrl.load_cave_from_file(cave_file)
        ctrl.update_cave_death_limit(2)
        assert ctrl.get_current_field_model().death_limit == 2

    def test_birth_invalid_value_returns_false(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Returns False when birth_limit is outside 0–7."""
        ctrl.load_cave_from_file(cave_file)
        assert ctrl.update_cave_birth_limit(8) is False

    def test_death_invalid_value_returns_false(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Returns False when death_limit is outside 0–7."""
        ctrl.load_cave_from_file(cave_file)
        assert ctrl.update_cave_death_limit(-1) is False


# ---------------------------------------------------------------------------
# get_agent_path — uncovered branches
# ---------------------------------------------------------------------------


class TestGetAgentPathEdgeCases:
    """Edge cases for Controller.get_agent_path."""

    def test_cave_model_after_train_returns_none(
        self, maze_file: str, cave_file: str
    ) -> None:
        """Agent is trained, but the current model is a cave (not a maze)."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=200)
        c.load_cave_from_file(cave_file)  # replace model with a cave
        assert c.get_agent_path((0, 0)) is None

    def test_exception_returns_none(self, maze_file: str) -> None:
        """An exception in agent.get_path is caught and None is returned."""
        c = Controller()
        c.load_maze_from_file(maze_file)
        c.run_agent((0, 0), (1, 1), episodes=200)
        with patch.object(
            c._maze._trained_agent,
            "get_path",
            side_effect=RuntimeError("agent broke"),
        ):
            assert c.get_agent_path((0, 0)) is None


# ---------------------------------------------------------------------------
# next_cave_generation
# ---------------------------------------------------------------------------


class TestNextCaveGeneration:
    """Tests for Controller.next_cave_generation."""

    def test_no_model_returns_false(self, ctrl: Controller) -> None:
        """Returns False when no field model is loaded."""
        assert ctrl.next_cave_generation() is False

    def test_maze_model_returns_false(self, ctrl_with_maze: Controller) -> None:
        """Returns False when the current model is a maze, not a cave."""
        assert ctrl_with_maze.next_cave_generation() is False

    def test_cave_model_returns_true(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Returns True after advancing a loaded cave to the next generation."""
        ctrl.load_cave_from_file(cave_file)
        assert ctrl.next_cave_generation() is True

    def test_cave_model_updates_field(self, ctrl: Controller) -> None:
        """The field model is replaced with a new object after advancing."""
        ctrl.load_cave_from_file(CAVE_4X4)
        model_before = ctrl.get_current_field_model()
        ctrl.next_cave_generation()
        # Model was replaced with a new object
        assert ctrl.get_current_field_model() is not model_before

    def test_final_generation_returns_true(
        self, ctrl: Controller, cave_file: str
    ) -> None:
        """Even at the final generation, returns True."""
        ctrl.load_cave_from_file(cave_file)
        with patch.object(
            ctrl.get_current_field_model().get_cave().__class__,
            "is_final_generation",
            return_value=True,
        ):
            # Even if is_final_generation, still returns True
            assert ctrl.next_cave_generation() is True


# ---------------------------------------------------------------------------
# CaveFieldModel — uncovered methods
# ---------------------------------------------------------------------------


class TestCaveFieldModel:
    """Tests for CaveFieldModel utility methods
    (is_empty, is_final_generation)."""

    @pytest.fixture
    def model(self) -> CaveFieldModel:
        """CaveFieldModel built from a Cave
        with birth_limit=3, death_limit=3."""
        cave = Cave(
            rows=3, cols=3, init_chance=50, birth_limit=3, death_limit=3
        )
        return CaveFieldModel.from_cave(cave)

    def test_is_empty_true_for_empty(self) -> None:
        """is_empty returns True when all cells are 0 (dead)."""
        m = CaveFieldModel(rows=3, cols=3, cells=[[0] * 3 for _ in range(3)])
        assert m.is_empty() is True

    def test_is_empty_false_when_has_live(self, model: CaveFieldModel) -> None:
        # model from Cave with init_chance=50 — guaranteed to have live cells
        # set one manually to be sure
        model.cells[0][0] = 1
        assert model.is_empty() is False

    def test_is_final_generation_false_for_evolving(
        self, model: CaveFieldModel
    ) -> None:
        """is_final_generation returns False when the field will change."""
        # model fixture uses init_chance=50 on a fresh Cave — field evolves
        # with default limits; explicitly set one live cell to ensure non-final.
        model.cells[0][0] = 1
        assert model.is_final_generation() is False

    def test_is_final_generation_true_for_stable(self) -> None:
        """is_final_generation returns True for a provably stable field.

        All-zeros + birth_limit=7: max alive-neighbours = 5 (corner + borders),
        5 > 7 is False → no cell is ever born → field never changes.
        """
        stable = CaveFieldModel(
            rows=3,
            cols=3,
            cells=[[0, 0, 0], [0, 0, 0], [0, 0, 0]],
            birth_limit=7,
            death_limit=0,
        )
        assert stable.is_final_generation() is True

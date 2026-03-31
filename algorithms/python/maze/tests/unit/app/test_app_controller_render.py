"""Tests for AppController.render_maze and AppController.render_cave."""

from unittest.mock import MagicMock, patch

import pytest
from PyQt5.QtGui import QImage
from pytestqt.qtbot import QtBot

from app.controller.app_controller import AppController
from models.field import CaveFieldModel, MazeFieldModel

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def filled_cave_model() -> CaveFieldModel:
    """2x2 cave with live cells (is_empty() == False)."""
    cells = [[True, False], [False, True]]
    return CaveFieldModel(rows=2, cols=2, cells=cells)


@pytest.fixture
def empty_cave_model() -> CaveFieldModel:
    """Empty cave (all cells False, is_empty() == True)."""
    return CaveFieldModel(
        rows=3, cols=3, cells=[[False] * 3 for _ in range(3)], init_chance=40
    )


@pytest.fixture
def final_gen_cave_model() -> CaveFieldModel:
    """Cave that is already at its final generation
    (all-1 with birth_limit=4, death_limit=3).

    With all 8 neighbours alive, a live cell survives (8 >= death_limit=3),
    so the next generation is identical to the current one.
    """
    size = 4
    cells = [[True] * size for _ in range(size)]
    return CaveFieldModel(
        rows=size,
        cols=size,
        cells=cells,
        birth_limit=4,
        death_limit=3,
    )


# ---------------------------------------------------------------------------
# render_maze
# ---------------------------------------------------------------------------


class TestRenderMaze:
    """Tests for AppController.render_maze."""

    def test_emits_maze_rendered_signal(
        self, qtbot: QtBot, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        with qtbot.waitSignal(ctrl.maze_rendered, timeout=1000) as blocker:
            ctrl.render_maze(maze_model)

        assert len(blocker.args) == 1
        assert isinstance(blocker.args[0], QImage)
        assert not blocker.args[0].isNull()

    def test_updates_current_field_model(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        ctrl.render_maze(maze_model)
        assert ctrl.current_field_model is maze_model

    def test_updates_maze_rows_and_cols(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        ctrl.render_maze(maze_model)
        assert ctrl.maze_rows == maze_model.rows
        assert ctrl.maze_cols == maze_model.cols

    def test_sets_current_grider(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        ctrl.render_maze(maze_model)
        assert ctrl._solve.grider is not None

    def test_sets_base_maze_image(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        ctrl.render_maze(maze_model)
        assert ctrl._solve.base_image is not None
        assert isinstance(ctrl._solve.base_image, QImage)

    def test_resets_solve_state(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        # Pre-set the solver state
        ctrl._solve.start = (0, 0)
        ctrl._solve.end = (3, 3)
        ctrl._solve.path = [(0, 0), (1, 0)]

        ctrl.render_maze(maze_model)

        assert ctrl._solve.start is None
        assert ctrl._solve.end is None
        assert ctrl._solve.path is None

    def test_no_crash_on_exception(
        self, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        """render_maze must not propagate exceptions to the caller."""
        with patch(
            "app.controller.app_controller.MazeGrider",
            side_effect=RuntimeError("boom"),
        ):
            ctrl.render_maze(maze_model)  # must not raise

    def test_no_signal_on_exception(
        self, qtbot: QtBot, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        """On exception the maze_rendered signal must not be emitted."""
        with (
            patch(
                "app.controller.app_controller.MazeGrider",
                side_effect=RuntimeError("boom"),
            ),
            qtbot.assertNotEmitted(ctrl.maze_rendered),
        ):
            ctrl.render_maze(maze_model)

    def test_emits_error_on_exception(
        self, qtbot: QtBot, ctrl: AppController, maze_model: MazeFieldModel
    ) -> None:
        """On exception error_occurred is emitted with the error message."""
        with (
            patch(
                "app.controller.app_controller.MazeGrider",
                side_effect=RuntimeError("boom"),
            ),
            qtbot.waitSignal(ctrl.error_occurred, timeout=500) as blocker,
        ):
            ctrl.render_maze(maze_model)
        assert "boom" in blocker.args[0]


# ---------------------------------------------------------------------------
# render_cave
# ---------------------------------------------------------------------------


class TestRenderCave:
    """Tests for AppController.render_cave."""

    def test_filled_cave_emits_cave_rendered(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        filled_cave_model: CaveFieldModel,
    ) -> None:
        with qtbot.waitSignal(ctrl.cave_rendered, timeout=1000) as blocker:
            ctrl.render_cave(filled_cave_model)

        assert isinstance(blocker.args[0], QImage)
        assert not blocker.args[0].isNull()

    def test_filled_cave_updates_current_field_model(
        self, ctrl: AppController, filled_cave_model: CaveFieldModel
    ) -> None:
        ctrl.render_cave(filled_cave_model)
        assert ctrl.current_field_model is filled_cave_model

    def test_filled_cave_updates_rows_and_cols(
        self, ctrl: AppController, filled_cave_model: CaveFieldModel
    ) -> None:
        ctrl.render_cave(filled_cave_model)
        assert ctrl.cave_rows == filled_cave_model.rows
        assert ctrl.cave_cols == filled_cave_model.cols

    def test_filled_cave_does_not_emit_init_chance_changed(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        filled_cave_model: CaveFieldModel,
    ) -> None:
        with qtbot.assertNotEmitted(ctrl.init_chance_changed):
            ctrl.render_cave(filled_cave_model)

    def test_empty_cave_emits_init_chance_changed(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        empty_cave_model: CaveFieldModel,
    ) -> None:
        ctrl.cave_init_chance = 55

        with qtbot.waitSignal(
            ctrl.init_chance_changed, timeout=1000
        ) as blocker:
            ctrl.render_cave(empty_cave_model)

        assert blocker.args == [55]

    def test_empty_cave_does_not_mutate_model(
        self, ctrl: AppController, empty_cave_model: CaveFieldModel
    ) -> None:
        ctrl.cave_init_chance = 30
        original_init_chance = empty_cave_model.init_chance
        ctrl.render_cave(empty_cave_model)
        assert empty_cave_model.init_chance == original_init_chance

    def test_playback_disabled_on_final_generation(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        final_gen_cave_model: CaveFieldModel,
    ) -> None:
        """auto_play_active=True + final generation →
        cave_playback_enabled(False) is emitted."""
        ctrl.auto_play_active = True

        with qtbot.waitSignal(
            ctrl.cave_playback_enabled, timeout=500
        ) as blocker:
            ctrl.render_cave(final_gen_cave_model)

        assert blocker.args == [False]

    def test_auto_play_not_stopped_on_non_final_generation(
        self, ctrl: AppController, filled_cave_model: CaveFieldModel
    ) -> None:
        """auto_play_active=True + non-final generation →
        auto-play continues."""
        mock_cave = MagicMock()
        mock_cave.is_final_generation.return_value = False

        with patch.object(
            filled_cave_model, "get_cave", return_value=mock_cave
        ):
            ctrl.auto_play_active = True
            ctrl.render_cave(filled_cave_model)

        assert ctrl.auto_play_active is True

    def test_no_crash_on_exception(
        self, ctrl: AppController, filled_cave_model: CaveFieldModel
    ) -> None:
        """render_cave must not propagate exceptions to the caller."""
        with patch(
            "app.controller.app_controller.CaveGrider",
            side_effect=ValueError("bad"),
        ):
            ctrl.render_cave(filled_cave_model)  # must not raise

    def test_emits_error_on_exception(
        self,
        qtbot: QtBot,
        ctrl: AppController,
        filled_cave_model: CaveFieldModel,
    ) -> None:
        """On exception the error_occurred signal is emitted."""
        with (
            patch(
                "app.controller.app_controller.CaveGrider",
                side_effect=ValueError("bad"),
            ),
            qtbot.waitSignal(ctrl.error_occurred, timeout=1000) as blocker,
        ):
            ctrl.render_cave(filled_cave_model)

        assert "bad" in blocker.args[0]

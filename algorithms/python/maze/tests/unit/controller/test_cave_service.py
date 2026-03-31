"""Unit tests for CaveService — direct coverage of the service layer."""

import pytest

from controller.cave_service import CaveService
from models.field import CaveFieldModel
from utils.config import DEFAULT_BIRTH_LIMIT, DEFAULT_DEATH_LIMIT


def _make_model(
    rows: int = 3,
    cols: int = 3,
    cells: list[list[int]] | None = None,
    birth_limit: int = DEFAULT_BIRTH_LIMIT,
    death_limit: int = DEFAULT_DEATH_LIMIT,
) -> CaveFieldModel:
    if cells is None:
        cells = [[1, 0, 1], [0, 1, 0], [1, 0, 1]]
    return CaveFieldModel(
        rows=rows,
        cols=cols,
        cells=cells,
        birth_limit=birth_limit,
        death_limit=death_limit,
    )


svc = CaveService()


# ---------------------------------------------------------------------------
# update_birth_limit
# ---------------------------------------------------------------------------


class TestUpdateBirthLimit:
    def test_valid_value_sets_birth_limit(self) -> None:
        model = _make_model()
        CaveService.update_birth_limit(model, 5)
        assert model.birth_limit == 5

    def test_zero_is_valid(self) -> None:
        model = _make_model()
        CaveService.update_birth_limit(model, 0)
        assert model.birth_limit == 0

    def test_seven_is_valid(self) -> None:
        model = _make_model()
        CaveService.update_birth_limit(model, 7)
        assert model.birth_limit == 7

    def test_eight_raises_value_error(self) -> None:
        model = _make_model()
        with pytest.raises(ValueError):
            CaveService.update_birth_limit(model, 8)

    def test_negative_raises_value_error(self) -> None:
        model = _make_model()
        with pytest.raises(ValueError):
            CaveService.update_birth_limit(model, -1)


# ---------------------------------------------------------------------------
# update_death_limit
# ---------------------------------------------------------------------------


class TestUpdateDeathLimit:
    def test_valid_value_sets_death_limit(self) -> None:
        model = _make_model()
        CaveService.update_death_limit(model, 2)
        assert model.death_limit == 2

    def test_eight_raises_value_error(self) -> None:
        model = _make_model()
        with pytest.raises(ValueError):
            CaveService.update_death_limit(model, 8)

    def test_negative_raises_value_error(self) -> None:
        model = _make_model()
        with pytest.raises(ValueError):
            CaveService.update_death_limit(model, -1)


# ---------------------------------------------------------------------------
# next_generation
# ---------------------------------------------------------------------------


class TestNextGeneration:
    def test_evolving_field_returns_new_model(self) -> None:
        """When the field changes, a new CaveFieldModel is returned.

        Configuration [[1,0,1],[0,1,0],[1,0,1]] with default limits evolves:
        dead cell (0,1) has 5 alive neighbours (2 borders + 3 live cells)
        which exceeds birth_limit=4, so it becomes alive → field changes.
        """
        model = _make_model(
            rows=3,
            cols=3,
            cells=[[1, 0, 1], [0, 1, 0], [1, 0, 1]],
        )
        result = CaveService.next_generation(model)
        assert result is not model

    def test_final_generation_returns_same_model(self) -> None:
        """When field does not change, the SAME model object is returned.

        All-zeros with birth_limit=7: the maximum alive-neighbour count for
        any cell is 5 (corner cell + 5 border neighbours).  5 > 7 is False,
        so no dead cell is ever born → field is provably stable.
        """
        model = _make_model(
            rows=3,
            cols=3,
            cells=[[0, 0, 0], [0, 0, 0], [0, 0, 0]],
            birth_limit=7,
            death_limit=0,
        )
        result = CaveService.next_generation(model)
        assert result is model

    def test_next_generation_preserves_birth_death_limits(self) -> None:
        """The returned model carries the same birth/death limits."""
        model = _make_model(birth_limit=2, death_limit=1)
        result = CaveService.next_generation(model)
        assert result.birth_limit == 2
        assert result.death_limit == 1

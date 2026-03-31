"""Tests for Cave — cellular automaton generation and evolution."""

# python3 -m pytest tests/test_cave.py -v
# python3 -m pytest --cov=core tests/test_cave.py -v
# python3 -m pytest --cov=core --cov-report=term-missing tests/test_cave.py -v
# python3 -m pytest --cov=core --cov-report=html tests/test_cave.py -vs

import pytest

from core.cave import Cave
from utils.config import BIRTH_DEATH_LIMITS


def test_alive_neighbors() -> None:
    """Checks count_alive_neighbors for boundary and interior
    cells of all-dead and mixed fields."""
    # 1
    cave = Cave(rows=3, cols=3, field_mtx=[[0, 0, 0], [0, 0, 0], [0, 0, 0]])

    assert cave.count_alive_neighbors(0, 0) == 5
    assert cave.count_alive_neighbors(0, 1) == 3
    assert cave.count_alive_neighbors(0, 2) == 5
    assert cave.count_alive_neighbors(1, 0) == 3
    assert cave.count_alive_neighbors(1, 1) == 0
    assert cave.count_alive_neighbors(1, 2) == 3
    assert cave.count_alive_neighbors(2, 0) == 5
    assert cave.count_alive_neighbors(2, 1) == 3
    assert cave.count_alive_neighbors(2, 2) == 5

    # 2
    field = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
    cave = Cave(rows=3, cols=3, field_mtx=field)

    assert cave.count_alive_neighbors(1, 1) == 8
    assert cave.count_alive_neighbors(0, 0) == 7
    assert cave.count_alive_neighbors(1, 0) == 7


def test_next_generation() -> None:
    """Verifies next_generation and is_final_generation
    for 1×1 and 3×3 caves."""
    # 1
    field = [[1]]
    cave = Cave(rows=1, cols=1, field_mtx=field, death_limit=3, birth_limit=4)

    next_cave = cave.next_generation()

    assert next_cave.field[0][0] == 1

    assert cave.is_final_generation()
    assert next_cave.is_final_generation()

    # 2
    field = [[0]]
    cave = Cave(rows=1, cols=1, field_mtx=field, death_limit=3, birth_limit=4)

    next_cave = cave.next_generation()

    assert next_cave.field[0][0] == 1

    assert not cave.is_final_generation()
    assert next_cave.is_final_generation()

    # 3
    field = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
    cave = Cave(rows=3, cols=3, field_mtx=field, death_limit=3, birth_limit=4)
    next_cave = cave.next_generation()

    assert next_cave.field[1][1] == 0

    assert not cave.is_final_generation()


def test_generate_rand_field() -> None:
    """Checks that generate_rand_field produces a 0/1 matrix
    of the correct size."""
    cave = Cave(rows=5, cols=10)
    cave.generate_rand_field()

    assert len(cave.field) == 5
    assert all(len(row) == 10 for row in cave.field)

    for row in cave.field:
        for cell in row:
            assert cell in (0, 1), f"Invalid value {cell} in field"


def test_validate_field() -> None:
    """Checks that _validate_field raises ValueError
    for out-of-range cell values."""
    cave = Cave(3, 3)
    cave.field[1][1] = 10

    with pytest.raises(ValueError, match="Invalid cell in field"):
        cave._validate_field()


def test_validate_limits() -> None:
    """Checks that valid limits 0–7 are accepted
    and invalid ones raise ValueError."""
    for limit in BIRTH_DEATH_LIMITS:
        try:
            cave = Cave(rows=3, cols=3, birth_limit=limit, death_limit=limit)
        except ValueError:
            pytest.fail(f"Cave creation failed with valid limit {limit}")

        assert cave.birth_limit == limit
        assert cave.death_limit == limit

    with pytest.raises(ValueError, match="Birth limit -1 is invalid"):
        Cave(rows=3, cols=3, birth_limit=-1, death_limit=3)

    with pytest.raises(ValueError, match="Birth limit 8 is invalid"):
        Cave(rows=3, cols=3, birth_limit=8, death_limit=3)

    with pytest.raises(ValueError, match="Death limit -1 is invalid"):
        Cave(rows=3, cols=3, birth_limit=3, death_limit=-1)

    with pytest.raises(ValueError, match="Death limit 8 is invalid"):
        Cave(rows=3, cols=3, birth_limit=3, death_limit=8)

    with pytest.raises(ValueError, match="Birth limit -1 is invalid"):
        Cave(rows=3, cols=3, birth_limit=-1, death_limit=9)


def test_repr_() -> None:
    """Checks that __repr__ includes rows, cols, field,
    birth_limit, and death_limit."""
    field = [[1, 0], [0, 1]]
    cave = Cave(rows=2, cols=2, field_mtx=field, birth_limit=4, death_limit=3)

    repr_str = repr(cave)

    assert repr_str.startswith("Cave(")
    assert repr_str.endswith(")")
    assert "rows=2" in repr_str
    assert "cols=2" in repr_str
    assert "field=" in repr_str
    assert "birth_limit=4" in repr_str
    assert "death_limit=3" in repr_str


def test_visualize_and_str() -> None:
    """Checks visualize for an empty cave and a 2×2 field;
    verifies __str__ delegates to visualize."""
    # 1
    cave = Cave(rows=0, cols=0)
    assert cave.visualize() == "Empty cave"

    # 2
    field = [[0, 1], [1, 0]]
    cave = Cave(rows=2, cols=2, field_mtx=field)

    result = cave.visualize()
    lines = result.split("\n")

    assert (
        "  " in lines[1] or "│   │" not in lines[1]
    )  # difficult to check precisely
    assert lines[1] == "│   # │"

    # __str__
    result_str = str(cave)
    assert result_str == result


def test_get_init_chance() -> None:
    """Checks that the default init_chance is 50."""
    cave = Cave(rows=3, cols=3, birth_limit=4, death_limit=3)
    # 1
    assert cave.init_chance == 50


def test_next_generation_preserves_init_chance() -> None:
    """next_generation() must propagate init_chance to the child cave."""
    field = [[1, 0], [0, 1]]
    cave = Cave(rows=2, cols=2, field_mtx=field, init_chance=75)
    next_cave = cave.next_generation()
    assert next_cave.init_chance == 75

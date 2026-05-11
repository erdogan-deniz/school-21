"""Unit tests for ``utilities.functions`` — pairwise similarity helper."""

import pandas as pd

from utilities.functions import top_similar_vectors


def test_top_similar_vectors_orders_by_cosine_similarity() -> None:
    """Two identical rows must come back as the top pair."""
    df = pd.DataFrame(
        {
            "a": [1.0, 0.0, 1.0, 0.0],
            "b": [0.0, 1.0, 0.0, 1.0],
            "c": [1.0, 0.0, 1.0, 0.5],
        },
        index=["doc0", "doc1", "doc2", "doc3"],
    )

    # doc0 and doc2 are identical (cos_sim = 1.0); they should be the top pair.
    top = top_similar_vectors(df, n=1)
    assert top is not None
    assert len(top) == 1
    assert sorted(top[0]) == ["doc0", "doc2"]


def test_top_similar_vectors_respects_n() -> None:
    df = pd.DataFrame(
        {"x": [1.0, 0.0, 0.0], "y": [0.0, 1.0, 0.0], "z": [0.0, 0.0, 1.0]},
        index=["a", "b", "c"],
    )

    # All three vectors are orthogonal; cos_sim = 0 for every pair.
    # n=2 must return exactly 2 pairs, n=3 must return 3.
    assert len(top_similar_vectors(df, n=2)) == 2
    assert len(top_similar_vectors(df, n=3)) == 3


def test_top_similar_vectors_default_n_is_10() -> None:
    """With 5 docs there are C(5,2)=10 pairs; the default n=10 returns all."""
    df = pd.DataFrame(
        {"v": [1.0, 2.0, 3.0, 4.0, 5.0], "w": [5.0, 4.0, 3.0, 2.0, 1.0]},
        index=list("abcde"),
    )

    result = top_similar_vectors(df)
    assert result is not None
    assert len(result) == 10

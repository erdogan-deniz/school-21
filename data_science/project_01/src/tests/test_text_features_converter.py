"""Unit tests for ``TextToFeaturesConverter`` — sklearn-backed methods.

The four encoding methods split cleanly by dependency weight:

  * ``one_hot_texts_encoding`` / ``word_count_texts_encoding`` /
    ``tfidf_texts_encoding`` — pure sklearn ``CountVectorizer`` /
    ``TfidfVectorizer``. Fit in microseconds on a 3-doc fixture.
  * ``vectorize_text_tokens`` / ``vectorize_texts`` — need a trained
    gensim ``Word2Vec`` model. Even at ``min_count=1`` the training
    loop runs for several seconds on tiny corpora — not worth gating
    every PR on. Skipped here; covered by the notebooks instead.

``initialize_tools`` is small enough that its post-state can be
asserted (the four model attributes flip from None to non-None).
"""

import pandas as pd
import pytest
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer

from models.text_features_converter import TextToFeaturesConverter


@pytest.fixture
def converter() -> TextToFeaturesConverter:
    """Pre-wire the sklearn vectorizers; skip the gensim Word2Vec init."""
    conv = TextToFeaturesConverter()
    conv.bin_cnt_vectorizer = CountVectorizer(binary=True)
    conv.cnt_vectorizer = CountVectorizer()
    conv.tfidf_model = TfidfVectorizer()
    return conv


@pytest.fixture
def texts() -> pd.Series:
    """Three-doc mini-corpus with overlap so feature counts are non-trivial."""
    return pd.Series(["alpha beta", "alpha gamma", "beta gamma delta"])


class TestOneHotTextsEncoding:
    def test_shape_matches_vocabulary(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.one_hot_texts_encoding(texts)
        # 3 docs × 4 unique tokens (alpha, beta, gamma, delta).
        assert df.shape == (3, 4)

    def test_values_are_binary(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.one_hot_texts_encoding(texts)
        # binary=True → every cell is 0 or 1, even if a word repeats.
        assert set(df.values.flatten().tolist()) <= {0, 1}

    def test_known_token_present(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.one_hot_texts_encoding(texts)
        # "alpha" appears in docs 0 and 1, not in doc 2.
        assert df["alpha"].tolist() == [1, 1, 0]


class TestWordCountTextsEncoding:
    def test_shape(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.word_count_texts_encoding(texts)
        assert df.shape == (3, 4)

    def test_counts_repeat_tokens(
        self, converter: TextToFeaturesConverter
    ) -> None:
        # "alpha alpha" in doc 0 should produce a count of 2 for that cell.
        texts = pd.Series(["alpha alpha", "alpha beta"])
        df = converter.word_count_texts_encoding(texts)
        assert df["alpha"].tolist() == [2, 1]


class TestTfidfTextsEncoding:
    def test_shape(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.tfidf_texts_encoding(texts)
        assert df.shape == (3, 4)

    def test_values_nonnegative(
        self, converter: TextToFeaturesConverter, texts: pd.Series
    ) -> None:
        df = converter.tfidf_texts_encoding(texts)
        # TF-IDF is non-negative by construction.
        assert (df.values >= 0).all()


class TestInitializeTools:
    def test_sets_all_four_models(self) -> None:
        conv = TextToFeaturesConverter()
        assert conv.tfidf_model is None
        assert conv.cnt_vectorizer is None
        assert conv.bin_cnt_vectorizer is None
        assert conv.vectorizer is None

        conv.initialize_tools(vec_size=50, window_size=3)

        # All four model attributes now hold real instances.
        assert isinstance(conv.tfidf_model, TfidfVectorizer)
        assert isinstance(conv.cnt_vectorizer, CountVectorizer)
        assert isinstance(conv.bin_cnt_vectorizer, CountVectorizer)
        # Word2Vec carries the vec_size we passed in.
        assert conv.vectorizer is not None
        assert conv.vectorizer.vector_size == 50
        assert conv.vectorizer.window == 3

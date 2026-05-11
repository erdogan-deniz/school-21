"""Unit tests for ``TextPreprocessor`` — the lightweight methods only.

``clean_text`` is a static method with no external dependencies (pure
string operations), so it tests in microseconds. ``stem_text`` needs
``PorterStemmer`` from nltk, which initialises instantly (no model
download).

Heavy methods that require spaCy / SymSpell model loads
(``tokenize_text``, ``lemmatize_text``, ``correct_text``) are skipped
here on purpose — they belong to a separate slow-test suite that
isn't gated on every PR.
"""

import pytest

from models.text_preprocessor import TextPreprocessor


class TestCleanText:
    """``TextPreprocessor.clean_text`` — static, pure string transform."""

    def test_empty_string(self) -> None:
        assert TextPreprocessor.clean_text("") == ""

    def test_already_clean(self) -> None:
        assert TextPreprocessor.clean_text("hello world") == "hello world"

    def test_lowercases(self) -> None:
        assert TextPreprocessor.clean_text("Hello World") == "hello world"

    def test_strips_punctuation(self) -> None:
        assert TextPreprocessor.clean_text("Hello, world!") == "hello world"

    def test_strips_digits(self) -> None:
        assert TextPreprocessor.clean_text("test 123 text") == "test  text"

    def test_preserves_apostrophe(self) -> None:
        # Apostrophe must survive — downstream tokenizer relies on it
        # to split contractions correctly (don't → do + n't).
        assert TextPreprocessor.clean_text("don't stop") == "don't stop"

    def test_collapses_multiple_spaces(self) -> None:
        assert TextPreprocessor.clean_text("hello    world") == "hello world"

    def test_strips_leading_trailing_whitespace(self) -> None:
        assert TextPreprocessor.clean_text("  hello world  ") == "hello world"

    def test_combined(self) -> None:
        result = TextPreprocessor.clean_text("  Hello, World! 123  ")
        assert result == "hello world"

    def test_non_string_input_returns_none(self) -> None:
        # Decorator catches TypeError + returns None via handle_errors path.
        # The static method itself doesn't have a self.handle_errors call,
        # but clean_text catches TypeError explicitly inside its try block.
        assert TextPreprocessor.clean_text(None) is None


class TestStemText:
    """``TextPreprocessor.stem_text`` — Porter stemming, no model load."""

    @pytest.fixture
    def preprocessor(self) -> TextPreprocessor:
        """Bootstrap with just the stemmer (skip the spaCy/SymSpell loads)."""
        from nltk.stem import PorterStemmer

        prep = TextPreprocessor()
        prep.stemmer = PorterStemmer()
        return prep

    def test_simple_stem(self, preprocessor: TextPreprocessor) -> None:
        # Porter stemmer: "running" -> "run", "runs" -> "run".
        # "ran" is irregular and Porter does NOT handle it.
        assert preprocessor.stem_text("running runs ran") == "run run ran"

    def test_plural_to_singular(self, preprocessor: TextPreprocessor) -> None:
        assert preprocessor.stem_text("cats dogs") == "cat dog"

    def test_single_word(self, preprocessor: TextPreprocessor) -> None:
        assert preprocessor.stem_text("running") == "run"

    def test_empty_string(self, preprocessor: TextPreprocessor) -> None:
        assert preprocessor.stem_text("") == ""

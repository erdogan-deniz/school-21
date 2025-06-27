"""
`Tag` analysis test suite.

Examples of usage:
    >>> pytest tag.py
    >>> pytest tag.py -v
    >>> pytest tag.py -m calculations -v
"""


import os
import sys
import json
import pytest

sys.path.append(
    os.path.dirname(
        os.path.dirname(__file__, ),
    ),
)

from src.movielens_analysis.models.tag import Tag


@pytest.mark.tag
class TestTag:
    """
    Tests for a `Tag` class.

    :Attributes:
        tags (Tag): A instance of the `Tag` class.
        correct_answers (dict | None): A correct answers for tests.
    """

    @pytest.fixture(autouse=True)
    def prepare_test_class(self) -> None:
        """
        Automatically initializes a `Tag` instance before each test.
        """

        self.tags: Tag = Tag(file_path="data/datasets/", )

        self.tags.load_data()
        self.tags.load_users_ids()
        self.tags.load_movies_ids()
        self.tags.load_tags()
        self.tags.load_timestamps()

        with open(
            "data/test/expected/tag.json",
            'r',
            encoding="utf-8",
        ) as file:
            self.correct_answers: dict | None = json.load(file, )

    @pytest.mark.returned_data_types
    def test_tag_returned_data_types(self) -> None:
        """
        Validate returned data types for `Tag` class methods.
        """

        # Tag.get_most_words_tags():
        assert isinstance(self.tags.get_most_words_tags(), dict, )

        # Tag.get_longest_tags():
        assert isinstance(self.tags.get_longest_tags(), list, )

        # Tag.get_most_words_and_longest_tags():
        assert isinstance(self.tags.get_most_words_and_longest_tags(), list, )

        # Tag.get_popular_tags():
        assert isinstance(self.tags.get_popular_tags(), dict, )

        # Tag.get_unique_with_word_tags(word=" in ", ):
        assert isinstance(
            self.tags.get_unique_with_word_tags(word=" in ", ),
            list,
        )

    @pytest.mark.sequence_elements_data_types
    def test_tag_sequence_elements_data_types(self) -> None:
        """
        Validate elements data type in collections returned by `Tag` methods.
        """

        # Tag.get_most_words_tags():
        assert isinstance(
            list(self.tags.get_most_words_tags().keys(), )[0], str,
        )
        assert isinstance(
            list(self.tags.get_most_words_tags().values(), )[0], int,
        )

        # Tag.get_longest_tags():
        assert isinstance(self.tags.get_longest_tags()[0], str, )

        # Tag.get_most_words_and_longest_tags():
        assert isinstance(self.tags.get_most_words_and_longest_tags()[0], str, )

        # Tag.get_popular_tags():
        assert isinstance(
            list(self.tags.get_popular_tags().keys(), )[0], str,
        )
        assert isinstance(
            list(self.tags.get_popular_tags().values(), )[0], int,
        )

        # Tag.get_unique_with_word_tags(word=" in ", ):
        assert isinstance(
            self.tags.get_unique_with_word_tags(word=" in ", )[0], str,
        )

    @pytest.mark.returned_data_sorting
    def test_tag_returned_data_sorting(self) -> None:
        """
        Validate elements data type in collections returned by `Tag` methods.
        """

        # Tag.get_most_words_tags(cnt=5, ):
        assert dict(sorted(
            self.correct_answers["get_most_words_tags"].items(),
            key=lambda tag_data: -tag_data[1],
        ), ) == self.tags.get_most_words_tags(cnt=5, )

        # Tag.get_longest_tags(cnt=5, ):
        assert sorted(
            self.correct_answers["get_longest_tags"],
            key=len,
            reverse=True,
        ) == self.tags.get_longest_tags(cnt=5, )

        # Tag.get_most_words_and_longest_tags(cnt=2, ):
        assert sorted(
            self.correct_answers["get_most_words_and_longest_tags"],
            key=len,
            reverse=True,
        ) == self.tags.get_most_words_and_longest_tags(cnt=2, )

        # Tag.get_popular_tags(cnt=4, ):
        assert dict(sorted(
            self.correct_answers["get_popular_tags"].items(),
            key=lambda tag_data: -tag_data[1],
        ), ) == self.tags.get_popular_tags(cnt=4, )

        # Tag.get_unique_with_word_tags(word=" in ", ):
        assert sorted(
            self.correct_answers["get_unique_with_word_tags_in"],
        ) == self.tags.get_unique_with_word_tags(word=" in ", )

    @pytest.mark.calculations
    def test_tag_calculations(self) -> None:
        """
        Validate calculation accuracy for `Tag` class methods.
        """

        # Tag.get_most_words_tags(cnt=5, ):
        assert self.tags.get_most_words_tags(
            cnt=5,
        ) == self.correct_answers["get_most_words_tags"]

        # Tag.get_longest_tags(cnt=5, ):
        assert self.tags.get_longest_tags(
            cnt=5,
        ) == self.correct_answers["get_longest_tags"]

        # Tag.get_most_words_and_longest_tags(cnt=2, ):
        assert self.tags.get_most_words_and_longest_tags(
            cnt=2,
        ) == self.correct_answers["get_most_words_and_longest_tags"]

        # Tag.get_popular_tags(cnt=4, ):
        assert self.tags.get_popular_tags(
            cnt=4,
        ) == self.correct_answers["get_popular_tags"]

        # Tag.get_unique_with_word_tags(word=" in ", ):
        assert self.tags.get_unique_with_word_tags(
            word=" in ",
        ) == self.correct_answers["get_unique_with_word_tags_in"]

        # Tag.get_unique_with_word_tags(word=" the ", ):
        assert self.tags.get_unique_with_word_tags(
            word=" the ",
        ) == self.correct_answers["get_unique_with_word_tags_the"]

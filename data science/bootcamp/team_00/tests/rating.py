"""
`Rating` analysis test suite.

Examples of usage:
    >>> pytest rating.py
    >>> pytest rating.py -v
    >>> pytest rating.py -m calculations -v
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

from src.movielens_analysis.models.rating import Rating


@pytest.mark.rating
class TestRating:
    """
    Tests for a `Rating` class.

    :Attributes:
        ratings (Rating): A instance of the `Rating` class.
        correct_answers (dict | None): A correct answers for tests.
    """

    @pytest.fixture(autouse=True)
    def prepare_test_class(self) -> None:
        """
        Automatically initializes a `Rating` instance before each test.
        """

        self.ratings: Rating = Rating(file_path="data/datasets/", )

        self.ratings.load_data()
        self.ratings.load_users_ids()
        self.ratings.load_movies_ids()
        self.ratings.load_ratings()
        self.ratings.load_timestamps()

        with open(
            "data/test/expected/rating.json",
            'r',
            encoding="utf-8",
        ) as file:
            self.correct_answers: dict | None = json.load(file, )

    @pytest.mark.returned_data_types
    def test_rating_returned_data_types(self) -> None:
        """
        Validate returned data types for `Rating` class methods.
        """

        # Rating.get_top_release_years():
        assert isinstance(self.ratings.get_top_release_years(), dict, )

        # Rating.get_top_ratings():
        assert isinstance(self.ratings.get_top_ratings(), dict, )

    @pytest.mark.sequence_elements_data_types
    def test_rating_sequence_elements_data_types(self) -> None:
        """
        Validate elements data type in collections returned by `Rating` methods.
        """

        # Rating.get_top_release_years():
        assert isinstance(
            list(self.ratings.get_top_release_years().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.ratings.get_top_release_years().values(), )[0],
            int,
        )

        # Rating.get_top_ratings():
        assert isinstance(
            list(self.ratings.get_top_ratings().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.ratings.get_top_ratings().values(), )[0],
            int,
        )

    @pytest.mark.returned_data_sorting
    def test_rating_returned_data_sorting(self) -> None:
        """
        Validate order for `Rating` methods that returns collections.
        """

        # Rating.get_top_release_years():
        assert dict(sorted(
            self.correct_answers["get_top_release_years"].items(),
            key=lambda year_data: -year_data[1],
        ), ) == self.ratings.get_top_release_years()

        # Rating.get_top_ratings():
        assert dict(sorted(
            self.correct_answers["get_top_ratings"].items(),
            key=lambda rating_data: -rating_data[1],
        ), ) == self.ratings.get_top_ratings()

    @pytest.mark.calculations
    def test_rating_calculations(self) -> None:
        """
        Validate calculation accuracy for `Rating` class methods.
        """

        # Rating.get_top_release_years():
        assert self.ratings.get_top_release_years(
        ) == self.correct_answers["get_top_release_years"]

        # Rating.get_top_ratings():
        assert self.ratings.get_top_ratings(
        ) == self.correct_answers["get_top_ratings"]

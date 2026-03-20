"""
`Link` analysis test suite.

Examples of usage:
    >>> pytest link.py
    >>> pytest link.py -v
    >>> pytest link.py -m calculations -v
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

from src.movielens_analysis.models.link import Link
from src.utils import extract_price_from_string, extract_minutes_from_string


@pytest.mark.link
class TestLink:
    """
    Tests for a `Link` class.

    :Attributes:
        links (Link): A instance of the `Link` class.
        correct_answers (dict | None): A correct answers for tests.
    """

    @pytest.fixture(autouse=True)
    def prepare_test_class(self) -> None:
        """
        Automatically initializes a `Link` instance before each test.
        """

        self.links: Link = Link(file_path="data/datasets/", )

        self.links.load_data()
        self.links.load_movies_ids()
        self.links.load_imdb_ids()
        self.links.load_tmdb_ids()
        self.links.load_movies_data(movies_ids=[
            "0114709",
            "0114709",  # Copy for tests
            "0114709",  # Copy for tests
            "0114709",  # Copy for tests
            "0114709",  # Copy for tests
            "0113497",
            "0113497",
            "0113497",  # Copy for tests
            "0113497",  # Copy for tests
            "0113228",
            "0113228",  # Copy for tests
            "0113228",  # Copy for tests
            "0114885",
            "0114885",  # Copy for tests
            "0113041",
            "0113277",
            "0114319",
            "0112302",
            "0114576",
            "0113189",
        ], )

        with open(
            "data/test/expected/link.json",
            'r',
            encoding="utf-8",
        ) as file:
            self.correct_answers: dict | None = json.load(file, )

    @pytest.mark.returned_data_types
    def test_link_returned_data_types(self) -> None:
        """
        Validate returned data types for `Link` class methods.
        """

        # Link.get_popular_directors():
        assert isinstance(self.links.get_popular_directors(), dict, )

        # Link.get_most_expensive_movies():
        assert isinstance(self.links.get_most_expensive_movies(), dict, )

        # Link.get_most_profitable_movies():
        assert isinstance(self.links.get_most_profitable_movies(), dict, )

        # Link.get_most_longest_movies():
        assert isinstance(self.links.get_most_longest_movies(), dict, )

        # Link.get_top_cost_per_minute_movies():
        assert isinstance(self.links.get_top_cost_per_minute_movies(), dict, )

    @pytest.mark.sequence_elements_data_types
    def test_link_sequence_elements_data_types(self) -> None:
        """
        Validate elements data type in collections returned by `Link` methods.
        """

        # Link.get_popular_directors():
        assert isinstance(
            list(self.links.get_popular_directors().keys(), )[0], str,
        )
        assert isinstance(
            list(self.links.get_popular_directors().values(), )[0], int,
        )

        # Link.get_most_expensive_movies():
        assert isinstance(
            list(self.links.get_most_expensive_movies().keys(), )[0], str,
        )
        assert isinstance(
            list(self.links.get_most_expensive_movies().values(), )[0], str,
        )

        # Link.get_most_profitable_movies():
        assert isinstance(
            list(self.links.get_most_profitable_movies().keys(), )[0], str,
        )
        assert isinstance(
            list(self.links.get_most_profitable_movies().values(), )[0], int,
        )

        # Link.get_most_longest_movies():
        assert isinstance(
            list(self.links.get_most_longest_movies().keys(), )[0], str,
        )
        assert isinstance(
            list(self.links.get_most_longest_movies().values(), )[0], str,
        )

        # Link.get_top_cost_per_minute_movies():
        assert isinstance(
            list(self.links.get_top_cost_per_minute_movies().keys(), )[0], str,
        )
        assert isinstance(
            list(self.links.get_top_cost_per_minute_movies().values(), )[0],
            float,
        )

    @pytest.mark.returned_data_sorting
    def test_link_returned_data_sorting(self) -> None:
        """
        Validate order for `Link` methods that returns collections.
        """

        # Link.get_popular_directors(cnt=4, ):
        assert dict(sorted(
            self.correct_answers["get_popular_directors"].items(),
            key=lambda director: -director[1],
        ), ) == self.links.get_popular_directors(cnt=4, )

        # Link.get_most_expensive_movies(cnt=5, ):
        assert dict(sorted(
            self.correct_answers["get_most_expensive_movies"].items(),
            key=lambda movie: extract_price_from_string(movie[1], ),
        ), ) == self.links.get_most_expensive_movies(cnt=5, )

        # Link.get_most_profitable_movies(cnt=5, ):
        assert dict(sorted(
            self.correct_answers["get_most_profitable_movies"].items(),
            key=lambda movie: movie[1], ),
        ) == self.links.get_most_profitable_movies(cnt=5, )

        # Link.get_most_longest_movies(cnt=5, ):
        assert dict(sorted(
            self.correct_answers["get_most_longest_movies"].items(),
            key=lambda movie: -extract_minutes_from_string(movie[1], ), ),
        ) == self.links.get_most_longest_movies(cnt=5, )

        # Link.get_top_cost_per_minute_movies(cnt=5, ):
        assert dict(sorted(
            self.correct_answers["get_top_cost_per_minute_movies"].items(),
            key=lambda movie: movie[1], ),
        ) == self.links.get_top_cost_per_minute_movies(cnt=5, )

    @pytest.mark.calculations
    def test_link_calculations(self) -> None:
        """
        Validate calculation accuracy for `Link` class methods.
        """

        # Link.get_popular_directors(cnt=4, ):
        assert self.links.get_popular_directors(
            cnt=4,
        ) == self.correct_answers["get_popular_directors"]

        # Link.get_most_expensive_movies(cnt=5, ):
        assert self.links.get_most_expensive_movies(
            cnt=5,
        ) == self.correct_answers["get_most_expensive_movies"]

        # Link.get_most_profitable_movies(cnt=5, ):
        assert self.links.get_most_profitable_movies(
            cnt=5,
        ) == self.correct_answers["get_most_profitable_movies"]

        # Link.get_most_longest_movies(cnt=5, ):
        assert self.links.get_most_longest_movies(
            cnt=5,
        ) == self.correct_answers["get_most_longest_movies"]

        # Link.get_top_cost_per_minute_movies(cnt=5, ):
        assert self.links.get_top_cost_per_minute_movies(
            cnt=5,
        ) == self.correct_answers["get_top_cost_per_minute_movies"]

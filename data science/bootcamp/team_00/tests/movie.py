"""
`Movie` analysis test suite.

Examples of usage:
    >>> pytest movie.py
    >>> pytest movie.py -v
    >>> pytest movie.py -m calculations -v
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

from typing import OrderedDict

from src.movielens_analysis.models.movie import Movie


@pytest.mark.movie
class TestMovie:
    """
    Tests for a `Movie` class.

    :Attributes:
        movies (Movie): A instance of the `Movie` class.
        correct_answers (dict | None): A correct answers for tests.
    """

    @pytest.fixture(autouse=True)
    def prepare_test_class(self) -> None:
        """
        Automatically initializes a `Movie` instance before each test.
        """

        self.movies: Movie = Movie(file_path="data/datasets/", )

        self.movies.load_data()
        self.movies.load_movies_ids()
        self.movies.load_titles()
        self.movies.load_genres()

        with open(
            "data/test/expected/movie.json",
            'r',
            encoding="utf-8",
        ) as file:
            self.correct_answers: dict | None = json.load(file, )

    @pytest.mark.returned_data_types
    def test_movie_returned_data_types(self) -> None:
        """
        Validate returned data types for `Movie` class methods.
        """

        # Movie.get_release_years_movie_counts():
        assert isinstance(
            self.movies.get_release_years_movie_counts(),
            OrderedDict,
        )

        # Movie.get_genres_counts():
        assert isinstance(self.movies.get_genres_counts(), dict, )

        # Movie.get_most_genres_movies():
        assert isinstance(self.movies.get_most_genres_movies(), dict, )

        # Movie.get_most_ratings_movies():
        assert isinstance(self.movies.get_most_ratings_movies(), dict, )

        # Movie.get_top_ratings_metric_features():
        assert isinstance(self.movies.get_top_ratings_metric_features(), dict, )

    @pytest.mark.sequence_elements_data_types
    def test_movie_sequence_elements_data_types(self) -> None:
        """
        Validate elements data type in collections returned by `Movie` methods.
        """

        # Movie.get_release_years_movie_counts():
        assert isinstance(
            list(self.movies.get_release_years_movie_counts().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.movies.get_release_years_movie_counts().values(), )[0],
            int,
        )

        # Movie.get_genres_counts():
        assert isinstance(
            list(self.movies.get_genres_counts().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.movies.get_genres_counts().values(), )[0],
            int,
        )

        # Movie.get_most_genres_movies():
        assert isinstance(
            list(self.movies.get_most_genres_movies().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.movies.get_most_genres_movies().values(), )[0],
            int,
        )

        # Movie.get_most_ratings_movies():
        assert isinstance(
            list(self.movies.get_most_ratings_movies().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.movies.get_most_ratings_movies().values(), )[0],
            int,
        )

        # Movie.get_top_ratings_metric_features():
        assert isinstance(
            list(self.movies.get_top_ratings_metric_features().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.movies.get_top_ratings_metric_features().values(), )[0],
            float,
        )

    @pytest.mark.returned_data_sorting
    def test_movie_returned_data_sorting(self) -> None:
        """
        Validate order for `Movie` methods that returns collections.
        """

        # Movie.get_release_years_movie_counts():
        assert dict(sorted(
            self.correct_answers["get_release_years_movie_counts"].items(),
            key=lambda movie_data: -movie_data[1],
        ), ) == self.movies.get_release_years_movie_counts()

        # Movie.get_genres_counts():
        assert dict(sorted(
            self.correct_answers["get_genres_counts"].items(),
            key=lambda movie_data: -movie_data[1],
        ), ) == self.movies.get_genres_counts()

        # Movie.get_most_genres_movies():
        assert dict(sorted(
            self.correct_answers["get_most_genres_movies"].items(),
            key=lambda movie_data: -movie_data[1],
        ), ) == self.movies.get_most_genres_movies()

        # Movie.get_most_ratings_movies():
        assert dict(sorted(
            self.correct_answers["get_most_ratings_movies"].items(),
            key=lambda movie_data: -movie_data[1],
        ), ) == self.movies.get_most_ratings_movies()

        # Movie.get_top_ratings_metric_features():
        assert dict(sorted(
            self.correct_answers["get_top_ratings_metric_features_mean"].items(
            ),
            key=lambda movie_data: -movie_data[1],
        ), ) == self.movies.get_top_ratings_metric_features()

    @pytest.mark.calculations
    def test_movie_calculations(self) -> None:
        """
        Validate calculation accuracy for `Movie` class methods.
        """

        # Movie.get_release_years_movie_counts():
        assert self.movies.get_release_years_movie_counts(
        ) == self.correct_answers["get_release_years_movie_counts"]

        # Movie.get_genres_counts():
        assert self.movies.get_genres_counts(
        ) == self.correct_answers["get_genres_counts"]

        # Movie.get_most_genres_movies():
        assert self.movies.get_most_genres_movies(
        ) == self.correct_answers["get_most_genres_movies"]

        # Movie.get_most_ratings_movies():
        assert self.movies.get_most_ratings_movies(
        ) == self.correct_answers["get_most_ratings_movies"]

        # Movie.get_top_ratings_metric_features(metric="min", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="min",
        ) == self.correct_answers["get_top_ratings_metric_features_min"]

        # Movie.get_top_ratings_metric_features(metric="max", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="max",
        ) == self.correct_answers["get_top_ratings_metric_features_max"]

        # Movie.get_top_ratings_metric_features(metric="mean", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="mean",
        ) == self.correct_answers["get_top_ratings_metric_features_mean"]

        # Movie.get_top_ratings_metric_features(metric="median", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="median",
        ) == self.correct_answers["get_top_ratings_metric_features_median"]

        # Movie.get_top_ratings_metric_features(metric="var", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="var",
        ) == self.correct_answers["get_top_ratings_metric_features_var"]

        # Movie.get_top_ratings_metric_features(metric="std", ):
        assert self.movies.get_top_ratings_metric_features(
            metric="std",
        ) == self.correct_answers["get_top_ratings_metric_features_std"]

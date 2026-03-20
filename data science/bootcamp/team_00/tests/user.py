"""
`User` analysis test suite.

Examples of usage:
    >>> pytest user.py
    >>> pytest user.py -v
    >>> pytest user.py -m calculations -v
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

from src.movielens_analysis.models.user import User


@pytest.mark.user
class TestUser:
    """
    Tests for a `User` class.

    :Attributes:
        users (User): A instance of the `User` class.
        correct_answers (dict | None): A correct answers for tests.
    """

    @pytest.fixture(autouse=True)
    def prepare_test_class(self) -> None:
        """
        Automatically initializes a `User` instance before each test.
        """

        self.user: User = User(file_path="data/datasets/", )

        with open(
            "data/test/expected/user.json",
            'r',
            encoding="utf-8",
        ) as file:
            self.correct_answers: dict | None = json.load(file, )

    @pytest.mark.returned_data_types
    def test_user_returned_data_types(self) -> None:
        """
        Validate returned data types for `User` class methods.
        """

        # User.get_users_rating_counts():
        assert isinstance(self.user.get_users_rating_counts(), dict, )

        # User.get_top_ratings_metric_users():
        assert isinstance(self.user.get_top_ratings_metric_users(), dict, )

    @pytest.mark.sequence_elements_data_types
    def test_user_sequence_elements_data_types(self) -> None:
        """
        Validate elements data type in collections returned by `User` methods.
        """

        # User.get_users_rating_counts():
        assert isinstance(
            list(self.user.get_users_rating_counts().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.user.get_users_rating_counts().values(), )[0],
            int,
        )

        # User.get_top_ratings_metric_users():
        assert isinstance(
            list(self.user.get_top_ratings_metric_users().keys(), )[0],
            str,
        )
        assert isinstance(
            list(self.user.get_top_ratings_metric_users().values(), )[0],
            float,
        )

    @pytest.mark.returned_data_sorting
    def test_user_returned_data_sorting(self) -> None:
        """
        Validate order for `User` methods that returns collections.
        """

        # User.get_users_rating_counts():
        assert dict(sorted(
            self.correct_answers["get_users_rating_counts"].items(),
            key=lambda user_data: user_data[1],
        ), ) == self.user.get_users_rating_counts()

        # User.get_top_ratings_metric_users(metric="min", ):
        assert dict(sorted(
            self.correct_answers["get_top_ratings_metric_users_min"].items(),
            key=lambda user_data: -user_data[1],
        ), ) == self.user.get_top_ratings_metric_users(metric="min", )

    @pytest.mark.calculations
    def test_user_calculations(self) -> None:
        """
        Validate calculation accuracy for `User` class methods.
        """

        # User.get_users_rating_counts():
        assert self.user.get_users_rating_counts(
        ) == self.correct_answers["get_users_rating_counts"]

        # User.get_top_ratings_metric_users(metric="min", ):
        assert self.user.get_top_ratings_metric_users(
            metric="min",
        ) == self.correct_answers["get_top_ratings_metric_users_min"]

        # User.get_top_ratings_metric_users(metric="max", ):
        assert self.user.get_top_ratings_metric_users(
            metric="max",
        ) == self.correct_answers["get_top_ratings_metric_users_max"]

        # User.get_top_ratings_metric_users(metric="mean", ):
        assert self.user.get_top_ratings_metric_users(
            metric="mean",
        ) == self.correct_answers["get_top_ratings_metric_users_mean"]

        # User.get_top_ratings_metric_users(metric="median", ):
        assert self.user.get_top_ratings_metric_users(
            metric="median",
        ) == self.correct_answers["get_top_ratings_metric_users_median"]

        # User.get_top_ratings_metric_users(metric="var", ):
        assert self.user.get_top_ratings_metric_users(
            metric="var",
        ) == self.correct_answers["get_top_ratings_metric_users_var"]

        # User.get_top_ratings_metric_users(metric="std", ):
        assert self.user.get_top_ratings_metric_users(
            metric="std",
        ) == self.correct_answers["get_top_ratings_metric_users_std"]

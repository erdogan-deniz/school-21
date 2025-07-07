"""
`User` data analysis module.

Examples of usage:
    >>> inst: User = User(file_path="data/datasets/", )

    >>> print(inst.get_users_rating_counts(), )
    >>> print(inst.get_top_ratings_metric_users(), )
"""


import os
import sys

sys.path.append(
    os.path.normpath(
        os.path.join(
            os.path.dirname(
                os.path.abspath(__file__, ),
            ),
            '..',
            '..',
            '..',
        ),
    ),
)

from typing import Literal

from src.movielens_analysis.models.movie import Movie
from src.movielens_analysis.models.rating import Rating


class User(Movie):
    """
    A class for analyzing and processing users data from `.csv` file.
    """

    def get_users_rating_counts(self) -> dict[str, int] | None:
        """
        Retives users rating counts.

        :Returns:
            dict[str, int]:
                Keys (str): Users IDs.
                Values (int): Count of user ratings.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            inst: Rating = Rating(file_path=self.file_path, )

            inst.load_users_ids()

            users_rating_cnts: dict[str, int] = {
                user_id: inst.users_ids.count(user_id, )
                for user_id in set(inst.users_ids, )
            }

            return dict(sorted(
                users_rating_cnts.items(),
                key=lambda user_rating_cnt: user_rating_cnt[1],
            ), )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_top_ratings_metric_users(
        self,
        cnt: int = 10,
        metric: Literal[
            "min",
            "max",
            "mean",
            "median",
            "var",
            "std",
        ] = "mean"
    ) -> dict[str, float] | None:
        """
        Retrieves top users by rating metric.

        :Parameters:
            cnt (int): Number of users to return.
                       Default: 10.
            metric (Literal["min", "max", "mean", "median", "var", "std", ]):
                Statistical metric to calculate.
                Default: "mean".

        :Returns:
            dict[str, float]:
                Keys (str): Users IDs.
                Values (float): Metric values.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.load_titles()
            self.load_movies_ids()

            return self.get_top_ratings_metric_features(
                cnt=cnt,
                metric=metric,
                target_feat = "userId",
            )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

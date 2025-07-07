"""
`Movie` data analysis module.

Examples of usage:
    >>> inst: Movie = Movie(file_path="data/datasets/", )

    >>> inst.load_data()
    >>> inst.load_movies_ids()
    >>> inst.load_titles()
    >>> inst.load_genres()

    >>> inst.print_data()
    >>> inst.print_movies_ids()
    >>> inst.print_titles()
    >>> inst.print_genres()

    >>> print(inst.get_release_years_movie_counts(), )
    >>> print(inst.get_genres_counts(), )
    >>> print(inst.get_most_genres_movies(), )
    >>> print(inst.get_most_ratings_movies(), )
    >>> print(inst.get_top_ratings_metric_features(), )
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

from re import error, compile
from typing import Any, Literal
from collections import (
    Counter,
    OrderedDict,
    defaultdict,
)

from src.utils import calculate_metric
from src.movielens_analysis.models.rating import Rating


class Movie:
    """
    A class for analyzing and processing movies data from `.csv` file.

    :Attributes:
        file_path (str): Path to the directory containing the `.csv` file.
        file (str): `.csv` file containing movies data.
                    Default: "movies.csv".

        data (list): Movies data rows.
                     Default: None.
        movies_ids (list): Movies IDs.
                           Default: None.
        titles (list): Titles.
                       Default: None.
        genres (list[list]]): Genres.
                              Default: None.
    """

    def __init__(
        self,
        file_path: str,
        file: str = "movies.csv"
    ) -> None:
        """
        Initializes the `Movie` analyzer.

        :Parameters:
            file_path (str): Path to the directory containing the `.csv` file.
            file (str): `.csv` file containing movies data.
                        Default: "movies.csv".
        """

        self.file_path: str = file_path
        self.file: str = file

        self.data: list | None = None
        self.movies_ids: list | None = None
        self.titles: list | None = None
        self.genres: list[list] | None = None

    def load_data(self, size: int = 1000) -> None:
        """
        Loads and stores a subset of data from the `.csv` file.

        :Parameters:
            size (int): Number of data rows to load (excluding header).
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file can not be read.
            Exception: All other errors.
        """

        try:
            with open(
                file=self.file_path + self.file,
                mode='r',
                encoding="utf-8",
            ) as file:
                next(file, )  # Skip header

                self.data = [
                    line.rstrip()
                    for line, _ in zip(file, range(size, ), )
                ]
        except FileNotFoundError as file_not_found_err:
            print("FileNotFoundError:", file_not_found_err, )
        except IOError as io_err:
            print("IOError:", io_err, )
        except Exception as err:
            print("Exception:", err, )

    def load_movies_ids(self, size: int = 1000) -> None:
        """
        Loads movies IDs from a `.csv` file.

        :Parameters:
            size (int): Number of movies IDs to load.
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file can not be read.
            IndexError: When lines do not contain expected columns.
            Exception: All other errors.
        """

        try:
            with open(
                file=self.file_path + self.file,
                mode='r',
                encoding="utf-8",
            ) as file:
                next(file, )  # Skip header

                self.movies_ids = [
                    line.rstrip().split(',', )[0]
                    for line, _
                    in zip(file, range(size, ), )
                ]
        except FileNotFoundError as file_not_found_err:
            print("FileNotFoundError:", file_not_found_err, )
        except IOError as io_err:
            print("IOError:", io_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def load_titles(self,  size: int = 1000) -> None:
        """
        Loads movies titles from a `.csv` file.

        :Parameters:
            size (int): Number of movies titles to load.
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file can not be read.
            IndexError: When lines do not contain expected columns.
            Exception: All other errors.
        """

        try:
            self.titles = []
            title_regex: Any = compile(r'(?:^|,)(?:"([^"]+)"|([^",]+))', )

            with open(
                file=self.file_path + self.file,
                mode='r',
                encoding="utf-8",
            ) as file:
                next(file, )  # Skip header

                for idx, title in enumerate(file, ):
                    if idx >= size:
                        break

                    title_matches: list | None = title_regex.findall(
                        title.strip(),
                    )
                    title: list[str] = [
                        match[0] or match[1]
                        for match in title_matches
                        if match[0] or match[1]
                    ]

                    if len(title, ) > 1:
                        self.titles.append(title[1], )
        except FileNotFoundError as file_not_found_err:
            print("FileNotFoundError:", file_not_found_err, )
        except IOError as io_err:
            print("IOError:", io_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def load_genres(self, size: int = 1000) -> None:
        """
        Loads movies genres from a `.csv` file.

        :Parameters:
            size (int): Number of movies genres to load.
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file can not be read.
            IndexError: When lines do not contain expected columns.
            Exception: All other errors.
        """

        try:
            with open(
                file=self.file_path + self.file,
                mode='r',
                encoding="utf-8",
            ) as file:
                next(file, )  # Skip header

                self.genres = [
                    line.rstrip().split(',', )[-1].split('|', )
                    for line, _
                    in zip(file, range(size, ), )
                ]
        except FileNotFoundError as file_not_found_err:
            print("FileNotFoundError:", file_not_found_err, )
        except IOError as io_err:
            print("IOError:", io_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_data(self) -> None:
        """
        Prints the stored data.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, data in enumerate(self.data, 1, ):
                print(f"row index: {idx}, movie data: {data}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_movies_ids(self) -> None:
        """
        Prints the stored movies IDs.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, movie_id in enumerate(self.movies_ids, 1, ):
                print(f"row index: {idx}, movie ID: {movie_id}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_titles(self) -> None:
        """
        Prints the stored movies titles.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, title in enumerate(self.titles, 1, ):
                print(f"row index: {idx}, movie title: {title}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_genres(self) -> None:
        """
        Prints the stored movies genres.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, genre in enumerate(self.genres, 1, ):
                print(f"row index: {idx}, movie genres: {genre}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_release_years_movie_counts(self) -> OrderedDict[str, int] | None:
        """
        Retrives years from movie titles in order of frequency.

        :Returns:
            OrderedDict[str, int]:
                Keys (str): Movies release years.
                Values (int): Movies counts.
            None: If error occurs or no data is loaded.

        :Exceptions:
            RegexError: When used regular expression raised exception.
            AttributeError: When used data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            years_with_cnts: defaultdict = defaultdict(int, )
            year_regex: Any = compile(r'\((\d{4})\)[^()]*$', )

            for title in self.titles:
                year_matches: list | None = year_regex.search(title, )
                years_with_cnts[year_matches.group(1, )] += 1

            return OrderedDict(sorted(
                years_with_cnts.items(),
                key=lambda year_with_cnt: -year_with_cnt[1],
            ), )
        except error as regex_err:
            print("RegexError:", regex_err, )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_genres_counts(self) -> dict[str, int] | None:
        """
        Retrives genres frequency counts sorted.

        :Returns:
            dict[str, int]:
                Keys (str): Movie genres.
                Values (int): Occurrences count.
            None: If error occurs or no data is loaded.

        :Exceptions:
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            genres: list = [
                genre
                for sublist in self.genres
                for genre in sublist
            ]

            return dict(Counter(genres, ).most_common(), )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_genres_movies(self, cnt: int = 10) -> dict[str, int] | None:
        """
        Retrieves top movies by genre count.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Movies titles.
                Values (int): Genres counts.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            genres_cnts: dict[str, int] = {
                title: len(genres, )
                for title, genres
                in dict(zip(self.titles, self.genres, ), ).items()
            }

            return dict(sorted(
                genres_cnts.items(),
                key=lambda cnt: -cnt[1],
            )[: cnt], )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_ratings_movies(self, cnt: int = 10) -> dict[str, int] | None:
        """
        Retrieves top movies by rating count sorted.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Movies titles.
                Values (int): Received ratings counts.
            None: If an error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            inst: Rating = Rating(file_path=self.file_path, )

            inst.load_movies_ids()

            movies_with_ids: dict[str, int] = dict(zip(
                self.titles,
                self.movies_ids,
            ), )

            return dict(sorted({
                    title: inst.movies_ids.count(ratings_cnt, )
                    for title, ratings_cnt
                    in movies_with_ids.items()
                }.items(),
                key=lambda ratings_cnt: -ratings_cnt[1],
            )[: cnt], )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_top_ratings_metric_features(
        self,
        cnt: int = 10,
        metric: Literal[
            "min",
            "max",
            "mean",
            "median",
            "var",
            "std",
        ] = "mean",
        target_feat: Literal["movieId", "userId", ] = "movieId"
    ) -> dict[str, float] | None:
        """
        Retrieve top target feature values by rating metric.

        :Parameters:
            cnt (int): Number of top to return.
                       Default: 10.
            metric (Literal["min", "max", "mean", "median", "var", "std", ]):
                Statistical metric to calculate.
                Default: "mean".
            target_feat (Literal["movieId", "userId", ] ): Target feature for
                                                           calculations.
                                                           Default: "movieId".

        :Returns:
            dict[str, float]:
                Keys (str): Target feature values.
                Values (float): Metric values.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            res: dict[str, float] = {}
            inst: Rating = Rating(file_path=self.file_path, )

            inst.load_ratings()

            if target_feat == "movieId":
                inst.load_movies_ids()

                movies_data: dict[str, str] = dict(zip(
                    self.movies_ids,
                    self.titles,
                ), )
                movies_ratings: dict[str, str] = list(zip(
                    inst.movies_ids,
                    inst.ratings,
                ), )

                for movie_id in movies_data.keys():
                    movie_ratings: list[float] = []

                    for rating in movies_ratings:
                        if rating[0] == movie_id:
                            movie_ratings.append(float(rating[1], ), )

                    res[movie_id] = calculate_metric(
                        vals=movie_ratings,
                        metric=metric,
                    )
            elif target_feat == "userId":
                inst.load_users_ids()

                users_with_ratings: dict[str, str] = list(zip(
                    inst.users_ids,
                    inst.ratings,
                ), )

                for user_id in inst.users_ids:
                    user_ratings: list[float] = []

                    for user_with_rating in users_with_ratings:
                        if user_with_rating[0] == user_id:
                            user_ratings.append(float(user_with_rating[1], ), )

                    res[user_id] = calculate_metric(
                        vals=user_ratings,
                        metric=metric,
                    )

            clean_res: dict[str, float] = {
                title: metric_val
                for title, metric_val
                in res.items()
                if metric_val is not None
            }

            return dict(sorted(
                clean_res.items(),
                key=lambda pair: -pair[1],
            )[: cnt], )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

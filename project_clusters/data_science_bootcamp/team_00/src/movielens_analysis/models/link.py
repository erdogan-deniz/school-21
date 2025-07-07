"""
`Link` data analysis module.

Examples of usage:
    >>> inst: Link = Link(file_path="data/datasets/", )

    >>> inst.load_data()
    >>> inst.load_movies_ids()
    >>> inst.load_imdb_ids()
    >>> inst.load_tmdb_ids()
    >>> inst.load_movies_data(movies_ids=[
    >>>     "0113189",
    >>>     "0114057",
    >>>     "0113819",
    >>>     "0118055",
    >>>     "0106402",
    >>>     "0110455",
    >>> ], )

    >>> inst.print_data()
    >>> inst.print_movies_ids()
    >>> inst.print_imdb_ids()
    >>> inst.print_tmdb_ids()
    >>> inst.print_extracted_fields()
    >>> inst.print_movies_data()

    >>> print(inst.get_popular_directors(), )
    >>> print(inst.get_most_expensive_movies(), )
    >>> print(inst.get_most_profitable_movies(), )
    >>> print(inst.get_most_longest_movies(), )
    >>> print(inst.get_top_cost_per_minute_movies(), )
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
from collections import defaultdict

from src.parse_utils import fetch_movies_webpage_text_fields
from src.utils import extract_price_from_string, extract_minutes_from_string


class Link:
    """
    A class for analyzing and processing links data from `.csv` file.

    :Attributes:
        file_path (str): Path to the directory containing the `.csv` file.
        file (str): `.csv` file containing links data.
                    Default: "links.csv".

        data (list): Raw links data.
                     Default: None.
        movies_ids (list): Movies IDs.
                           Default: None.
        imdb_ids (list): IMDB IDs.
                         Default: None.
        tmdb_ids (list): TMDB IDs.
                         Default: None.

        extr_fields (list): Extracted fields.
                            Default: None.
        movies_data (list): Movies data.
                            Default: None.
    """

    def __init__(
        self,
        file_path: str,
        file: str = "links.csv"
    ) -> None:
        """
        Initializes the `Link` analyzer.

        :Parameters:
            file_path (str): Path to the directory containing the `.csv` file.
            file (str): `.csv` file containing links data.
                        Default: "links.csv".
        """

        self.file_path: str = file_path
        self.file: str = file

        self.data: list | None = None
        self.movies_ids: list | None = None
        self.imdb_ids: list | None = None
        self.tmdb_ids: list | None = None

        self.extr_fields: list | None = None
        self.movies_data: list | None = None

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
                    for line, _
                    in zip(file, range(size, ), )
                ]
        except FileNotFoundError as file_not_found_err:
            print("FileNotFoundError:", file_not_found_err, )
        except IOError as io_err:
            print("IOError:", io_err, )
        except Exception as err:
            print("Exception:", err, )

    def load_movies_ids(self, size: int = 1000) -> None:
        """
        Loads movies IDs from a `.csv` file and save them.

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

    def load_imdb_ids(self, size: int = 1000) -> None:
        """
        Loads IMDB IDs from a `.csv` file and save them.

        :Parameters:
            size (int): Number of IMDB IDs to load.
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

                self.imdb_ids = [
                    line.rstrip().split(',', )[1]
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

    def load_tmdb_ids(self, size: int = 1000) -> None:
        """
        Loads TMDB IDs from a `.csv` file and save them.

        :Parameters:
            size (int): Number of TMDB IDs to load.
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

                self.tmdb_ids = [
                    line.rstrip().split(',', )[2]
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

    def load_movies_data(
        self,
        movies_ids : list[str],
        fields: list[Literal["gross", "title", "budget", "rating", "writer",
                             "runtime", "release", "country", "director",
                             "language",
        ]] = [
            "gross",
            "title",
            "budget",
            "rating",
            "writer",
            "runtime",
            "release",
            "country",
            "director",
            "language",
        ]
    ) -> None:
        """
        Loads movies data from IMDB website.

        :Parameters:
            movies_ids (list[str]): Movies IDs.
            fields (list[Literal["gross", "title", "budget", "rating", "writers"
                                 ,"runtime",  "release", "country", "director",
                                 "language",
            ]]): Movies fields to extract.
                 Default: ["gross", "title","budget", "rating", "writer",
                           "runtime", "release", "country", "director",
                           "language",
                          ].

        :Exceptions:
            ValueError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.fields = fields
            self.movies_data = fetch_movies_webpage_text_fields(
                movies_ids=movies_ids,
                fields=fields,
                req_config_path=self.file_path.split("dataset", )[0],
            )
        except ValueError as val_err:
            print("ValueError:", val_err, )
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
                print(f"row index: {idx}, data: {data}", )
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
                print(f"row index: {idx}, movie_id: {movie_id}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_imdb_ids(self) -> None:
        """
        Prints the stored IMDB IDs.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, imdb_id in enumerate(self.imdb_ids, 1, ):
                print(f"row index: {idx}, IMDB ID: {imdb_id}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_tmdb_ids(self) -> None:
        """
        Prints the stored TMDB IDs.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, tmdb_id in enumerate(self.tmdb_ids, 1, ):
                print(f"row index: {idx}, TMDB ID: {tmdb_id}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_extracted_fields(self) -> None:
        """
        Prints the extracted movies fields.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            print(f"Extracted movies fields: {self.fields}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_movies_data(self) -> None:
        """
        Prints movies data.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, movie_data in enumerate(self.movies_data, 1, ):
                print(f"row index: {idx}, movie_data: {movie_data}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_popular_directors(self, cnt: int = 10) -> dict[str, int] | None:
        """
        Retrieves the most popular directors sorted by movie counts.

        :Parameters:
            cnt (int): Number of directors to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Directors.
                Values (int): Movie counts.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            IndexError: When lines do not contain expected columns.
            Exception: All other errors.
        """

        try:
            directors_idx: int = self.fields.index("director", ) + 1
            directors_with_cnts: defaultdict = defaultdict(int, )

            for movie_data in self.movies_data:
                directors_with_cnts[movie_data[directors_idx]] += 1

            return dict(sorted(
                directors_with_cnts.items(),
                key=lambda cnt: -cnt[1])[: cnt],
            )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_expensive_movies(self, cnt: int = 10) -> dict[str, str] | None:
        """
        Retrieves the highest budget movies sorted.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, str]:
                Keys (str): Movie title.
                Values (str): Movie budget.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            ValueError: When used invalid data format.
            IndexError: When lines do not contain expected columns.
            Exception: All other errors.
        """

        try:
            titles_idx: int = self.fields.index("title", ) + 1
            budgets_idx: int = self.fields.index("budget", ) + 1
            movies_with_budget: dict[str, str] = {
                movie_data[titles_idx]: movie_data[budgets_idx]
                for movie_data in self.movies_data
                if movie_data[budgets_idx]
            }

            return dict(sorted(
                movies_with_budget.items(),
                key=lambda movie: -extract_price_from_string(movie[1], ),
            )[: cnt], )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_profitable_movies(
        self,
        cnt: int = 10
    ) -> dict[str, int] | None:
        """
        Retrives the most profitable movies.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Movie title.
                Values (int): Movie profit.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            ValueError: When used invalid data format.
            IndexError: When data do not contain expected columns.
            Exception: All other errors.
        """

        try:
            gross_idx: int = self.fields.index("gross", ) + 1
            titles_idx: int = self.fields.index("title", ) + 1
            budgets_idx: int = self.fields.index("budget", ) + 1
            movies_with_diffs: dict[str, int] = {
                movie_data[titles_idx]:
                    extract_price_from_string(movie_data[gross_idx], ) -
                    extract_price_from_string(movie_data[budgets_idx], )
                for movie_data in self.movies_data
                if movie_data[gross_idx] is not None and
                   movie_data[budgets_idx] is not None
            }

            return dict(sorted(
                movies_with_diffs.items(),
                key=lambda movie_with_diff: -movie_with_diff[1],
            )[: cnt], )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_longest_movies(self, cnt: int = 10) -> dict[str, str] | None:
        """
        Retrieve the longest movies.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, str]:
                Keys (str): Movie title.
                Values (str): Movie runtime.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            ValueError: When used invalid data format.
            IndexError: When used data do not contain expected columns.
            Exception: All other errors.
        """

        try:
            titles_idx: int = self.fields.index("title", ) + 1
            runtimes_idx: int = self.fields.index("runtime", ) + 1
            movies_with_runtimes: dict[str, str] = {
                movie_data[titles_idx]: movie_data[runtimes_idx]
                for movie_data in self.movies_data
                if movie_data[runtimes_idx] is not None
            }

            return dict(sorted(
                movies_with_runtimes.items(),
                key=lambda movie_data: -extract_minutes_from_string(
                    movie_data[1],
                ),
            )[: cnt], )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_top_cost_per_minute_movies(
        self,
        cnt: int = 10
    ) -> dict[str, float] | None:
        """
        Retrives movies with the highest cost per minute.

        :Parameters:
            cnt (int): Number of movies to return.
                       Default: 10.

        :Returns:
            dict[str, float]:
                Keys (str): Movie title.
                Values (float): Minute cost.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            ValueError: When used invalid data format.
            IndexError: When used data do not contain expected columns.
            Exception: All other errors.
        """

        try:
            titles_idx: int = self.fields.index("title", ) + 1
            budgets_idx: int = self.fields.index("budget", ) + 1
            runtimes_idx: int = self.fields.index("runtime", ) + 1
            movies_min_costs: dict[str, float] = {}

            for movie_data in self.movies_data:
                title: str = movie_data[titles_idx]
                budget: float = extract_price_from_string(
                    movie_data[budgets_idx],
                )
                runtime: float = extract_minutes_from_string(
                    movie_data[runtimes_idx],
                )

                if None not in (budget, runtime, ):
                    movies_min_costs[title] = round(budget / runtime, 2, )

            return dict(sorted(
                movies_min_costs.items(),
                key=lambda movie_data: -movie_data[1],
            )[: cnt], )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except IndexError as idx_err:
            print("IndexError:", idx_err, )
        except Exception as err:
            print("Exception:", err, )

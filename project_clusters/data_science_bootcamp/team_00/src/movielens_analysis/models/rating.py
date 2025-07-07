"""
`Rating` data analysis module.

Examples of usage:
    >>> inst: Rating = Rating(file_path="data/datasets/", )

    >>> inst.load_data()
    >>> inst.load_users_ids()
    >>> inst.load_movies_ids()
    >>> inst.load_ratings()
    >>> inst.load_timestamps()

    >>> inst.print_data()
    >>> inst.print_users_ids()
    >>> inst.print_movies_ids()
    >>> inst.print_ratings()
    >>> inst.print_timestamps()

    >>> print(inst.get_top_release_years(), )
    >>> print(inst.get_top_ratings(), )
"""


from datetime import datetime


class Rating:
    """
    A class for analyzing and processing ratings data from `.csv` file.

    :Attributes:
        file_path (str): Path to the directory containing the `.csv` file.
        file (str): `.csv` file containing ratings data.
                    Default: "ratings.csv".

        data (list): Raw ratings data rows.
                     Default: None.
        users_ids (list): Users IDs.
                          Default: None.
        movies_ids (list): Movies IDs.
                           Default: None.
        ratings (list): Ratings values.
                        Default: None.
        tss (list): Timestamps values.
                    Default: None.
    """

    def __init__(
        self,
        file_path: str,
        file: str = "ratings.csv"
    ) -> None:
        """
        Initializes the `Rating` analyzer.

        :Parameters:
            file_path (str): Path to the directory containing the `.csv` file.
            file (str): `.csv` file containing ratings data.
                        Default: "ratings.csv".
        """

        self.file_path: str = file_path
        self.file: str = file

        self.data: list | None = None
        self.users_ids: list | None = None
        self.movies_ids: list | None = None
        self.ratings: list | None = None
        self.tss: list | None = None

    def load_data(self, size: int = 1000) -> None:
        """
        Loads and stores a subset of data rows from the `.csv` file.

        :Parameters:
            size (int): Number of data rows to load (excluding header).
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file cannot be read.
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

    def load_users_ids(self, size: int = 1000) -> None:
        """
        Loads users IDs from a `.csv` file.

        :Parameters:
            size (int): Number of users IDs to load.
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            IOError: When file cannot be read.
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

                self.users_ids = [
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

    def load_ratings(self, size: int = 1000) -> None:
        """
        Loads ratings from a `.csv` file.

        :Parameters:
            size (int): Number of ratings to load.
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

                self.ratings = [
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

    def load_timestamps(self, size: int = 1000) -> None:
        """
        Loads timestamps from a `.csv` file.

        :Parameters:
            size (int): Number of timestamps to load.
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

                self.tss = [
                    line.rstrip().split(',', )[3]
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
                print(f"row index: {idx}, data: {data}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_users_ids(self) -> None:
        """
        Prints the stored users IDs.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, user_id in enumerate(self.users_ids, 1, ):
                print(f"row index: {idx}, user ID: {user_id}", )
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

    def print_ratings(self) -> None:
        """
        Prints the stored ratings.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, rating in enumerate(self.ratings, 1, ):
                print(f"row index: {idx}, rating: {rating}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def print_timestamps(self) -> None:
        """
        Prints the stored timestamps.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, ts in enumerate(self.tss, 1, ):
                print(f"row index: {idx}, timestamp: {ts}", )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except UnicodeEncodeError as unicode_encode_err:
            print("UnicodeEncodeError:", unicode_encode_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_top_release_years(self) -> dict[str, int] | None:
        """
        Retrives movie release years from timestamps sorted chronologically.

        :Returns:
            dict[str, int]:
                Keys (str): Release years.
                Values (int): Count of ratings in that year.
            None: If an error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            years: list[str] = [
                datetime.fromtimestamp(int(ts, ), ).year
                for ts
                in self.tss
            ]

            return dict(sorted([
                (str(year, ), years.count(year, ), )
                for year
                in set(years, )
            ], ), )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_top_ratings(self) -> dict[str, int] | None:
        """
        Retrieves the most popular ratings sorted by values.

        :Returns:
            dict[str, int]:
                Keys (str): Ratings values.
                Values (int): Count of occurrences.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            ratings_freqs: dict[str, int] = {}

            for rating in self.ratings:
                ratings_freqs[rating] = ratings_freqs.get(rating, 0, ) + 1

            return dict(sorted(ratings_freqs.items(), ), )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

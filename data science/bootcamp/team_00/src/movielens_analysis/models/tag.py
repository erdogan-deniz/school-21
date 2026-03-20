"""
`Tag` data analysis module.

Examples of usage:
    >>> inst: Tag = Tag(file_path="data/datasets/", )

    >>> inst.load_data()
    >>> inst.load_users_ids()
    >>> inst.load_movies_ids()
    >>> inst.load_tags()
    >>> inst.load_timestamps()

    >>> inst.print_data()
    >>> inst.print_users_ids()
    >>> inst.print_movies_ids()
    >>> inst.print_tags()
    >>> inst.print_timestamps()

    >>> print(inst.get_most_words_tags(), )
    >>> print(inst.get_longest_tags(), )
    >>> print(inst.get_most_words_and_longest_tags(), )
    >>> print(inst.get_popular_tags(), )
    >>> print(inst.get_unique_with_word_tags(word=" in ", ), )
"""


class Tag:
    """
    A class for analyzing and processing tags data from `.csv` file.

    :Attributes:
        file_path (str): Path to the directory containing the `.csv` file.
        file (str): `.csv` file containing tags data.
                    Default: "tags.csv".

        data (list): Tags data rows.
                     Default: None.
        users_ids (list): Users IDs.
                          Default: None.
        movies_ids (list): Movies IDs.
                           Default: None.
        tags (list): Tags values.
                     Default: None.
        tss (list): Timestamps values.
                    Default: None.
    """

    def __init__(
        self,
        file_path: str,
        file: str = "tags.csv"
    ) -> None:
        """
        Initializes the `Tag` analyzer.

        :Parameters:
            file_path (str): Path to the directory containing the `.csv` file.
            file (str): `.csv` file containing tags data.
                        Default: "tags.csv".
        """

        self.file_path: str = file_path
        self.file: str = file

        self.data: list | None = None
        self.users_ids: list | None = None
        self.movies_ids: list | None = None
        self.tags: list | None = None
        self.tss: list | None = None

    def load_data(self, size: int = 1000) -> None:
        """
        Loads a subset of data rows from the `.csv` file.

        :Parameters:
            size (int): Number of data rows to load (excluding header).
                        Default: 1000.

        :Exceptions:
            FileNotFoundError: When specified file does not exist.
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

    def load_users_ids(self, size: int = 1000) -> None:
        """
        Loads users IDs from a `.csv` file.

        :Parameters:
            size (int): Number of users IDs to load.
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

    def load_tags(self, size: int = 1000) -> None:
        """
        Loads tags from a `.csv` file.

        :Parameters:
            size (int): Number of tags to load.
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

                self.tags = [
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

    def print_tags(self) -> None:
        """
        Prints the stored tags.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            UnicodeEncodeError: When used characters may not display.
            Exception: All other errors.
        """

        try:
            for idx, tag in enumerate(self.tags, 1, ):
                print(f"row index: {idx}, tag: {tag}", )
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

    def get_most_words_tags(self, cnt: int = 10) -> dict[str | int] | None:
        """
        Retrieves top tags containing the most words sorted.

        :Parameters:
            cnt (int): Number of tags to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Tags.
                Values (int): Words counts.
            None: If an error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            sorted_uniq_tags: list[str] = sorted(
                set(self.tags, ),
                key=lambda uniq_tag: -len(uniq_tag.strip().split(), ),
            )

            return {
                uniq_tag: len(uniq_tag.split(), )
                for uniq_tag
                in sorted_uniq_tags[: cnt]
            }
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_longest_tags(self, cnt: int = 10) -> list[str] | None:
        """
        Retrieves the longest tags sorted.

        :Parameters:
            cnt (int): Number of tags to return.
                       Default: 10.

        :Returns:
            list[str]: Longest tags ordered by length.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            return sorted(
                set(self.tags, ),
                key=len,
                reverse=True,
            )[: cnt]
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_most_words_and_longest_tags(
        self,
        cnt: int = 10
    ) -> list[str] | None:
        """
        Retrieves tags that rank highly in word count and length.

        :Parameters:
            cnt (int): Number of tags to return.
                       Default: 10.

        :Returns:
            list[str]: Tags.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            most_words_tags: dict[str | int] | None = self.get_most_words_tags(
                cnt= cnt ** 2,
            )
            longest_tags: list[str] | None = self.get_longest_tags(
                cnt=cnt ** 2,
            )

            return sorted(
                set(most_words_tags, ).intersection(longest_tags, ),
                key=lambda uniq_tag: (-len(uniq_tag, ), uniq_tag.lower(), ),
            )[: cnt]
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_popular_tags(self, cnt: int = 10) -> dict[str | int] | None:
        """
        Retrieves the most popular tags sorted.

        :Parameters:
            cnt (int): Number of tags to return.
                       Default: 10.

        :Returns:
            dict[str, int]:
                Keys (str): Tags.
                Values (int): Occurrence counts.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            tags_freqs: dict[str | int] = {}

            for tag in self.tags:
                tags_freqs[tag] = tags_freqs.get(tag, 0, ) + 1

            return dict(sorted(
                tags_freqs.items(),
                key=lambda item: (-item[1], item[0], ),
            )[: cnt], )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

    def get_unique_with_word_tags(self, word: str) -> list[str] | None:
        """
        Retrieves unique tags containing the word, sorted alphabetically.

        :Parameters:
            word (str): The word to search for within tags.

        :Returns:
            list[str]: Alphabetically sorted tags.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            AttributeError: When data attribute not initialized.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            return sorted(set([tag for tag in self.tags if word in tag], ), )
        except ValueError as val_err:
            print("ValueError:", val_err, )
        except AttributeError as attr_err:
            print("AttributeError:", attr_err, )
        except TypeError as type_err:
            print("TypeError:", type_err, )
        except Exception as err:
            print("Exception:", err, )

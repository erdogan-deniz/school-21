"""
`Matrix` model module.

Examples of usage:
    >>> matrix: Matrix = Matrix()

    >>> matrix.fill_matrix_from_file("matrix.txt", "data/", )
    >>> matrix.define_dimension()
    >>> print(matrix.count_matrix_squares(), )
    >>> print(matrix.count_matrix_circles(), )
"""


class Matrix:
    """
    Matrix class of data and operations.

    :Attributes:
        n (int | None): Matrix dimension.
                        Default: None.
        matrix (list): Matrix fields.
                       Default: None.
    """

    def __init__(
        self,
        n: int | None = None,
        matrix: list[list[int]] | None = None
    ) -> None:
        """
        Initializes the `Matrix` class representative.

        :Parameters:
            n (int | None): Matrix dimension.
                            Default: None.
            matrix (list[list[int]] | None): Matrix fields.
                                             Default: None.
        """

        self.n: int | None = n
        self.matrix: list = matrix or []

    def fill_matrix_from_file(
        self,
        file: str,
        file_path: str
    ) -> None:
        """
        Fill `Matrix` class representative with file matrix.

        :Parameters:
            file (str): File with matrix.
            file_path (str): A path to file with matrix.

        :Exceptions:
            FileNotFoundError: When used file does not exists.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        matrix_rows: list = []

        try:
            with open(
                encoding="utf-8",
                file=file_path + file,
            ) as file:
                matrix_rows = file.readlines()

            for matrix_row in matrix_rows:
                self.matrix.append(list(map(int, matrix_row.split(), ), ), )
        except FileNotFoundError  as file_not_found_err:
            raise FileNotFoundError (
                f"\nFile: {__file__}\n" +
                f"Message: {file_not_found_err}.",
            )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def define_dimension(self) -> None:
        """
        Sets the dimension of the matrix.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            NameError: When used invalid name of field.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.n = len(self.matrix, )
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
            )
        except NameError as name_err:
            raise NameError(
                f"\nFile: {__file__}\n" +
                f"Message: {name_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def count_matrix_squares(self) -> int | None:
        """
        Returns count of matrix squares.

        :Returns:
            int: Count of matrix squares.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When used index does not exist.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        squares_cnt: int = 0

        try:
            for idx in range(self.n - 1, ):
                for jdx in range(self.n - 1, ):
                    if (self.matrix[idx][jdx] == 1):
                        if (
                            (idx == 0) and (jdx == 0)
                        ) or (
                            (idx == 0) and (jdx != 0) and
                            (self.matrix[idx][jdx - 1] == 0) and
                            (self.matrix[idx + 1][jdx - 1] == 0)
                        ) or (
                            (idx != 0) and (jdx == 0) and
                            (self.matrix[idx - 1][jdx] == 0) and
                            (self.matrix[idx - 1][jdx + 1] == 0)
                        ) or (
                            (self.matrix[idx - 1][jdx] == 0) and
                            (self.matrix[idx - 1][jdx + 1] == 0) and
                            (self.matrix[idx][jdx - 1] == 0) and
                            (self.matrix[idx + 1][jdx - 1] == 0)
                        ):
                            squares_cnt += 1

            return squares_cnt
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
            )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def count_matrix_circles(self) -> int | None:
        """
        Returns count of matrix circles.

        :Returns:
            int: Count of matrix circles.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When used index does not exist.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        circles_cnt: int = 0

        try:
            for idx in range(self.n - 1, ):
                for jdx in range(self.n - 1, ):
                    if (self.matrix[idx][jdx] == 0):
                        if (
                            (self.matrix[idx][jdx + 1] == 1) and
                            (self.matrix[idx + 1][jdx] == 1)
                        ):
                            circles_cnt += 1

            return circles_cnt
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
            )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

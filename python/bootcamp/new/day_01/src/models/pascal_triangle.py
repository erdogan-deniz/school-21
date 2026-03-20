"""
`Pascal's triangle` model module.

Examples of usage:
    >>> triangle: PascalTriangle = PascalTriangle()

    >>> triangle.fill_rows_count()
    >>> 5
    >>> triangle.build_triangle()
    >>> triangle.print_triangle()
"""


class PascalTriangle:
    """
    Pascal's triangle class of data and operations.

    :Attributes:
        rows_cnt (int | None): A count of Pascal's triangle rows.
                               Default: None.
        rows (list[list[int]] | None): A rows of Pascal's triangle.
                                       Default: None.
    """

    def __init__(
        self,
        rows_cnt: int | None = None,
        rows: list[list[int]] | None = None
    ) -> None:
        """
        Initializes the `Pascal's triangle` class representative.

        :Parameters:
            rows_cnt (int | None): A count of Pascal's triangle rows.
                                   Default: None.
            rows (list[list[int]] | None): A rows of Pascal's triangle.
                                           Default: None.
        """

        self.rows_cnt: int | None = rows_cnt
        self.rows: list[list[int]] | None = rows or [[1, ], [1, 1, ], ]

    def fill_rows_count(self) -> None:
        """
        Fill `Pascal's triangle` class representative with a rows count.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            self.rows_cnt = int(input(), )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def build_triangle(self) -> None:
        """
        Create Pascal's triangle rows.

        :Exceptions:
            AttributeError: When used invalid data attribute.
            IndexError: When iterable object do not contain expected element.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            for idx in range(1, self.rows_cnt + 1, ):
                if idx > 2:
                    row: list[int] = [1, ]

                    for jdx in range(idx - 2, ):
                        row.append(
                            self.rows[-1][jdx] + self.rows[-1][jdx + 1],
                        )

                    row.append(1, )
                    self.rows.append(row, )
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
            )
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
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

    def print_triangle(self) -> None:
        """
        Prints Pascal's triangle rows.

        :Exceptions:
            AttributeError: When used invalid data attribute.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            for row in  self.rows:
                print(*row, )
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
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

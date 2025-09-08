"""
`Robot` model module.

Examples of usage:
    >>> robot: Robot = Robot()

    >>> robot.fill_robot_data()
    >>> 3 4
    >>> 3 0 2 1
    >>> 6 4 8 5
    >>> 3 3 6 0
    >>> print(robot.calculate_max_coins(), )
"""


class Robot:
    """
    Robot class of data and operations.

    :Attributes:
        n (int | None): A count of field rows.
                        Default: None.
        m (int | None): A count of field columns.
                        Default: None.
        field (list[list[int]] | None): A field of coins.
                                        Default: [].
    """

    def __init__(
        self,
        n: int | None = None,
        m: int | None = None,
        field: list[list[int]] | None = None
    ) -> None:
        """
        Initializes the `Robot` class representative.

        :Parameters:
            n (int | None): A count of field rows.
                            Default: None.
            m (int | None): A count of field columns.
                            Default: None.
            field (list[list[int]] | None): A field of coins.
                                            Default: None.
        """

        self.n: int | None = n
        self.m: int | None = m
        self.field: list | None = field or []

    def fill_robot_data(self) -> None:
        """
        Fill robot data from an user.

        :Exceptions:
            IndexError: When iterable object do not contain expected element.
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            self.n, self.m = map(int, input().split(), )

            for _ in range(self.n, ):
                row: list[int] = list(map(int, input().split(), ), )
                self.field.append(row, )
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
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def calculate_max_coins(self) -> float | None:
        """
        Determine from the given field how many coins the robot will collect.

        :Returns:
            float: The max collected coins.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When iterable object do not contain expected element.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            dp: list[list[int]] = [[0, ] * self.m for _ in range(self.n, )]
            dp[0][0] = self.field[0][0]

            for idx in range(1, self.m, ):
                dp[0][idx] = dp[0][idx - 1] + self.field[0][idx]

            for idx in range(1, self.n, ):
                dp[idx][0] = dp[idx - 1][0] + self.field[idx][0]

            for idx in range(1, self.n, ):
                for jdx in range(1, self.m, ):
                    dp[idx][jdx] = max(
                        dp[idx - 1][jdx],
                        dp[idx][jdx - 1],
                    ) + self.field[idx][jdx]

            return dp[self.n - 1][self.m - 1]
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

"""
`Polynomial` model module.

Examples of usage:
    >>> polynom: Polynomial = Polynomial()

    >>> polynom.fill_polynomial_data()
    >>> 2 3.0
    >>> 5
    >>> 1.2
    >>> -3
    >>> print(polynom.calculate_polynomial_derivative_at_point(), )
"""


class Polynomial:
    """
    Polynomial class of data and operations.

    :Attributes:
        dim (int | None): A polynomial dimension.
                          Default: None.
        point_val (float | None): A value of point for derivative calculation.
                                  Default: None.
        coeffs (list | None): A coefficients of polynomial.
                              Default: [].
    """

    def __init__(
        self,
        dim: int | None = None,
        point_val: float | None = None,
        coeffs: list[int] | None = None
    ) -> None:
        """
        Initializes the `Polynomial` class representative.

        :Parameters:
            dim (int | None): A polynomial dimension.
                              Default: None.
            point_val (float | None): A value of point for derivative
                                      calculation.
                                      Default: None.
            coeffs (list[int] | None): A coefficients of polynomial.
                                       Default: None.
        """

        self.dim: int | None = dim
        self.point_val: float | None = point_val
        self.coeffs: list | None = coeffs or []

    def fill_polynomial_data(self) -> None:
        """
        Fill polynomial data from an user.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.dim, self.point_val = map(float, input().split(), )
            self.dim = int(self.dim, )

            for _ in range(self.dim + 1, ):
                self.coeffs.append(float(input(), ), )

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

    def calculate_polynomial_derivative_at_point(self) -> float | None:
        """
        Returns the derivative of a polynomial at the point.

        :Returns:
            float: Calculated polynomial derivative at the point.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When iterable object do not contain expected element.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            idx: int = 0
            res: int = 0

            for n in range(self.dim, 0, -1, ):
                res += self.coeffs[idx] * n * self.point_val ** (n - 1)
                idx += 1

            return res
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

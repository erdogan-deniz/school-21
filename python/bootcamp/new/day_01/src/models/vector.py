"""
`Vector` model module.

Examples of usage:
    >>> vec_one: Vector = Vector()
    >>> vec_two: Vector = Vector()

    >>> vec_one.input_vector_coordinates()
    >>> 1.0 2.0 3.0
    >>> vec_two.input_vector_coordinates()
    >>> 4.0 5.0 6.0
    >>> print(vec.input_vector_coordinates(vec_one, vec_two, ), )
"""


from __future__ import annotations


class Vector:
    """
    Vector class of data and operations.

    :Attributes:
        dim (int): Vector dimension.
                   Default: 3.
        coords (list): Vector coordinates.
                       Default: [0.0, ].
    """

    def __init__(
        self,
        dim: int = 3,
        coords: list| None = None
    ) -> None:
        """
        Initializes the `Vector` class representative.

        :Parameters:
            dim (int): Vector dimension.
                       Default: 3.
            coords (list| None): Vector coordinates.
                                 Default: None.
        """

        self.dim: int = dim
        self.coords: list = coords or [0.0, ] * dim

    @staticmethod
    def calculate_vectors_scalar_product(
        vec_one: Vector,
        vec_two: Vector
    ) -> float | None:
        """
        Returns calculated scalar product of two vectors.

        :Parameters:
            vec_one (Vector): First vector class object.
            vec_two (Vector): Secodn vector class object.

        :Returns:
            float: Calculated scalar product of two vectors.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When data attribute not initialized.
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        scal_prod_val: float = 0

        try:
            scal_prod_val += sum(
                coord_vec_one * coord_vec_two
                for coord_vec_one, coord_vec_two in zip(
                    vec_one.coords,
                    vec_two.coords,
                    strict=True,
                )
            )

            return scal_prod_val
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
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

    def input_vector_coordinates(self) -> None:
        """
        Sets vectors coordinates.

        :Exceptions:
            ValueError: When used invalid data format.
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            self.coords = list(map(float, input().split(), ), )

            if len(self.coords, ) != self.dim:
                raise Exception(
                    f"\nFile: {__file__}\n" +
                    f"Message: incorrect vector dimension values.",
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

"""
Exercise 09: the derivative at a point - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from models.polynomial import Polynomial


def main() -> None:
    """
    Exercise 09 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        polynom: Polynomial = Polynomial()

        polynom.fill_polynomial_data()
        print(f"\n{polynom.calculate_polynomial_derivative_at_point():.3f}", )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

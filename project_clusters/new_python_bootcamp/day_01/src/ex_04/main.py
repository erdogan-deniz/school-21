"""
Exercise 04: a "Pascal's triangle" - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from models.pascal_triangle import PascalTriangle


def main() -> None:
    """
    Exercise 04 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        triangle: PascalTriangle = PascalTriangle()

        triangle.fill_rows_count()
        triangle.build_triangle()
        print()
        triangle.print_triangle()
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

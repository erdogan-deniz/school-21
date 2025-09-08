"""
Exercise 03: a figures - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from models.matrix import Matrix


def main() -> None:
    """
    Exercise 03 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        matrix: Matrix = Matrix()

        matrix.fill_matrix_from_file("matrix.txt", "data/", )
        matrix.define_dimension()
        print(
            f"\n{matrix.count_matrix_squares()} " +
            f"{matrix.count_matrix_circles()}",
        )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

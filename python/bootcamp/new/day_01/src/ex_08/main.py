"""
Exercise 08: a different numbers - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from utils import input_n_numbers


def main() -> None:
    """
    Exercise 08 solution function.

    :Exceptions:
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        nums: list[int] | None = input_n_numbers()

        print(f"\n{len(set(nums, ), )}", )
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


if __name__ == "__main__":
    main()

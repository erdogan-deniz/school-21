"""
Exercise 05: a string to float conversion - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from utils import convert_string_to_float


def main() -> None:
    """
    Exercise 05 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        user_input: str = input()

        print(f"\n{convert_string_to_float(user_input, ) * 2:.3f}", )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

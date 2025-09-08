"""
Exercise 02: a palindrome - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from utils import is_symmetric_list, convert_integer_to_list


def main() -> None:
    """
    Exercise 02 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        int_: int = int(input(), )
        conv_int: list | None = convert_integer_to_list(int_, )

        print(f"\n{is_symmetric_list(conv_int, )}", )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

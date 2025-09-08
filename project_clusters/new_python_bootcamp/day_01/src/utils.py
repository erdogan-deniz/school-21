"""
Module of utils.

Examples of usage:
    >>> print(is_symmetric_list([1, 2, 1, ], ), )
    >>> print(input_n_numbers(), )
    >>> print(convert_integer_to_list(123, ), )
    >>> print(convert_string_to_float("123.221", ), )
"""


def is_symmetric_list(lst: list) -> bool | None:
    """
    Checks if the list is symmetric.

    :Parameters:
        lst (list): List of elements.

    :Returns:
        bool: The answer to the question.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        return lst == lst[:: -1]
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

def input_n_numbers() -> list[int] | None:
    """
    Returns interger numbers.

    :Returns:
        list[int]: Entered integer numbers.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        nums: list = []
        n: int = int(input(), )

        for _ in range(n, ):
            nums.append(int(input(), ), )

        return nums
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

def convert_integer_to_list(int_: int) -> list | None:
    """
    Returns integer number digits.

    :Parameters:
        int_ (int): Integer number.

    :Returns:
        list: Converted integer number.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    conv_int: list = []

    try:
        if int_ < 0:
            conv_int.append("-", )

            int_ = -int_

        while (int_ > 0) or (len(conv_int, ) == 0):
            conv_int.append(int_ % 10, )

            int_ //= 10

        return conv_int
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

def convert_string_to_float(str_: str) -> float | None:
    """
    Returns float number, converted string.

    :Parameters:
        str_ (str): String containing float number.

    :Returns:
        float: Float number.
        None: If error occurs or no data is loaded.

    :Exceptions:
        IndexError: When used incorrect index.
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        num_sign: int = 1

        if str_[0] == '-':
            num_sign *= -1
            str_ = str_[1: ]

        res_int_part: int = 0
        res_fract_part: float = 0
        int_part, fract_part = str_.split('.', )
        int_part_degree: int = 10 ** (len(int_part, ) - 1)
        fract_part_degree: float = 10 ** -len(fract_part, )

        for digit in int_part:
            res_int_part += int_part_degree * int(digit, )
            int_part_degree //= 10

        for digit in fract_part[:: -1]:
            res_fract_part += fract_part_degree * int(digit, )
            fract_part_degree *= 10

        return (res_int_part + res_fract_part) * num_sign
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

"""
Module of utils.

Examples of usage:
    >>> print(get_min_value(vals=[1, 2, 3, ], ), )
    >>> print(get_max_value(vals=[1, 2, 3, ], ), )
    >>> print(calculate_mean_value(vals=[1, 2, 3, ], ), )
    >>> print(calculate_median_value(vals=[1, 2, 3, 4, ], ), )
    >>> print(calculate_variance_value(vals=[1, 2, 3, 4, ], ), )
    >>> print(calculate_std_value(vals=[1, 2, 3, 4, ], ), )
    >>> print(calculate_metric(vals=[1, 2, 3, 4, ], ), )
    >>> print(extract_minutes_from_string(time="11 hour 4 minutes", ), )
    >>> print(extract_price_from_string(price="$11,000,000", ), )
"""


from re import search
from typing import Literal


def get_min_value(vals: list[int | float]) -> int | float | None:
    """
    Return the minimum value in a list of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        int | float: The minimum value.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        return min(vals, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def get_max_value(vals: list[int | float]) -> int | float | None:
    """
    Return the maximum value in a list of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        int | float: The maximum value.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        return max(vals, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def calculate_mean_value(vals: list[int | float]) -> float | None:
    """
    Calculate the mean of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        float: The mean value rounded to 2 decimal places.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ZeroDivisionError: When divide number on zero.
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        return round(sum(vals, ) / len(vals, ), 2, )
    except ZeroDivisionError as zero_div_err:
        print("ZeroDivisionError:", zero_div_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def calculate_median_value(vals: list[int | float]) -> float | None:
    """
    Calculate the median of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        float: The median value rounded to 2 decimal places.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        mid_idx: int = len(vals, ) // 2

        if len(vals, ) % 2 == 1:
            return round(sorted(vals, )[mid_idx], 2, )

        return round(
            (sorted(vals, )[mid_idx - 1] + sorted(vals, )[mid_idx]) / 2,
            2,
        )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def calculate_variance_value(vals: list[int | float]) -> float | None:
    """
    Calculate the variance of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        float: The variance value rounded to 2 decimal places.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        mean_val: float = sum(vals, ) / len(vals, )
        squared_diff: list[float] = [(val - mean_val) ** 2 for val in vals]

        return round(sum(squared_diff, ) / len(vals, ), 2, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def calculate_std_value(vals: list[int | float]) -> float | None:
    """
    Calculate the standard deviation of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.

    :Returns:
        float: The standard deviation value rounded to 2 decimal places.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return 0.0

        return round(calculate_variance_value(vals=vals, ) ** 0.5, 2, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def calculate_metric(
    vals: list[int | float],
    metric: Literal[
        "min",
        "max",
        "mean",
        "median",
        "var",
        "std",
    ] = "mean"
) -> int | float | None:
    """
    Calculate the statistical metric for a list of numbers.

    :Parameters:
        vals (list[int | float]): List of numbers.
        metric (Literal["min", "max", "mean", "median", "var", "std", ]):
            The metric to calculate.
            Default: "mean".

    :Returns:
        float: The calculated metric.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        if not vals:
            return None

        match metric:
            case "min":
                return get_min_value(vals=vals, )

            case "max":
                return get_max_value(vals=vals, )

            case "mean":
                return calculate_mean_value(vals=vals, )

            case "median":
                return calculate_median_value(vals=vals, )

            case "var":
                return calculate_variance_value(vals=vals, )

            case "std":
                return calculate_std_value(vals=vals, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )

def extract_minutes_from_string(time: str | None) -> int | None:
    """
    Extract total minutes from a time string.

    :Parameters:
        time (str | None): Time string.

    :Returns:
        int: Exctracted minutes.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        ValueError: When used invalid data format.
        Exception: All other errors.
    """

    try:
        if time is None:
            return 0

        hours: int = 0

        if "hour" in time:
            hours = int(search(r'(\d+)\s*hour', time, ).group(1, ), )

        mins: int = int(search(r'(\d+)\s*minute', time, ).group(1, ), )

        return hours * 60 + mins
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except Exception as err:
        print("Exception:", err, )

def extract_price_from_string(price: str | None) -> int | None:
    """
    Extract price from a string.

    :Parameters:
        price (str | None): Price string.

    :Returns:
        int: Extracted price.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        ValueError: When used invalid data format.
        Exception: All other errors.
    """

    try:
        if price is not None:
            return int(price.replace(
                '$',
                '',
            ).replace(
                '£',
                '',
            ).replace(
                ',',
                '',
            ), )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except Exception as err:
        print("Exception:", err, )

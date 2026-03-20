"""
Additional utilities module.
"""


import sys

from typing import Any
from joblib import load


def get_conversion_multiplier_to_g(unit: str = 'g') -> float | None:
    """
    Returns the multiplicatior for converting units of weight measurement to
    grams.

    :Parameters:
        unit (str): String of the measurement unit.
                    Default: 'g'.

    :Returns:
        float: Multiplicatior for conversion to grams.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid data format.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        match unit.lower():
            case 'g':
                return 1.0
            case "mg":
                return 0.001
            case "mcg" | "ug":
                return 0.000001
            case "iu":
                return 0.0000003
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )

def get_clear_string(string: str) -> str | None:
    """
    Return a string of words.

    :Parameters:
        string (str): String.

    :Returns:
        str: Clear string.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        return string.strip('"', ).strip()
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )

def get_script_arguments() -> list[Any] | None:
    """
    Return script arguments.

    :Returns:
        list[str]: Script arguments.
        None: If error occurs or no data is loaded.

    :Exceptions:
        AttributeError: When data attribute not initialized.
        IndexError: When dictionary do not contain expected values.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        script_args: list[Any] = sys.argv

        return script_args[1: ]
    except AttributeError as attr_err:
        print("AttributeError:", attr_err, )
    except IndexError as idx_err:
        print("IndexError:", idx_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )

def unpack_model(model_file: str, model_file_path: str) -> Any | None:
    """
    Return unpacked model object.

    :Parameters:
        model_file (str): A model file.
        model_file_path (str): A path to a model file.

    :Returns:
        Any: Unpacked model.
        None: If error occurs or no data is loaded.

    :Exceptions:
        FileNotFoundError: When file was not found.
        TypeError: When used incorrect data types.
        Exception: All other errors.
    """

    try:
        model: Any = load(model_file_path + model_file, )

        return model
    except FileNotFoundError as file_not_found_err:
        print("FileNotFoundError:", file_not_found_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )

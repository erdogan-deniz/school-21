"""
Decorators Python module.
"""


import sys
import functools

from typing import Any, Callable


def handle_errors(func: Callable) -> Callable:
    """
    Decorator for handling exceptions in functions or methods.

    :Parameters:
        func (Callable): The function or method to be wrapped.

    :Returns:
        Callable: The wrapped function with exception handling.

    :Exceptions:
        Exception: Exception raised inside the wrapped function.
    """

    @functools.wraps(func)
    def wrapper(*args: Any, **kwargs: Any) -> Any | None:
        """
        Function that wraps the function.

        :Parameters:
            *args (Any): Positional arguments for the function.
            **kwargs (Any): Keyword arguments for the function.

        :Returns:
            Any: The return value of the function.

        :Exceptions:
            Exception: Exception raised in the function is caught.
        """

        try:
            return func(*args, **kwargs, )
        except Exception as err:
            print(
                f"\nError file: {func.__module__}" +
                f"\nError message: {err}",
            )

    return wrapper

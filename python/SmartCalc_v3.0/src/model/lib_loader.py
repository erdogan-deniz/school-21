"""Shared loader for the C SmartCalc shared library.

All model classes that need the library call load_lib() instead of
constructing their own ctypes.CDLL.  The OS loads the DLL exactly once;
subsequent calls return the cached instance.
"""

import ctypes
import os
import platform


_lib: ctypes.CDLL | None = None


def load_lib() -> ctypes.CDLL:
    """Return the loaded C shared library, loading it on first call.

    Returns:
        The cached CDLL instance.

    Raises:
        FileNotFoundError: If the compiled shared library is absent.

    """
    global _lib  # noqa: PLW0603
    if _lib is not None:
        return _lib

    lib_dir = os.path.join(os.path.dirname(__file__), "..", "libs")
    if os.name == "nt":
        lib_name = "libsmartcalc.dll"
    elif platform.system() == "Darwin":
        lib_name = "libsmartcalc.dylib"
    else:
        lib_name = "libsmartcalc.so"

    lib_path = os.path.abspath(os.path.join(lib_dir, lib_name))
    if not os.path.exists(lib_path):
        raise FileNotFoundError(
            f"Shared library not found: {lib_path}\n"
            'Run "make lib" to compile it.'
        )

    _lib = ctypes.CDLL(lib_path)
    return _lib

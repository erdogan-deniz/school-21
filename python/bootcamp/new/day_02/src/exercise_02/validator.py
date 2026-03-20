"""Save-directory validator."""

import os
from pathlib import Path


def get_valid_save_dir() -> str:
    """
    Prompt the user for a save directory until a valid writable path is given.

    :Returns:
        str: representation of the validated directory path as returned by
            :class:`pathlib.Path`.
    """

    while True:
        path: str = input("Enter directory to save images: ").strip()
        p: Path = Path(path)

        if p.exists() and p.is_dir() and os.access(p, os.W_OK):
            return str(p)

        if not p.exists():
            print(f"Path '{path}' does not exist.")
        elif not p.is_dir():
            print(f"'{path}' is not a directory.")
        else:
            print(f"No write access to '{path}'.")

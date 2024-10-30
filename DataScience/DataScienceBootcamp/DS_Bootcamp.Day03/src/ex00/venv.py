#!/usr/bin/env python3

import os


def print_current_venv() -> None:
    """"""

    venv_variable: str = "VIRTUAL_ENV"
    venv_path: str | None = os.getenv(venv_variable)

    print("Your current virtual env is", venv_path)


if __name__ == "__main__":
    print_current_venv()

import os


def print_current_venv() -> None:
    """"""

    venv_path: str | None = os.getenv("VIRTUAL_ENV")

    try:
        curr_venv: str = venv_path.split(":")[1]

        print("Your current virtual env is", curr_venv)
    except Exception as err:
        print(f"You don't hava a venv. {err}")


if __name__ == "__main__":
    print_current_venv()

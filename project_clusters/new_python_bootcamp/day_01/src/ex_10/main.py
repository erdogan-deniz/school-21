"""
Exercise 10: a machines - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from models.machines import Machines


def main() -> None:
    """
    Exercise 10 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        machines: Machines = Machines()

        machines.fill_machines_data()
        print(f"\n{machines.find_two_suitable_machines_cost()}", )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

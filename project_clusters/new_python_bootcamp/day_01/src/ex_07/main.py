"""
Exercise 07: a robot - solution module.
"""


import sys

from pathlib import Path

sys.path.append(str(Path(__file__, ).parent.parent, ),  )

from models.robot import Robot


def main() -> None:
    """
    Exercise 07 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        robot: Robot = Robot()

        robot.fill_robot_data()
        print(f"\n{robot.calculate_max_coins()}", )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()

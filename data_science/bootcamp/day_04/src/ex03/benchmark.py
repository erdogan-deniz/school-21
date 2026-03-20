#!/usr/bin/env python3

import sys
import timeit

from functools import reduce


def get_number_square(num: int) -> int:
    """"""

    return num * num


def get_squares_sum_cycle(num: int) -> int:
    """"""

    squares_sum: int = 0

    for curr_num in range(num):
        squares_sum += curr_num**2

    return squares_sum


def get_squares_sum_reduce(num: int) -> int:
    """"""

    squares_sum: int = reduce(
        lambda square_sum, curr_num: square_sum + get_number_square(curr_num),
        range(num),
    )

    return squares_sum


def print_func_worktime() -> None:
    """"""

    script_args: list = sys.argv

    if len(script_args) < 4:
        return None

    approach_arg: int | None = None
    approach_name: str | None = None
    approach_count: int | None = None

    try:
        approach_name = script_args[1]
        approach_count = int(script_args[2])
        approach_arg = int(script_args[3])

        if approach_name == "loop":
            cycle_approach_time: float = timeit.timeit(
                lambda: get_squares_sum_cycle(approach_arg),
                number=approach_count,
            )

            print(round(cycle_approach_time, 9))
        elif approach_name == "reduce":
            reduce_approach_time: float = timeit.timeit(
                lambda: get_squares_sum_reduce(approach_arg),
                number=approach_count,
            )

            print(round(reduce_approach_time, 9))
        else:
            raise Exception("ERROR! Incorrect argument.")
    except Exception as err:
        print(f"ERROR! {err}")


if __name__ == "__main__":
    print_func_worktime()

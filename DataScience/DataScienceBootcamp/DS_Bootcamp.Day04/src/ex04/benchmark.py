#!/usr/bin/env python3

import timeit
import random

from collections import Counter


def get_generated_numbers(
    iters_count: int, min_num_val: int, max_num_val
) -> list:
    """"""

    generated_nums: list = [
        random.randint(min_num_val, max_num_val) for _ in range(iters_count)
    ]

    return generated_nums


def add_number_to_number_count(nums_counts: dict, num: int) -> None:
    """"""

    if num in nums_counts:
        nums_counts[num] += 1
    else:
        nums_counts[num] = 1


def get_numbers_counts_cycle(nums: list) -> dict:
    """"""

    nums_counts: dict = {}

    for num in nums:
        add_number_to_number_count(nums_counts, num)

    return nums_counts


def get_numbers_counts_counter(nums: list) -> Counter:
    """"""

    nums_counts: Counter = Counter(nums)

    return nums_counts


def get_top_numbers_counts_cycle(nums: list, top_length: int) -> dict:
    """"""

    nums_counts: dict = {}

    for num in nums:
        add_number_to_number_count(nums_counts, num)

    top_nums_counts: dict = {
        key: val
        for key, val in sorted(
            nums_counts.items(), key=lambda pair: pair[1], reverse=True
        )[:top_length]
    }

    return top_nums_counts


def get_top_numbers_counts_counter(nums: list, top_length: int) -> Counter:
    """"""

    nums_counts: Counter = Counter(nums)

    top_nums_counts: Counter = nums_counts.most_common(top_length)

    return top_nums_counts


def print_funcs_stats() -> None:
    """"""

    top_length: int = 10
    nums: list = get_generated_numbers(1000000, 0, 100)

    cycle_approach_nums_counts_time: float = timeit.timeit(
        lambda: get_numbers_counts_cycle(nums), number=1
    )
    counter_approach_nums_counts_time: float = timeit.timeit(
        lambda: get_numbers_counts_counter(nums), number=1
    )
    cycle_approach_nums_counts_top_time: float = timeit.timeit(
        lambda: get_top_numbers_counts_cycle(nums, top_length), number=1
    )
    counter_approach_nums_counts_top_time: float = timeit.timeit(
        lambda: get_top_numbers_counts_counter(nums, top_length), number=1
    )

    print(f"My function: {round(cycle_approach_nums_counts_time, 7)}")
    print(f"Counter: {round(counter_approach_nums_counts_time, 7)}")
    print(f"My top: {round(cycle_approach_nums_counts_top_time, 7)}")
    print(f"Counter top: {round(counter_approach_nums_counts_top_time, 7)}")


if __name__ == "__main__":
    print_funcs_stats()

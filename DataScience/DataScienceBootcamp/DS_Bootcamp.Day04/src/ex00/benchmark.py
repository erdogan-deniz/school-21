#!/usr/bin/env python3

import timeit


def get_gmails_cycle(emails: list) -> list:
    """"""

    gmails: list = []

    for email in emails:
        if "@gmail.com" in email:
            gmails.append(email)

    return gmails


def get_gmails_list_compr(emails: list) -> list:
    """"""

    gmails: list = [email for email in emails if "@gmail.com" in email]

    return gmails


def print_fastest_func_worktime() -> None:
    """"""

    emails: list = [
        "anna@live.com",
        "anna@live.com",
        "anna@live.com",
        "anna@live.com",
        "anna@live.com",
        "john@gmail.com",
        "john@gmail.com",
        "john@gmail.com",
        "john@gmail.com",
        "john@gmail.com",
        "james@gmail.com",
        "james@gmail.com",
        "james@gmail.com",
        "james@gmail.com",
        "james@gmail.com",
        "alice@yahoo.com",
        "alice@yahoo.com",
        "alice@yahoo.com",
        "alice@yahoo.com",
        "alice@yahoo.com",
        "philipp@gmail.com",
        "philipp@gmail.com",
        "philipp@gmail.com",
        "philipp@gmail.com",
        "philipp@gmail.com",
    ]

    cycle_approach_time: float = timeit.timeit(
        lambda: get_gmails_cycle(emails), number=90000000
    )
    list_compr_approach_time: float = timeit.timeit(
        lambda: get_gmails_list_compr(emails), number=90000000
    )

    print(
        "It is better to use a list comprehension:"
        if list_compr_approach_time <= cycle_approach_time
        else "It is better to use a loop:"
    )
    print(
        min(cycle_approach_time, list_compr_approach_time),
        "vs",
        max(cycle_approach_time, list_compr_approach_time),
    )


if __name__ == "__main__":
    print_fastest_func_worktime()

#!/usr/bin/env python3

import timeit


def get_gmail(email: str) -> str | None:
    """"""

    return email if "@gmail.com" in email else None


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


def get_gmails_map(emails: list) -> list:
    """"""

    gmails: list = list(
        map(get_gmail, emails)
    )  # You can remove list() and map will be really fast

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
    map_approach_time: float = timeit.timeit(
        lambda: get_gmails_map(emails), number=90000000
    )

    max_approach_time: float = max(
        cycle_approach_time, list_compr_approach_time, map_approach_time
    )
    min_approach_time: float = min(
        cycle_approach_time, list_compr_approach_time, map_approach_time
    )
    sum_approaches_time: float = (
        cycle_approach_time + list_compr_approach_time + map_approach_time
    )

    if (map_approach_time <= list_compr_approach_time) and (
        map_approach_time <= cycle_approach_time
    ):
        print("It is better to use a map:")
    elif (list_compr_approach_time <= map_approach_time) and (
        list_compr_approach_time <= cycle_approach_time
    ):
        print("It is better to use a list comprehension:")
    else:
        print("It is better to use a loop:")

    print(
        min_approach_time,
        "vs",
        sum_approaches_time - min_approach_time - max_approach_time,
        "vs",
        max_approach_time,
    )


if __name__ == "__main__":
    print_fastest_func_worktime()

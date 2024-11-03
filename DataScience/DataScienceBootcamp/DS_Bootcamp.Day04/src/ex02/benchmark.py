#!/usr/bin/env python3

import sys
import timeit


def is_gmail(email: str) -> bool:
    """"""

    return "@gmail.com" in email


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


def get_gmails_filter(emails: list) -> list:
    """"""

    gmails: list = list(
        filter(is_gmail, emails)
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

    script_args: list = sys.argv

    if len(script_args) < 3:
        return None

    approach_name: str | None = None
    approach_count: int | None = None

    try:
        approach_name = script_args[1]
        approach_count = int(script_args[2])

        if approach_name == "loop":
            cycle_approach_time: float = timeit.timeit(
                lambda: get_gmails_cycle(emails), number=approach_count
            )

            print(round(cycle_approach_time, 9))
        elif approach_name == "list_comprehension":
            list_compr_approach_time: float = timeit.timeit(
                lambda: get_gmails_list_compr(emails), number=approach_count
            )

            print(round(list_compr_approach_time, 9))
        elif approach_name == "map":
            map_approach_time: float = timeit.timeit(
                lambda: get_gmails_map(emails), number=approach_count
            )

            print(round(map_approach_time, 9))
        elif approach_name == "filter":
            filter_approach_time: float = timeit.timeit(
                lambda: get_gmails_filter(emails), number=approach_count
            )

            print(round(filter_approach_time, 9))
        else:
            raise Exception("ERROR! Incorrect argument.")
    except Exception as err:
        print(f"ERROR! {err}")


if __name__ == "__main__":
    print_fastest_func_worktime()

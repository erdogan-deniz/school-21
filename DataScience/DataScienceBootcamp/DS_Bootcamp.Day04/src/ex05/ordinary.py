#!/usr/bin/env python3

import sys
import psutil


def get_file_content() -> list:
    """"""

    script_args: list = sys.argv
    file_content: list | None = None

    try:
        file: str = script_args[1]

        with open(file, "r") as work_file:
            file_content = work_file.readlines()
    except Exception as err:
        print(f"ERROR! {err}")

    return file_content


def main() -> None:
    """"""

    main_process: psutil.Process = psutil.Process()

    memory_usage_start: float = main_process.memory_info().rss
    time_usage_start: float = main_process.cpu_times()

    file_content: list = get_file_content()

    try:
        for _ in file_content:
            pass
    except Exception as err:
        print(f"ERROR! {err}")

    time_usage_end: float = main_process.cpu_times()
    memory_usage_end: float = main_process.memory_info().rss

    peak_usage_memory: float = (memory_usage_end - memory_usage_start) / (
        1024**3
    )
    usage_time: float = (time_usage_end.user + time_usage_end.system) - (
        time_usage_start.user + time_usage_start.system
    )

    print("Peak memory usage =", round(peak_usage_memory, 3), "GB")
    print("User mode time + System mode time =", round(usage_time, 2), "s")


if __name__ == "__main__":
    main()

import sys


def print_greeting() -> None:
    """"""

    script_args = sys.argv

    if len(script_args) == 2:
        file_content: list = None

        with open("employees.tsv", "r+") as work_file:
            file_content = work_file.readlines()

        required_entry: str = None

        for file_row in file_content:
            if script_args[1].capitalize() in file_row:
                required_entry = file_row

        if required_entry is not None:
            print(
                f"Dear {required_entry.split('\t')[0]},"
                + "welcome to our team. We are sure that it will"
                + "be a pleasure to work with you. That’s a precondition"
                + "for the professionals that our company hires"
            )


if __name__ == "__main__":
    print_greeting()

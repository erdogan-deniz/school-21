import sys


def create_employees_table_from_emails() -> None:
    """"""

    script_args = sys.argv

    if len(script_args) == 2:
        file_content: list = None

        with open(script_args[1], "r+") as work_file:
            file_content = work_file.readlines()

        file_content.insert(0, "Name\tSurname\tE-mail\n")

        for file_row_idx in range(1, len(file_content)):
            employee_name: str = (
                file_content[file_row_idx].split(".")[0].capitalize()
            )
            employee_surname: str = (
                file_content[file_row_idx]
                .split(".")[1]
                .split("@")[0]
                .capitalize()
            )
            file_content[file_row_idx] = (
                employee_name
                + "\t"
                + employee_surname
                + "\t"
                + f"{file_content[file_row_idx]}"
            )

        with open("employees.tsv", "w+") as work_file:
            work_file.writelines(file_content)


if __name__ == "__main__":
    create_employees_table_from_emails()

import sys


def is_latin_letter(symbol: str) -> bool:
    """"""

    symbol_is_latin_letter: bool = (
        symbol in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    )

    return symbol_is_latin_letter


class Research:
    """"""

    def __init__(self) -> None:
        """"""

        self.file_path: str = sys.argv[1]

    def file_reader(self) -> list:
        """"""

        file_content: list | None = None

        with open(self.file_path, "r") as work_file:
            file_content: list = work_file.readlines()

        for symbol in file_content[0][:-1]:
            if (symbol != ",") and (not is_latin_letter(symbol)):
                raise Exception("ERROR! Incorrect file content header.")

        if (len(file_content[0].split(",")) != 2) or (
            file_content[0].count(",") > 1
        ):
            raise Exception("ERROR! Incorrect file content header.")

        for file_row in file_content[1:]:
            if (file_row != "1,0\n") and (file_row != "0,1\n"):
                raise Exception("ERROR! Incorrect file content.")

        return file_content


if __name__ == "__main__":
    researcher: Research = Research()

    file_content: list = researcher.file_reader()

    print(*file_content, sep="")

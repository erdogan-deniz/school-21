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

    def file_reader(self, has_header: bool = True) -> list:
        """"""

        file_content: list | None = None

        with open(self.file_path, "r") as work_file:
            file_content: list = work_file.readlines()

        if has_header:
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

        file_content = [pair.rstrip().split(",") for pair in file_content[1:]]
        file_content = [
            [int(num) for num in sublist] for sublist in file_content
        ]

        return file_content

    class Calculations:
        """"""

        @staticmethod
        def counts(pairs: list) -> tuple:
            """"""

            head_count: int = 0
            tail_count: int = 0

            for pair in pairs:
                if pair[0] == 0:
                    tail_count += 1
                else:
                    head_count += 1

            return (head_count, tail_count)

        @staticmethod
        def fractions(head_count: int, tail_count: int) -> tuple:
            """"""

            num_of_elements: int = head_count + tail_count

            return (head_count / num_of_elements, tail_count / num_of_elements)


if __name__ == "__main__":
    researcher: Research = Research()
    digit_pairs: list = researcher.file_reader()

    element_counters: tuple = researcher.Calculations.counts(digit_pairs)
    element_fractions: tuple = researcher.Calculations.fractions(
        *element_counters
    )

    print(digit_pairs)
    print(*element_counters)
    print(*element_fractions)

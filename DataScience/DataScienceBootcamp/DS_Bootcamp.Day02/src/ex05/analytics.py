import sys

from random import randint
from config import REPORT_TEMPL


def get_count_of_heads(digit_pairs: list) -> int:
    """"""

    count_of_heads: int = 0

    for pair in digit_pairs:
        if pair[0] == 1:
            count_of_heads += 1

    return count_of_heads


def prepare_report_content(
    num_of_pairs: int,
    num_of_gen_pairs: int,
    num_of_gen_heads: int,
    element_counters: tuple,
    element_fractions: tuple,
) -> str:
    """"""

    report_content: str = REPORT_TEMPL

    report_content = (
        report_content.replace("@OBS@", str(num_of_pairs))
        .replace("@GEN_OBS@", str(num_of_gen_pairs))
        .replace("@TAILS@", str(element_counters[1]))
        .replace("@HEADS@", str(element_counters[0]))
        .replace("@GEN_HEADS@", str(num_of_gen_heads))
        .replace("@GEN_TAILS@", str(num_of_gen_pairs - num_of_gen_heads))
        .replace("@HEADS_PERC@", str(round(element_fractions[1] * 100, 2)))
        .replace("@TAILS_PERC@", str(round(element_fractions[0] * 100, 2)))
    )

    return report_content


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

        def __init__(self, pairs: list) -> None:
            """"""

            self.pairs: list = pairs

        def counts(self) -> tuple:
            """"""

            head_count: int = 0
            tail_count: int = 0

            for pair in self.pairs:
                if pair[0] == 0:
                    tail_count += 1
                else:
                    head_count += 1

            return (head_count, tail_count)

        def fractions(self, head_count: int, tail_count: int) -> tuple:
            """"""

            num_of_elements: int = head_count + tail_count

            return (head_count / num_of_elements, tail_count / num_of_elements)


class Analytics(Research.Calculations):
    """"""

    def predict_random(self, num_of_gen_pairs: int) -> list:
        """"""

        generated_pairs: list = []

        for _ in range(num_of_gen_pairs):
            random_num: int = randint(0, 1)

            generated_pairs.append([random_num, 1 - random_num])

        return generated_pairs

    def predict_last(self) -> list:
        """"""

        return self.pairs[-1]

    def save_data_to_file(
        self, data: object, file_path: str, file_name: str, file_format: str
    ) -> None:
        """"""

        with open(file_path + file_name + file_format, "w+") as work_file:
            work_file.writelines(data)

from config import FILE_PATH, FILE_NAME, FILE_FORMAT, NUM_OF_GEN_PAIRS
from analytics import (
    Research,
    Analytics,
    get_count_of_heads,
    prepare_report_content,
)


if __name__ == "__main__":
    researcher: Research = Research()
    digit_pairs: list = researcher.file_reader()

    analytic: Analytics = Analytics(digit_pairs)
    element_counters: tuple = analytic.counts()
    element_fractions: tuple = analytic.fractions(*element_counters)
    generated_pairs: list = analytic.predict_random(NUM_OF_GEN_PAIRS)
    last_pair: list = analytic.predict_last()
    count_of_generated_heads: int = get_count_of_heads(generated_pairs)

    report_content: str = prepare_report_content(
        len(digit_pairs),
        len(generated_pairs),
        count_of_generated_heads,
        element_counters,
        element_fractions,
    )

    analytic.save_data_to_file(
        report_content, FILE_PATH, FILE_NAME, FILE_FORMAT
    )

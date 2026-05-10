"""Console rendering utilities for the live and final exam displays."""

import sys
from typing import Any

from models import Examiner, Student


def make_table(headers: list[str], rows: list[tuple[Any, ...]]) -> str:
    """
    Render an ASCII table with centred columns.

    :Parameters:
        headers (list[str]): Column header strings.
        rows (list[tuple[Any, ...]]): Sequence of row tuples; each element is
            converted with ``str()``.

    :Returns:
        str: A multi-line string containing the formatted table, including
            top, header-separator and bottom border lines.
    """

    widths: list[int] = [len(h) for h in headers]

    for row in rows:
        for i, cell in enumerate(row):
            widths[i] = max(widths[i], len(str(cell)))

    sep: str = "+" + "+".join("-" * (w + 2) for w in widths) + "+"

    def fmt(cells: tuple[Any, ...] | list[str]) -> str:
        """Format a row of cells with centred text and vertical separators."""

        return "| " + " | ".join(str(c).center(w) for c, w in zip(cells, widths)) + " |"

    lines: list[str] = [sep, fmt(headers), sep]

    for row in rows:
        lines.append(fmt(row))

    lines.append(sep)

    return "\n".join(lines)


def render_live(
    students: list[Student],
    examiners: list[Examiner],
    total_students: int,
    elapsed: float,
) -> str:
    """
    Build the live exam status string (tables + summary lines).

    :Parameters:
        students (list[Student]): Current Student instances.
        examiners (list[Examiner]): Current Examiner instances.
        total_students (int): Total number of students at exam start.
        elapsed (float): Seconds since the exam began.

    :Returns:
        str: A multi-line string ready to be written to stdout.
    """

    in_queue: list[tuple[str, int]] = sorted(
        [(s.name, s.queue_pos) for s in students if s.status == "In queue"],
        key=lambda x: x[1],
    )
    passed: list[str] = [s.name for s in students if s.status == "Passed"]
    failed: list[str] = [s.name for s in students if s.status == "Failed"]
    s_rows: list[tuple[Any, ...]] = (
        [(n, "In queue") for n, _ in in_queue]
        + [(n, "Passed") for n in passed]
        + [(n, "Failed") for n in failed]
    )
    s_table: str = make_table(["Student", "Status"], s_rows)
    e_rows: list[tuple[Any, ...]] = [
        (
            e.name,
            e.current or "-",
            e.total,
            e.failed,
            f"{e.work_time:.2f}",
        )
        for e in examiners
    ]
    e_headers: list[str] = ["Examiner", "Current Student", "Total Students", "Failed", "Work Time"]
    e_table: str = make_table(e_headers, e_rows)
    in_q_count: int = len(in_queue)

    return "\n".join(
        [
            s_table,
            "",
            e_table,
            "",
            f"Remaining in queue: {in_q_count} out of {total_students}",
            f"Time since exam started: {elapsed:.2f}",
        ]
    )


def render_final(
    students: list[Student],
    examiners: list[Examiner],
    total_time: float,
    q_stats: dict[str, dict[str, int]],
) -> str:
    """
    Build the final exam summary string shown after all examiners finish.

    :Parameters:
        students (list[Student]): Final Student instances.
        examiners (list[Examiner]): Final Examiner instances.
        total_time (float): Total wall-clock seconds from exam start to finish.
        q_stats (dict[str, dict[str, int]]): Mapping from question text to
            ``{'correct': int, 'total': int}``.

    :Returns:
        str: A multi-line string with tables and summary lines ready to print.
    """

    passed: list[tuple[str, float | None]] = [
        (s.name, s.finish_time) for s in students if s.status == "Passed"
    ]
    failed: list[tuple[str, float | None]] = [
        (s.name, s.finish_time) for s in students if s.status == "Failed"
    ]
    s_rows: list[tuple[Any, ...]] = [(n, "Passed") for n, _ in passed] + [
        (n, "Failed") for n, _ in failed
    ]
    s_table: str = make_table(["Student", "Status"], s_rows)
    e_rows: list[tuple[Any, ...]] = [
        (e.name, e.total, e.failed, f"{e.work_time:.2f}") for e in examiners
    ]
    e_table: str = make_table(["Examiner", "Total Students", "Failed", "Work Time"], e_rows)
    top_students: list[str] = []

    if passed:
        min_t: float = min(t for _, t in passed if t is not None)
        top_students = [n for n, t in passed if t == min_t]

    top_examiners: list[str] = []
    rates: list[tuple[str, float]] = [
        (e.name, e.failed / e.total) for e in examiners if e.total > 0
    ]

    if rates:
        min_rate: float = min(r for _, r in rates)
        top_examiners = [n for n, r in rates if r == min_rate]

    expelled: list[str] = []

    if failed:
        min_fail_t: float = min(t for _, t in failed if t is not None)
        expelled = [n for n, t in failed if t == min_fail_t]

    best_qs: list[str] = []

    if q_stats:
        max_correct: int = max(v["correct"] for v in q_stats.values())
        best_qs = [q for q, v in q_stats.items() if v["correct"] == max_correct]

    total: int = len(students)
    pass_count: int = len(passed)
    result: str = "Exam passed" if total > 0 and pass_count / total > 0.85 else "Exam failed"
    totals_line: str = ""

    if examiners:
        totals: Examiner = sum(examiners[1:], examiners[0])
        totals_line = (
            f"Total across all examiners: "
            f"{totals.total} students, "
            f"{totals.failed} failed, "
            f"{totals.work_time:.2f}s work time"
        )

    return "\n".join(
        [
            s_table,
            "",
            e_table,
            "",
            f"Time from exam start to finish: {total_time:.2f}",
            *([totals_line] if totals_line else []),
            f'Top-performing students: {", ".join(top_students)}',
            f'Top examiners: {", ".join(top_examiners)}',
            f'Students to be expelled: {", ".join(expelled)}',
            f'Best questions: {", ".join(best_qs)}',
            f"Result: {result}",
        ]
    )


def clear_lines(n: int) -> None:
    """
    Move the cursor up *n* lines and erase everything below it.

    :Parameters:
        n (int): Number of lines to erase.  Does nothing when *n* is zero.
    """

    if n > 0:
        sys.stdout.write(f"\033[{n}A\033[J")

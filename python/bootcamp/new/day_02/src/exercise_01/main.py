"""Entry point for the exam simulation."""

import multiprocessing
import os
import queue
import sys
import time
from typing import Any

from display import clear_lines, render_final, render_live
from exam import examiner_worker
from models import Examiner, Question, Student
from state import apply_update

_RENDER_INTERVAL: float = 0.1  # seconds between live display refreshes


def main() -> None:
    """Load input files, run the exam simulation, and print the final report."""

    base: str = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "data")

    with open(os.path.join(base, "examiners.txt"), encoding="utf-8") as fh:
        examiner_lines: list[str] = [line.strip() for line in fh if line.strip()]

    with open(os.path.join(base, "students.txt"), encoding="utf-8") as fh:
        student_lines: list[str] = [line.strip() for line in fh if line.strip()]

    with open(os.path.join(base, "questions.txt"), encoding="utf-8") as fh:
        questions: list[Question] = [Question(line.strip()) for line in fh if line.strip()]

    examiners_data: list[tuple[str, str]] = [
        (parts[0], parts[1]) for parts in (line.split() for line in examiner_lines)
    ]
    students_data: list[tuple[str, str]] = [
        (parts[0], parts[1]) for parts in (line.split() for line in student_lines)
    ]

    if sys.platform == "win32":
        os.system("")  # Enable ANSI escape codes on Windows

    students: list[Student] = [
        Student(name=name, gender=gender, queue_pos=i)
        for i, (name, gender) in enumerate(students_data)
    ]
    examiners: list[Examiner] = [
        Examiner(name=name, gender=gender) for name, gender in examiners_data
    ]
    q_stats: dict[str, dict[str, int]] = {}
    total_students: int = len(students)
    student_q: multiprocessing.Queue[tuple[str, str]] = multiprocessing.Queue()
    update_q: multiprocessing.Queue[tuple[Any, ...]] = multiprocessing.Queue()

    for student in students_data:
        student_q.put(student)

    exam_start: float = time.time()
    processes: list[multiprocessing.Process] = []

    for name, gender in examiners_data:
        proc: multiprocessing.Process = multiprocessing.Process(
            target=examiner_worker,
            args=(name, gender, student_q, update_q, questions, exam_start),
        )
        proc.start()
        processes.append(proc)

    active: int = len(examiners_data)
    prev_lines: int = 0
    last_render: float = 0.0

    while active > 0:
        try:
            msg: tuple[Any, ...] = update_q.get(timeout=0.05)

            if apply_update(msg, students, examiners, q_stats):
                active -= 1
        except queue.Empty:
            pass

        now: float = time.time()

        if now - last_render >= _RENDER_INTERVAL:
            last_render = now
            output: str = render_live(students, examiners, total_students, now - exam_start)

            clear_lines(prev_lines)
            sys.stdout.write(output + "\n")
            sys.stdout.flush()

            prev_lines = output.count("\n") + 1

    while True:
        try:
            msg = update_q.get_nowait()

            apply_update(msg, students, examiners, q_stats)
        except queue.Empty:
            break

    for proc in processes:
        proc.join()

    total_time: float = time.time() - exam_start

    clear_lines(prev_lines)
    print(render_final(students, examiners, total_time, q_stats))


if __name__ == "__main__":
    main()

"""Exam simulation logic for individual sessions and examiner worker processes."""

import multiprocessing
import queue
import random
import time

from models import Question
from probability import examiner_answers, pick_word

# Duration of a single exam is [name_length - 1, name_length + 1] seconds.
_BREAK_AFTER_SECONDS: int = 30
_BREAK_MIN: int = 12
_BREAK_MAX: int = 18
_QUESTIONS_PER_EXAM: int = 3


def run_exam(
    s_name: str,
    s_gender: str,
    e_name: str,
    e_gender: str,
    questions: list[Question],
    duration: float,
) -> tuple[bool, dict[str, bool]]:
    """
    Simulate a single exam session between one student and one examiner.

    :Parameters:
        s_name (str): Student's name (unused in logic, present for symmetry).
        s_gender (str): Student gender (``'M'`` or ``'F'``), controls word bias.
        e_name (str): Examiner's name (unused in logic, present for symmetry).
        e_gender (str): Examiner gender (``'M'`` or ``'F'``), controls word bias.
        questions (list[Question]): Pool of questions to sample from.
        duration (float): Seconds to sleep, modelling real exam length.

    :Returns:
        (tuple[bool, dict[str, bool]]): A tuple ``(passed, q_results)`` where
            *passed* is ``True`` if thestudent passed, and *q_results* maps each
            asked question to whether the student answered it correctly.
    """

    k: int = min(_QUESTIONS_PER_EXAM, len(questions))
    selected: list[Question] = random.sample(questions, k)
    correct: int = 0
    incorrect: int = 0
    q_results: dict[str, bool] = {}

    for q in selected:
        answer: str = pick_word(q.text, s_gender)
        correct_set: set[str] = examiner_answers(q.text, e_gender)
        ok: bool = answer in correct_set
        q_results[q.text] = ok

        if ok:
            correct += 1
        else:
            incorrect += 1

    mood: float = random.random()
    passed: bool

    if mood < 1 / 8:
        passed = False
    elif mood < 1 / 8 + 1 / 4:
        passed = True
    else:
        passed = correct > incorrect

    time.sleep(duration)

    return passed, q_results


def examiner_worker(
    name: str,
    gender: str,
    student_q: multiprocessing.Queue,
    update_q: multiprocessing.Queue,
    questions: list[Question],
    exam_start: float,
) -> None:
    """
    Examiner process entry point: pull students, run exams, report results.

    :Parameters:
        name (str): Examiner's name; its length determines exam duration range.
        gender (str): Examiner gender (``'M'`` or ``'F'``).
        student_q (multiprocessing.Queue): Shared queue of
            ``(student_name, student_gender)`` tuples.
        update_q (multiprocessing.Queue): Queue used to send state-change
            messages to the main process.
        questions (list[Question]): Full question bank shared across all examiners.
        exam_start (float): ``time.time()`` value when the overall exam began,
            used to determine when the lunch break becomes available.
    """

    name_len: int = len(name)
    work_start: float = time.time()
    took_break: bool = False

    while True:
        try:
            student_name: str
            student_gender: str
            student_name, student_gender = student_q.get(timeout=1.0)
        except queue.Empty:
            break

        update_q.put(('start', name, student_name))

        duration: float = random.uniform(name_len - 1, name_len + 1)
        passed: bool
        q_results: dict[str, bool]
        passed, q_results = run_exam(
            student_name, student_gender, name, gender, questions, duration
        )
        finish_time: float = time.time() - exam_start
        work_time: float = time.time() - work_start

        update_q.put((
            'done', name, student_name,
            passed, finish_time, q_results, work_time,
        ))

        if not took_break and time.time() - exam_start >= _BREAK_AFTER_SECONDS:
            took_break = True

            update_q.put(('break', name))
            time.sleep(random.uniform(_BREAK_MIN, _BREAK_MAX))
            update_q.put(('back', name, time.time() - work_start))

    update_q.put(('finished', name, time.time() - work_start))

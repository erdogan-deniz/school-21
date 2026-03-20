"""Shared state mutation for the exam simulation."""

from typing import Any

from models import Examiner, Student


def apply_update(
    msg: tuple[Any, ...],
    students: list[Student],
    examiners: list[Examiner],
    q_stats: dict[str, dict[str, int]],
) -> bool:
    """
    Apply a single worker message to the shared exam state.

    :Parameters:
        msg (tuple[Any, ...]): Tuple whose first element is the message type string and whose
            remaining elements carry type-specific payload.
        students (list[Student]): List of Student instances.
        examiners (list[Examiner]): List of Examiner instances.
        q_stats (dict[str, dict[str, int]]): Mapping from question text to
            ``{'correct': int, 'total': int}`` tracking correct answers.

    :Returns:
        bool: ``True`` if the message type is ``'finished'`` (signals the main
            loop that one fewer examiner is active), ``False`` otherwise.
    """

    mtype: str = msg[0]

    if mtype == 'start':
        ex_name: str = msg[1]
        st_name: str = msg[2]

        for e in examiners:
            if e.name == ex_name:
                e.current = st_name

                break

    elif mtype == 'done':
        ex_name = msg[1]
        st_name = msg[2]
        passed: bool = msg[3]
        finish_time: float = msg[4]
        q_results: dict[str, bool] = msg[5]
        work_time: float = msg[6]

        for e in examiners:
            if e.name == ex_name:
                e.current = None
                e.total += 1

                if not passed:
                    e.failed += 1

                e.work_time = work_time

                break

        for s in students:
            if s.name == st_name:
                s.status = 'Passed' if passed else 'Failed'
                s.finish_time = finish_time

                break

        for q, ok in q_results.items():
            if q not in q_stats:
                q_stats[q] = {'correct': 0, 'total': 0}

            q_stats[q]['total'] += 1

            if ok:
                q_stats[q]['correct'] += 1

    elif mtype == 'break':
        ex_name = msg[1]

        for e in examiners:
            if e.name == ex_name:
                e.current = None

                break

    elif mtype == 'back':
        ex_name = msg[1]
        work_time = msg[2]

        for e in examiners:
            if e.name == ex_name:
                e.work_time = work_time

                break

    elif mtype == 'finished':
        ex_name = msg[1]
        work_time = msg[2]

        for e in examiners:
            if e.name == ex_name:
                e.work_time = work_time
                e.current = None

                break

        return True

    return False

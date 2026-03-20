"""Domain model classes for the exam simulation."""


class Student:
    """
    A student queued to sit an exam session.

    :Attributes:
        name (str): Student's full name.
        gender (str): ``'M'`` or ``'F'`` — controls word-selection bias
            inside probability functions.
        status (str): Current state: ``'In queue'``, ``'Passed'``, or
            ``'Failed'``.
        finish_time (float | None): Seconds elapsed from exam start to the
            moment this student's result was recorded; ``None`` while still
            in queue or being examined.
        queue_pos (int): Zero-based position in the original arrival order,
            used to keep the live display sorted consistently.
    """

    def __init__(self, name: str, gender: str, queue_pos: int) -> None:
        """
        Initialise a new Student in the ``'In queue'`` state.

        :Parameters:
            name (str): Student's full name.
            gender (str): ``'M'`` or ``'F'``.
            queue_pos (int): Position in the original arrival queue (0-based).
        """

        self.name: str = name
        self.gender: str = gender
        self.status: str = 'In queue'
        self.finish_time: float | None = None
        self.queue_pos: int = queue_pos

    def __repr__(self) -> str:
        """Return an unambiguous representation for debugging."""

        return f'Student(name={self.name!r}, status={self.status!r})'


class Examiner:
    """
    An examiner who pulls students from the queue and runs exam sessions.

    :Attributes:
        name (str): Examiner's full name.  Its character length determines the
            exam duration range: ``[len(name) - 1, len(name) + 1]`` seconds.
        gender (str): ``'M'`` or ``'F'`` — controls which words the examiner
            considers correct answers.
        current (str | None): Name of the student currently being examined,
            or ``None`` when idle.
        total (int): Number of students examined so far.
        failed (int): Number of those students who did not pass.
        work_time (float): Cumulative active seconds (updated after each
            session and break).
    """

    def __init__(self, name: str, gender: str) -> None:
        """
        Initialise an idle Examiner with zeroed statistics.

        :Parameters:
            name (str): Examiner's full name.
            gender (str): ``'M'`` or ``'F'``.
        """

        self.name: str = name
        self.gender: str = gender
        self.current: str | None = None
        self.total: int = 0
        self.failed: int = 0
        self.work_time: float = 0.0

    def __add__(self, other: 'Examiner') -> 'Examiner':
        """
        Aggregate two Examiner instances into one combined totals object.

        :Parameters:
            other (Examiner): The examiner whose statistics are added to this
                one's.

        :Returns:
            Examiner: A new Examiner whose ``total``, ``failed``, and
                ``work_time`` are the element-wise sums of both operands.
        """

        result = Examiner(name=f'{self.name}+{other.name}', gender=self.gender)
        result.total = self.total + other.total
        result.failed = self.failed + other.failed
        result.work_time = self.work_time + other.work_time

        return result

    def __repr__(self) -> str:
        """Return an unambiguous representation for debugging."""

        return f'Examiner(name={self.name!r}, total={self.total})'


class Question:
    """
    An exam question loaded from the question bank file.

    :Attributes:
        text (str): The full question text as a single string, e.g.
            ``'Solar eclipses affect people'``.
    """

    def __init__(self, text: str) -> None:
        """
        Wrap a raw question string.

        :Parameters:
            text (str): The full question text (a single line from
                ``questions.txt``, stripped of whitespace).
        """

        self.text: str = text

    def __str__(self) -> str:
        """Return the question text directly."""

        return self.text

    def __repr__(self) -> str:
        """Return an unambiguous representation for debugging."""

        return f'Question({self.text!r})'

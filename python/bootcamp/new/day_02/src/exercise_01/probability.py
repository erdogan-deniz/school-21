"""Golden-ratio probability utilities for word selection during exam."""

import random

PHI: float = (1 + 5**0.5) / 2  # Golden ratio ≈ 1.618


def golden_probs(n: int, reverse: bool = False) -> list[float]:
    """
    Build a list of *n* probabilities following the golden ratio rule.

    :Parameters:
        n (int): Number of probability slots (one per word in a question).
        reverse (bool): When *True* the list is reversed, so the highest
            probabilities fall at the *end* instead of the start.

    :Returns:
        list[float]: A list of *n* non-negative floats that sum to 1.0.
    """

    probs: list[float] = []
    remaining: float = 1.0

    for _ in range(n - 1):
        p: float = remaining / PHI

        probs.append(p)

        remaining -= p

    probs.append(remaining)

    if reverse:
        probs.reverse()

    return probs


def pick_word(question: str, gender: str) -> str:
    """
    Choose one word from *question* using gender-biased golden ratio.

    :Parameters:
        question (str): The exam question whose words are candidates.
        gender (str): ``'M'`` for male (start-biased) or ``'F'`` for female
            (end-biased).

    :Returns:
        str: A single word selected from *question*.
    """

    words: list[str] = question.split()
    probs: list[float] = golden_probs(len(words), reverse=(gender == "F"))

    return random.choices(words, weights=probs, k=1)[0]


def examiner_answers(question: str, gender: str) -> set[str]:
    """
    Determine the set of words the examiner considers correct answers.

    :Parameters:
        question (str): The exam question being evaluated.
        gender (str): Examiner gender (``'M'`` or ``'F'``) determining the
            directional bias of the initial selection.

    :Returns:
        set[str]: A non-empty set of words that the examiner marks as correct.
    """

    words: list[str] = question.split()
    n: int = len(words)
    probs: list[float] = golden_probs(n, reverse=(gender == "F"))
    chosen: set[int] = set()
    idx: int = random.choices(range(n), weights=probs, k=1)[0]

    chosen.add(idx)

    while len(chosen) < n and random.random() < 1 / 3:
        remaining_indices: list[int] = [i for i in range(n) if i not in chosen]

        if not remaining_indices:
            break

        rem_probs: list[float] = [probs[i] for i in remaining_indices]
        total: float = sum(rem_probs)
        rem_probs = [p / total for p in rem_probs]
        idx = random.choices(remaining_indices, weights=rem_probs, k=1)[0]

        chosen.add(idx)

    return {words[i] for i in chosen}

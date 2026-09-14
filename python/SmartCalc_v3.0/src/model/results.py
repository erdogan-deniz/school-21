"""Typed result structures for calculator model methods."""

from typing import TypedDict


class AnnuityResult(TypedDict):
    """Result of LoanCalculator.calculate_annuity()."""

    monthly_payment: float  # Fixed monthly instalment (principal + interest).
    overpayment: float  # Total interest paid over the loan term.
    total: float  # Sum of all monthly payments.


class DifferentiatedResult(TypedDict):
    """Result of LoanCalculator.calculate_differentiated()."""

    first_payment: float  # Largest instalment (first month).
    last_payment: float  # Smallest instalment (last month).
    overpayment: float  # Total interest paid over the loan term.
    total: float  # Sum of all monthly payments.
    payments: list[float]  # Per-month payment amounts, oldest first.


class DepositResult(TypedDict):
    """Result of DepositCalculator.calculate()."""

    total_interest: float  # Gross interest accrued over the full term.
    tax_amount: float  # Tax withheld on the interest income.
    final_amount: float  # Closing balance (principal + net interest).


class HistoryEntry(TypedDict):
    """One row returned by History.get_history()."""

    expression: str  # The original expression string entered by the user.
    result: str  # Evaluated result as a formatted string.
    timestamp: str  # ISO-8601 datetime string of when the entry was saved.


class DepositEntry(TypedDict):
    """One scheduled addition or withdrawal entry."""

    month: int  # 1-based month index within the deposit term.
    amount: float  # Positive; caller decides if addition or withdrawal.

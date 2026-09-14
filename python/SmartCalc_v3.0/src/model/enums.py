"""Shared domain enumerations for SmartCalc."""

from enum import StrEnum


class PaymentType(StrEnum):
    """Loan repayment schedule type."""

    ANNUITY = "annuity"
    DIFFERENTIATED = "differentiated"


class AccrualPeriod(StrEnum):
    """Frequency at which deposit interest is accrued."""

    MONTHLY = "monthly"
    QUARTERLY = "quarterly"
    ANNUALLY = "annually"

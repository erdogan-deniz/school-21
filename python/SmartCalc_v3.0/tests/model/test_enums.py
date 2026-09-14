"""Unit tests for model.enums: PaymentType and AccrualPeriod enums."""

from model.enums import AccrualPeriod, PaymentType


def test_payment_type_str_values() -> None:
    """Verifies the string values of both PaymentType members."""
    assert (
        PaymentType.ANNUITY  # type: ignore[comparison-overlap]
        == "annuity"
    )
    assert (
        PaymentType.DIFFERENTIATED  # type: ignore[comparison-overlap]
        == "differentiated"
    )


def test_accrual_period_str_values() -> None:
    """Verifies the string values of all three AccrualPeriod members."""
    assert (
        AccrualPeriod.MONTHLY  # type: ignore[comparison-overlap]
        == "monthly"
    )
    assert (
        AccrualPeriod.QUARTERLY  # type: ignore[comparison-overlap]
        == "quarterly"
    )
    assert (
        AccrualPeriod.ANNUALLY  # type: ignore[comparison-overlap]
        == "annually"
    )


def test_payment_type_from_string() -> None:
    """Confirms PaymentType can be constructed from its string value."""
    assert PaymentType("annuity") is PaymentType.ANNUITY


def test_accrual_period_from_string() -> None:
    """Confirms AccrualPeriod can be constructed from its string value."""
    assert AccrualPeriod("monthly") is AccrualPeriod.MONTHLY


def test_payment_type_in_string_dict() -> None:
    """Verify a PaymentType member acts as a plain string key in dicts."""
    mapping = {"annuity": 1, "differentiated": 2}
    assert mapping[PaymentType.ANNUITY] == 1


def test_accrual_period_in_string_dict() -> None:
    """Verify an AccrualPeriod member acts as a plain string key in dicts."""
    mapping = {"monthly": 12, "quarterly": 4, "annually": 1}
    assert mapping[AccrualPeriod.MONTHLY] == 12

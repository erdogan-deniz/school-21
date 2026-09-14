"""Property-based and parametrized invariant tests for DepositCalculator.

Uses pytest.mark.parametrize for a fixed set of realistic deposit inputs and
Hypothesis for arbitrary-value consistency checks.
"""

import math

import pytest
from hypothesis import HealthCheck, given, settings
from hypothesis import strategies as st

from model.deposit import DepositCalculator


DEPOSIT_CASES = [
    (100_000, 6, 8.0, 0.0, "monthly", False),
    (100_000, 12, 12.0, 0.0, "monthly", False),
    (100_000, 12, 12.0, 0.0, "monthly", True),
    (50_000, 12, 6.0, 13.0, "quarterly", False),
    (200_000, 24, 10.0, 0.0, "annually", False),
    (100_000, 12, 0.0, 0.0, "monthly", False),   # zero rate
    (100_000, 13, 12.0, 0.0, "annually", False),  # tail period
]


# ---------------------------------------------------------------------------
# 1. Parametrized invariant tests
# ---------------------------------------------------------------------------


class TestDepositInvariants:
    """Properties that must hold for all deposit inputs."""

    @pytest.mark.parametrize("amount,months,rate,tax,period,cap", DEPOSIT_CASES)
    def test_tax_equals_rate_times_interest(
        self,
        dep: DepositCalculator,
        amount: float,
        months: int,
        rate: float,
        tax: float,
        period: str,
        cap: bool,
    ) -> None:
        """Verify tax_amount = total_interest * tax_rate / 100 for all args."""
        r = dep.calculate(amount, months, rate, tax, period, cap)
        assert math.isclose(
            r["tax_amount"],
            r["total_interest"] * tax / 100,
            rel_tol=1e-9,
            abs_tol=1e-9,
        )

    @pytest.mark.parametrize("amount,months,rate,tax,period,cap", DEPOSIT_CASES)
    def test_final_amount_nonneg(
        self,
        dep: DepositCalculator,
        amount: float,
        months: int,
        rate: float,
        tax: float,
        period: str,
        cap: bool,
    ) -> None:
        """Verifies final_amount ≥ 0 for all parametrized inputs."""
        r = dep.calculate(amount, months, rate, tax, period, cap)
        assert r["final_amount"] >= 0.0

    @pytest.mark.parametrize("amount,months,rate,tax,period,cap", DEPOSIT_CASES)
    def test_interest_nonneg(
        self,
        dep: DepositCalculator,
        amount: float,
        months: int,
        rate: float,
        tax: float,
        period: str,
        cap: bool,
    ) -> None:
        """Verifies total_interest ≥ 0 for all parametrized inputs."""
        r = dep.calculate(amount, months, rate, tax, period, cap)
        assert r["total_interest"] >= 0.0

    @pytest.mark.parametrize(
        "amount,months,period",
        [
            (100_000, 12, "monthly"),
            (50_000, 6, "quarterly"),
            (200_000, 12, "annually"),
        ],
    )
    def test_zero_rate_gives_zero_interest(
        self, dep: DepositCalculator, amount: int, months: int, period: str
    ) -> None:
        """Verifies zero interest is accrued when annual_rate = 0."""
        r = dep.calculate(amount, months, 0.0, 0.0, period, False)
        assert math.isclose(r["total_interest"], 0.0, abs_tol=1e-9)

    @pytest.mark.parametrize(
        "amount,months,period",
        [
            (100_000, 12, "monthly"),
            (100_000, 12, "quarterly"),
        ],
    )
    def test_capitalize_gives_more_interest(
        self, dep: DepositCalculator, amount: int, months: int, period: str
    ) -> None:
        """Verify capitalization yields at least as much interest as payout."""
        no_cap = dep.calculate(amount, months, 10.0, 0.0, period, False)
        with_cap = dep.calculate(amount, months, 10.0, 0.0, period, True)
        assert with_cap["total_interest"] >= no_cap["total_interest"]

    @pytest.mark.parametrize(
        "rate_low,rate_high",
        [
            (5.0, 10.0),
            (1.0, 20.0),
        ],
    )
    def test_higher_rate_gives_more_interest(
        self, dep: DepositCalculator, rate_low: float, rate_high: float
    ) -> None:
        """Verifies higher interest rate yields more total interest."""
        low = dep.calculate(100_000, 12, rate_low, 0.0, "monthly", False)
        high = dep.calculate(100_000, 12, rate_high, 0.0, "monthly", False)
        assert high["total_interest"] > low["total_interest"]

    def test_final_amount_balance_tax_consistency(
        self, dep: DepositCalculator
    ) -> None:
        """Verify final = initial + interest - tax (no cap, no additions)."""
        amount = 100_000
        r = dep.calculate(amount, 12, 10.0, 13.0, "monthly", False)
        expected = amount + r["total_interest"] - r["tax_amount"]
        assert math.isclose(r["final_amount"], expected, rel_tol=1e-9)

    def test_addition_increases_final_amount(
        self, dep: DepositCalculator
    ) -> None:
        """Verify a scheduled deposit addition increases the final amount."""
        base = dep.calculate(100_000, 12, 10.0, 0.0, "monthly", False)
        with_add = dep.calculate(
            100_000,
            12,
            10.0,
            0.0,
            "monthly",
            False,
            additions=[{"month": 3, "amount": 20_000}],
        )
        assert with_add["final_amount"] > base["final_amount"]

    def test_payout_frequency_does_not_change_total_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Verify payout frequency doesn't change total interest without cap."""
        monthly = dep.calculate(100_000, 12, 12.0, 0.0, "monthly", False)
        quarterly = dep.calculate(100_000, 12, 12.0, 0.0, "quarterly", False)
        assert math.isclose(
            monthly["total_interest"],
            quarterly["total_interest"],
            rel_tol=1e-9,
            abs_tol=1e-6,
        )


# ---------------------------------------------------------------------------
# 2. Hypothesis-driven invariant checks
# ---------------------------------------------------------------------------


class TestDepositProperties:
    """Hypothesis-driven invariant checks for DepositCalculator."""

    @given(
        amount=st.floats(
            min_value=1.0, max_value=1e9, allow_nan=False, allow_infinity=False
        ),
        months=st.integers(min_value=1, max_value=600),
        rate=st.floats(
            min_value=0.0,
            max_value=100.0,
            allow_nan=False,
            allow_infinity=False,
        ),
        tax=st.floats(
            min_value=0.0,
            max_value=100.0,
            allow_nan=False,
            allow_infinity=False,
        ),
        period=st.sampled_from(["monthly", "quarterly", "annually"]),
        cap=st.booleans(),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_tax_always_fraction_of_interest(
        self,
        dep: DepositCalculator,
        amount: float,
        months: int,
        rate: float,
        tax: float,
        period: str,
        cap: bool,
    ) -> None:
        """tax_amount = total_interest * tax_rate / 100 always."""
        r = dep.calculate(amount, months, rate, tax, period, cap)
        assert math.isclose(
            r["tax_amount"],
            r["total_interest"] * tax / 100,
            rel_tol=1e-7,
            abs_tol=1e-9,
        )

    @given(
        amount=st.floats(
            min_value=1.0, max_value=1e9, allow_nan=False, allow_infinity=False
        ),
        months=st.integers(min_value=1, max_value=600),
        rate=st.floats(
            min_value=0.0,
            max_value=100.0,
            allow_nan=False,
            allow_infinity=False,
        ),
        period=st.sampled_from(["monthly", "quarterly", "annually"]),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_final_amount_consistency_no_cap(
        self,
        dep: DepositCalculator,
        amount: float,
        months: int,
        rate: float,
        period: str,
    ) -> None:
        """Final = initial + interest - tax (no capitalization)."""
        tax = 13.0
        r = dep.calculate(amount, months, rate, tax, period, capitalize=False)
        expected = amount + r["total_interest"] - r["tax_amount"]
        assert math.isclose(
            r["final_amount"], expected, rel_tol=1e-7, abs_tol=1e-6
        )

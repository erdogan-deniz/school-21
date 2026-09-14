"""Property-based and parametrized invariant tests for LoanCalculator.

Uses pytest.mark.parametrize for a fixed set of realistic loan inputs and
Hypothesis for arbitrary-value consistency checks.
"""

import math

import pytest
from hypothesis import HealthCheck, given, settings
from hypothesis import strategies as st

from model.loan import LoanCalculator


LOAN_CASES = [
    (10_000, 6, 6.0),
    (50_000, 12, 12.0),
    (100_000, 24, 9.5),
    (500_000, 60, 15.0),
    (1_000_000, 120, 8.0),
    (200_000, 36, 0.0),   # zero rate
    (75_000, 18, 24.0),   # high rate
]


# ---------------------------------------------------------------------------
# 1. Parametrized invariant tests
# ---------------------------------------------------------------------------


class TestLoanInvariants:
    """Properties that must hold for all loan inputs."""

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_annuity_total_equals_payment_times_months(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verify total = monthly_payment * months for all inputs."""
        r = loan.calculate_annuity(principal, months, rate)
        assert math.isclose(
            r["total"], r["monthly_payment"] * months, rel_tol=1e-9
        )

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_annuity_overpayment_equals_total_minus_principal(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verifies the identity overpayment = total - principal."""
        r = loan.calculate_annuity(principal, months, rate)
        assert math.isclose(
            r["overpayment"], r["total"] - principal, rel_tol=1e-9
        )

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_annuity_overpayment_nonnegative(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verifies overpayment ≥ 0 for all non-negative rates."""
        r = loan.calculate_annuity(principal, months, rate)
        assert r["overpayment"] >= -1e-9

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_differentiated_sum_equals_total(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verifies sum(payments) == total for differentiated schedule."""
        r = loan.calculate_differentiated(principal, months, rate)
        assert math.isclose(sum(r["payments"]), r["total"], rel_tol=1e-9)

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_differentiated_payments_monotone(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verify each differentiated payment is ≥ the next (non-increasing)."""
        r = loan.calculate_differentiated(principal, months, rate)
        for a, b in zip(r["payments"], r["payments"][1:], strict=False):
            assert a >= b - 1e-9

    @pytest.mark.parametrize("principal,months,rate", LOAN_CASES)
    def test_differentiated_overpayment_nonneg(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Verify differentiated overpayment ≥ 0 for all parametrized inputs."""
        r = loan.calculate_differentiated(principal, months, rate)
        assert r["overpayment"] >= -1e-9

    @pytest.mark.parametrize(
        "principal,months",
        [
            (12_000, 12),
            (24_000, 24),
            (60_000, 60),
        ],
    )
    def test_zero_rate_annuity_no_overpayment(
        self, loan: LoanCalculator, principal: int, months: int
    ) -> None:
        """Verify no overpayment and equal division for a zero-rate annuity."""
        r = loan.calculate_annuity(principal, months, 0.0)
        assert math.isclose(r["overpayment"], 0.0, abs_tol=1e-9)
        assert math.isclose(
            r["monthly_payment"], principal / months, rel_tol=1e-9
        )

    @pytest.mark.parametrize(
        "rate_low,rate_high",
        [
            (5.0, 10.0),
            (3.0, 12.0),
            (1.0, 20.0),
        ],
    )
    def test_annuity_monotone_in_rate(
        self, loan: LoanCalculator, rate_low: float, rate_high: float
    ) -> None:
        """Higher interest rate → higher overpayment (all else equal)."""
        low = loan.calculate_annuity(100_000, 12, rate_low)
        high = loan.calculate_annuity(100_000, 12, rate_high)
        assert high["overpayment"] > low["overpayment"]

    @pytest.mark.parametrize(
        "months_short,months_long",
        [
            (6, 12),
            (12, 24),
            (12, 60),
        ],
    )
    def test_annuity_monotone_in_term(
        self, loan: LoanCalculator, months_short: int, months_long: int
    ) -> None:
        """Longer term → higher total overpayment (all else equal)."""
        short = loan.calculate_annuity(100_000, months_short, 12.0)
        long_ = loan.calculate_annuity(100_000, months_long, 12.0)
        assert long_["overpayment"] > short["overpayment"]


# ---------------------------------------------------------------------------
# 2. Hypothesis-driven invariant checks
# ---------------------------------------------------------------------------


class TestLoanProperties:
    """Hypothesis-driven invariant checks for LoanCalculator."""

    @given(
        principal=st.floats(
            min_value=1_000,
            max_value=10_000_000,
            allow_nan=False,
            allow_infinity=False,
        ),
        months=st.integers(min_value=1, max_value=360),
        rate=st.floats(
            min_value=0.0, max_value=50.0, allow_nan=False, allow_infinity=False
        ),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_annuity_total_consistency(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """Total = monthly_payment * months, overpayment = total - principal."""
        r = loan.calculate_annuity(principal, months, rate)
        assert math.isclose(
            r["total"], r["monthly_payment"] * months, rel_tol=1e-7
        )
        assert math.isclose(
            r["overpayment"], r["total"] - principal, rel_tol=1e-7
        )
        assert r["overpayment"] >= -1e-6

    @given(
        principal=st.floats(
            min_value=1_000,
            max_value=10_000_000,
            allow_nan=False,
            allow_infinity=False,
        ),
        months=st.integers(min_value=1, max_value=360),
        rate=st.floats(
            min_value=0.0, max_value=50.0, allow_nan=False, allow_infinity=False
        ),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_differentiated_sum_consistency(
        self, loan: LoanCalculator, principal: float, months: int, rate: float
    ) -> None:
        """sum(payments) = total."""
        r = loan.calculate_differentiated(principal, months, rate)
        assert math.isclose(sum(r["payments"]), r["total"], rel_tol=1e-7)

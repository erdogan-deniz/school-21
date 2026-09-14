"""Unit tests for model.deposit.DepositCalculator."""

import math
from unittest.mock import MagicMock

import pytest

from model.deposit import DepositCalculator


class TestBasicDeposit:
    """Tests for simple interest accrual."""

    def test_monthly_interest_no_capitalize(
        self, dep: DepositCalculator
    ) -> None:
        """Verifies 12% annual on 100k for 12 months ≈ 12 000 ₽ interest."""
        result = dep.calculate(
            amount=100_000,
            months=12,
            annual_rate=12.0,
            tax_rate=0.0,
            period="monthly",
            capitalize=False,
        )
        assert math.isclose(result["total_interest"], 12_000.0, rel_tol=1e-3)

    def test_no_tax_when_rate_zero(self, dep: DepositCalculator) -> None:
        """Verifies tax_amount = 0 when tax_rate = 0."""
        result = dep.calculate(
            amount=50_000,
            months=6,
            annual_rate=8.0,
            tax_rate=0.0,
            period="monthly",
            capitalize=False,
        )
        assert math.isclose(result["tax_amount"], 0.0, abs_tol=1e-9)

    def test_tax_is_percentage_of_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Verifies tax_amount = total_interest * 13%."""
        result = dep.calculate(
            amount=100_000,
            months=12,
            annual_rate=10.0,
            tax_rate=13.0,
            period="monthly",
            capitalize=False,
        )
        expected_tax = result["total_interest"] * 0.13
        assert math.isclose(result["tax_amount"], expected_tax, rel_tol=1e-9)

    def test_capitalization_increases_final_amount(
        self, dep: DepositCalculator
    ) -> None:
        """Verify capitalization yields more interest than simple payout."""
        without = dep.calculate(100_000, 12, 10.0, 0.0, "monthly", False)
        with_cap = dep.calculate(100_000, 12, 10.0, 0.0, "monthly", True)
        assert with_cap["total_interest"] >= without["total_interest"]


class TestPeriods:
    """Tests for different payment periodicity options."""

    def test_payout_frequency_does_not_change_total_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Payout frequency doesn't change total interest (no compounding)."""
        monthly = dep.calculate(100_000, 12, 12.0, 0.0, "monthly", False)
        quarterly = dep.calculate(
            100_000, 12, 12.0, 0.0, "quarterly", False
        )
        assert math.isclose(
            monthly["total_interest"], quarterly["total_interest"],
            rel_tol=1e-9, abs_tol=1e-6,
        )

    def test_annually_supported(self, dep: DepositCalculator) -> None:
        """Smoke test: annual period produces positive interest."""
        result = dep.calculate(100_000, 12, 12.0, 0.0, "annually", False)
        assert result["total_interest"] > 0


class TestAdditionsAndWithdrawals:
    """Tests for scheduled additions and partial withdrawals."""

    def test_addition_increases_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Verifies that a mid-term deposit addition raises total interest."""
        base = dep.calculate(100_000, 12, 10.0, 0.0, "monthly", False)
        with_add = dep.calculate(
            100_000,
            12,
            10.0,
            0.0,
            "monthly",
            False,
            additions=[{"month": 6, "amount": 10_000}],
        )
        assert with_add["total_interest"] > base["total_interest"]


class TestPartialPeriodAndWithdrawals:
    """Tests for tail period and partial-period withdrawals."""

    def test_partial_period_quarterly(self, dep: DepositCalculator) -> None:
        """Verify positive interest for 5-month term with quarterly period."""
        # 5 months with quarterly period: month 3 pays out,
        # months 4-5 are a tail
        result = dep.calculate(100_000, 5, 12.0, 0.0, "quarterly", False)
        assert result["total_interest"] > 0

    def test_withdrawal_reduces_balance(
        self, dep: DepositCalculator
    ) -> None:
        """Verifies that a mid-term withdrawal lowers total interest."""
        base = dep.calculate(100_000, 12, 10.0, 0.0, "monthly", False)
        with_wd = dep.calculate(
            100_000,
            12,
            10.0,
            0.0,
            "monthly",
            False,
            withdrawals=[{"month": 6, "amount": 10_000}],
        )
        assert with_wd["total_interest"] < base["total_interest"]

    def test_withdrawal_cannot_go_negative(
        self, dep: DepositCalculator
    ) -> None:
        """Verify over-withdrawing clamps the balance to 0, not negative."""
        result = dep.calculate(
            100_000,
            12,
            10.0,
            0.0,
            "monthly",
            False,
            withdrawals=[{"month": 1, "amount": 999_999}],
        )
        assert result["final_amount"] >= 0

    def test_partial_period_capitalize(
        self, dep: DepositCalculator
    ) -> None:
        """Verify tail-period interest accrues with and without cap."""
        # Capitalize with non-divisible months should still accumulate
        # tail interest
        result_cap = dep.calculate(100_000, 5, 12.0, 0.0, "quarterly", True)
        result_no = dep.calculate(100_000, 5, 12.0, 0.0, "quarterly", False)
        assert result_cap["total_interest"] > 0
        assert result_no["total_interest"] > 0


class TestValidation:
    """Tests for input validation in DepositCalculator."""

    def test_zero_amount_raises(self, dep: DepositCalculator) -> None:
        """Verifies ValueError when amount = 0."""
        with pytest.raises(ValueError):
            dep.calculate(0, 12, 10.0, 0.0, "monthly", False)

    def test_invalid_period_raises(self, dep: DepositCalculator) -> None:
        """Verifies ValueError for an unsupported period string."""
        with pytest.raises(ValueError):
            dep.calculate(100_000, 12, 10.0, 0.0, "weekly", False)

    def test_tax_over_100_raises(self, dep: DepositCalculator) -> None:
        """Verifies ValueError when tax_rate > 100."""
        with pytest.raises(ValueError):
            dep.calculate(100_000, 12, 10.0, 101.0, "monthly", False)

    def test_zero_months_raises(self, dep: DepositCalculator) -> None:
        """Verifies ValueError when months = 0."""
        with pytest.raises(ValueError):
            dep.calculate(100_000, 0, 10.0, 0.0, "monthly", False)

    def test_negative_rate_raises(self, dep: DepositCalculator) -> None:
        """Verifies ValueError when annual_rate is negative."""
        with pytest.raises(ValueError):
            dep.calculate(100_000, 12, -1.0, 0.0, "monthly", False)

    def test_deposit_raises_on_c_error(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verify ValueError when C function returns non-zero."""
        dep = DepositCalculator()
        fake_lib = MagicMock()
        fake_lib.s21_deposit.return_value = 1
        monkeypatch.setattr(dep, "_lib", fake_lib)
        with pytest.raises(ValueError, match="C library error in s21_deposit"):
            dep.calculate(100_000, 12, 10.0, 0.0, "monthly", False)

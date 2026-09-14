"""Integration checks: functional coverage of all model layers."""

import math

import pytest

from model.calculator import Calculator
from model.deposit import DepositCalculator
from model.loan import LoanCalculator


class TestCalculatorBoundary:
    """Boundary and combined-expression tests for Calculator."""

    def test_255_char_accepted(self, calc: Calculator) -> None:
        """Verify a 255-character expression is accepted and evaluated."""
        # '1+0+0+...+0' is exactly 255 chars and evaluates to 1.0.
        expr = "1" + "+0" * 127
        assert len(expr) == 255
        assert math.isclose(calc.calculate(expr), 1.0, abs_tol=1e-9)

    def test_256_char_raises(self, calc: Calculator) -> None:
        """Verifies ValueError for a 256-character expression."""
        with pytest.raises(ValueError):
            calc.calculate("1" * 256)

    def test_mod_operator(self, calc: Calculator) -> None:
        """Verifies the 'mod' keyword operator: 10 mod 3 = 1."""
        assert math.isclose(calc.calculate("10 mod 3"), 1.0, abs_tol=1e-9)

    def test_log_plus_ln(self, calc: Calculator) -> None:
        """Verify log(100)+ln(1) = 2 (base-10 log, natural ln)."""
        # log(100) = 2.0  (base-10),  ln(1) = 0.0  (natural)
        assert math.isclose(calc.calculate("log(100)+ln(1)"), 2.0, rel_tol=1e-6)

    def test_nested_log(self, calc: Calculator) -> None:
        """Verifies log(log(100)) = log10(log10(100))."""
        expected = math.log10(math.log10(100))
        assert math.isclose(
            calc.calculate("log(log(100))"), expected, rel_tol=1e-6
        )

    def test_asin_acos_atan(self, calc: Calculator) -> None:
        """Verifies all three inverse trig functions at canonical inputs."""
        assert math.isclose(
            calc.calculate("asin(1)"), math.pi / 2, rel_tol=1e-6
        )
        assert math.isclose(
            calc.calculate("acos(0)"), math.pi / 2, rel_tol=1e-6
        )
        assert math.isclose(
            calc.calculate("atan(1)"), math.pi / 4, rel_tol=1e-6
        )

    def test_sqrt_product(self, calc: Calculator) -> None:
        """Verifies sqrt(2)*sqrt(2) = 2."""
        assert math.isclose(
            calc.calculate("sqrt(2)*sqrt(2)"), 2.0, rel_tol=1e-6
        )

    def test_sci_notation_small_not_zero(self, calc: Calculator) -> None:
        """Verifies sin(1e-5) ≠ 0 and matches Python's math.sin(1e-5)."""
        # Ensures Decimal conversion: sin(1e-5) must not be evaluated as sin(0).
        result = calc.calculate("sin(1e-5)")
        assert not math.isclose(result, 0.0, abs_tol=1e-9)
        assert math.isclose(result, math.sin(1e-5), rel_tol=1e-5)

    def test_division_by_zero_raises(self, calc: Calculator) -> None:
        """Verifies ValueError or OverflowError for 1/0."""
        with pytest.raises((ValueError, OverflowError)):
            calc.calculate("1/0")

    def test_empty_expression_raises(self, calc: Calculator) -> None:
        """Verifies an exception is raised for an empty string expression."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("")


class TestGraphBoundary:
    """Boundary tests for get_graph_points."""

    def test_sqrt_produces_none_for_negative_x(self, calc: Calculator) -> None:
        """Verifies None entries for x<0 domain of sqrt(x)."""
        _, ys = calc.get_graph_points("sqrt(x)", -5.0, 5.0, num_points=200)
        assert None in ys
        assert any(y is not None for y in ys)

    def test_equal_length_output(self, calc: Calculator) -> None:
        """Verifies xs and ys always have the same number of elements."""
        xs, ys = calc.get_graph_points("x^2", -3.0, 3.0, num_points=50)
        assert len(xs) == len(ys)

    def test_y_clipped_to_range(self, calc: Calculator) -> None:
        """Verify y values are clamped to ±1 000 001 for diverging exprs."""
        _, ys = calc.get_graph_points("1/x", 0.001, 1.0, num_points=50)
        for y in ys:
            if y is not None:
                assert -1_000_001 <= y <= 1_000_001


class TestLoanBoundary:
    """Boundary tests for LoanCalculator."""

    def test_zero_rate_annuity_no_overpayment(
        self, loan: LoanCalculator
    ) -> None:
        """Verify zero-rate annuity: payment = principal/months, overpay = 0."""
        r = loan.calculate_annuity(12_000, 12, 0.0)
        assert math.isclose(r["monthly_payment"], 1_000.0, abs_tol=1e-9)
        assert math.isclose(r["overpayment"], 0.0, abs_tol=1e-9)

    def test_zero_rate_differentiated_equal_payments(
        self, loan: LoanCalculator
    ) -> None:
        """Verifies all differentiated payments are equal when rate = 0."""
        r = loan.calculate_differentiated(12_000, 12, 0.0)
        assert all(
            math.isclose(p, 1_000.0, abs_tol=1e-9) for p in r["payments"]
        )

    def test_differentiated_payments_decreasing(
        self, loan: LoanCalculator
    ) -> None:
        """Verifies payments are monotonically non-increasing for rate > 0."""
        r = loan.calculate_differentiated(100_000, 12, 12.0)
        for a, b in zip(r["payments"], r["payments"][1:], strict=False):
            assert a >= b - 1e-9  # monotonically non-increasing

    def test_annuity_total_consistency(self, loan: LoanCalculator) -> None:
        """Verify total = payment * 24 and overpayment = total - principal."""
        r = loan.calculate_annuity(100_000, 24, 9.0)
        assert math.isclose(r["total"], r["monthly_payment"] * 24, rel_tol=1e-9)
        assert math.isclose(
            r["overpayment"], r["total"] - 100_000, rel_tol=1e-9
        )


class TestDepositBoundary:
    """Boundary tests for DepositCalculator."""

    def test_tax_is_fraction_of_interest(self, dep: DepositCalculator) -> None:
        """Verifies tax_amount = total_interest * 13%."""
        r = dep.calculate(100_000, 12, 12.0, 13.0, "monthly", False)
        assert math.isclose(
            r["tax_amount"], r["total_interest"] * 0.13, rel_tol=1e-9
        )

    def test_capitalization_gives_more_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Verify capitalization yields more interest than simple payout."""
        r_no = dep.calculate(100_000, 12, 12.0, 0.0, "monthly", False)
        r_yes = dep.calculate(100_000, 12, 12.0, 0.0, "monthly", True)
        assert r_yes["total_interest"] > r_no["total_interest"]

    def test_addition_increases_interest(self, dep: DepositCalculator) -> None:
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

    def test_withdrawal_reduces_interest(self, dep: DepositCalculator) -> None:
        """Verifies that a mid-term withdrawal reduces total interest."""
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

    def test_over_withdrawal_balance_nonnegative(
        self, dep: DepositCalculator
    ) -> None:
        """Verify balance clamps to 0 when withdrawals exceed the deposit."""
        r = dep.calculate(
            100_000,
            12,
            10.0,
            0.0,
            "monthly",
            False,
            withdrawals=[{"month": 1, "amount": 999_999}],
        )
        assert r["final_amount"] >= 0

    def test_annual_tail_period_accrues_interest(
        self, dep: DepositCalculator
    ) -> None:
        """Verify tail-month interest is accrued for 13-month annual deposit."""
        # 13 months with annual period: 1 year paid, 1 tail month accrued
        r = dep.calculate(100_000, 13, 12.0, 0.0, "annually", False)
        assert r["total_interest"] > 0

    def test_final_amount_equals_balance_minus_tax(
        self, dep: DepositCalculator
    ) -> None:
        """Verify final_amount = principal + interest - tax (no cap)."""
        r = dep.calculate(100_000, 12, 10.0, 13.0, "monthly", False)
        expected_final = 100_000 + r["total_interest"] - r["tax_amount"]
        assert math.isclose(r["final_amount"], expected_final, rel_tol=1e-9)

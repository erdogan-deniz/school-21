"""Unit tests for model.loan.LoanCalculator."""

import math
from unittest.mock import MagicMock

import pytest

from model.loan import LoanCalculator


class TestAnnuityPayments:
    """Tests for annuity (equal monthly payment) calculation."""

    def test_basic_annuity(self, loan: LoanCalculator) -> None:
        """Verifies monthly payment ≈ 8 884.88 ₽ for a 100k/12m/12% loan."""
        result = loan.calculate_annuity(100_000, 12, 12.0)
        assert math.isclose(result["monthly_payment"], 8884.88, rel_tol=1e-3)

    def test_total_greater_than_principal(self, loan: LoanCalculator) -> None:
        """Verifies total repayment exceeds the principal when rate > 0."""
        result = loan.calculate_annuity(100_000, 12, 12.0)
        assert result["total"] > 100_000

    def test_overpayment_positive(self, loan: LoanCalculator) -> None:
        """Verifies overpayment is positive when interest rate is positive."""
        result = loan.calculate_annuity(100_000, 12, 12.0)
        assert result["overpayment"] > 0

    def test_overpayment_equals_total_minus_principal(
        self, loan: LoanCalculator
    ) -> None:
        """Verifies the identity: overpayment = total - principal."""
        result = loan.calculate_annuity(50_000, 24, 10.0)
        assert math.isclose(
            result["total"] - 50_000, result["overpayment"], rel_tol=1e-9
        )

    def test_zero_rate(self, loan: LoanCalculator) -> None:
        """Verify a zero-rate loan has no overpayment and equal payments."""
        result = loan.calculate_annuity(12_000, 12, 0.0)
        assert math.isclose(result["monthly_payment"], 1000.0, rel_tol=1e-9)
        assert math.isclose(result["overpayment"], 0.0, abs_tol=1e-9)


class TestDifferentiatedPayments:
    """Tests for differentiated (decreasing) payment calculation."""

    def test_first_greater_than_last(self, loan: LoanCalculator) -> None:
        """Verifies that the first payment exceeds the last for rate > 0."""
        result = loan.calculate_differentiated(100_000, 12, 12.0)
        assert result["first_payment"] > result["last_payment"]

    def test_total_and_overpayment_present(self, loan: LoanCalculator) -> None:
        """Verify 'total' and 'overpayment' keys are present in the result."""
        result = loan.calculate_differentiated(100_000, 12, 12.0)
        assert "total" in result
        assert "overpayment" in result

    def test_payments_list_length(self, loan: LoanCalculator) -> None:
        """Verify the payments list length matches the term in months."""
        result = loan.calculate_differentiated(100_000, 6, 12.0)
        assert len(result["payments"]) == 6

    def test_payments_sum_equals_total(self, loan: LoanCalculator) -> None:
        """Verifies sum(payments) == total."""
        result = loan.calculate_differentiated(100_000, 12, 12.0)
        assert math.isclose(
            sum(result["payments"]), result["total"], rel_tol=1e-9
        )


class TestValidation:
    """Tests for input validation in LoanCalculator."""

    def test_zero_principal_raises(self, loan: LoanCalculator) -> None:
        """Verifies ValueError when principal = 0."""
        with pytest.raises(ValueError):
            loan.calculate_annuity(0, 12, 10.0)

    def test_negative_months_raises(self, loan: LoanCalculator) -> None:
        """Verifies ValueError when months is negative."""
        with pytest.raises(ValueError):
            loan.calculate_annuity(100_000, -1, 10.0)

    def test_negative_rate_raises(self, loan: LoanCalculator) -> None:
        """Verifies ValueError when annual_rate is negative."""
        with pytest.raises(ValueError):
            loan.calculate_annuity(100_000, 12, -5.0)

    def test_annuity_raises_on_c_error(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verify ValueError when C function returns non-zero."""
        loan = LoanCalculator()
        fake_lib = MagicMock()
        fake_lib.s21_loan_annuity.return_value = 1
        monkeypatch.setattr(loan, "_lib", fake_lib)
        with pytest.raises(
            ValueError, match="C library error in s21_loan_annuity"
        ):
            loan.calculate_annuity(100_000, 12, 12.0)

    def test_differentiated_raises_on_c_error(
        self, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verify ValueError when C function returns non-zero."""
        loan = LoanCalculator()
        fake_lib = MagicMock()
        fake_lib.s21_loan_differentiated.return_value = 1
        monkeypatch.setattr(loan, "_lib", fake_lib)
        with pytest.raises(
            ValueError, match="C library error in s21_loan_differentiated"
        ):
            loan.calculate_differentiated(100_000, 12, 12.0)

"""Shared base class for financial calculators."""


class FinanceCalculator:
    """Provide shared utilities for LoanCalculator and DepositCalculator."""

    @staticmethod
    def _validate_term_and_rate(months: int, annual_rate: float) -> None:
        """Raise ValueError if term or rate are invalid.

        Args:
            months: Loan/deposit term in months.
            annual_rate: Annual interest rate in percent.

        Raises:
            ValueError: If months ≤ 0 or annual_rate < 0.

        """
        if months <= 0:
            raise ValueError("Term must be a positive number of months.")
        if annual_rate < 0:
            raise ValueError("Annual rate must be non-negative.")

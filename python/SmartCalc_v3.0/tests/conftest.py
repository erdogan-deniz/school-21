"""Shared pytest configuration and fixtures for all tests."""

import sys

from PyQt6.QtCore import QCoreApplication
import pytest

from model.calculator import Calculator
from model.deposit import DepositCalculator
from model.loan import LoanCalculator


@pytest.fixture(scope="module")
def calc() -> Calculator:
    """Shared Calculator instance for one test module."""
    return Calculator()


@pytest.fixture(scope="module")
def loan() -> LoanCalculator:
    """Shared LoanCalculator instance for one test module."""
    return LoanCalculator()


@pytest.fixture(scope="module")
def dep() -> DepositCalculator:
    """Shared DepositCalculator instance for one test module."""
    return DepositCalculator()


@pytest.fixture(scope="session")
def qapp() -> QCoreApplication:
    """Single QCoreApplication for the entire test session.

    Required for any test that uses QObject signals.  Qt does not allow a
    second QApplication to be created after the first one is destroyed, so
    this must be session-scoped.
    """
    app = QCoreApplication.instance()
    if app is None:
        app = QCoreApplication(sys.argv)
    assert app is not None
    return app

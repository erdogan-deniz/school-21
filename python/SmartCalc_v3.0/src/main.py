"""Application entry point for SmartCalc v3.0."""

import os
import sys

from PyQt6.QtWidgets import QApplication, QMessageBox

from model.calculator import Calculator
from model.deposit import DepositCalculator
from model.history import History
from model.loan import LoanCalculator
from utils.config import AppConfig
from utils.logger import setup_logger
from view.main_window import MainWindow
from viewmodel.calc_viewmodel import CalcViewModel
from viewmodel.deposit_viewmodel import DepositViewModel
from viewmodel.loan_viewmodel import LoanViewModel


def main() -> int:
    """Initialise all layers, wire them together, and start the event loop.

    Returns:
        Exit code (0 on clean exit).

    """
    config = AppConfig()
    logger = setup_logger(config.rotation_period)
    logger.info("SmartCalc v3.0 starting")

    app = QApplication(sys.argv)
    app.setApplicationName("SmartCalc v3.0")

    try:
        calculator = Calculator()
        history = History()
        loan_model = LoanCalculator()
        deposit_model = DepositCalculator()
    except FileNotFoundError as exc:  # DLL missing; other init errors propagate
        QMessageBox.critical(
            None,
            "Library not found",
            f"{exc}\n\nRun 'make lib' to compile the C library.",
        )
        return 1

    calc_vm = CalcViewModel(calculator, history, precision=config.precision)
    loan_vm = LoanViewModel(loan_model)
    deposit_vm = DepositViewModel(deposit_model)

    window = MainWindow(
        calc_vm=calc_vm,
        loan_vm=loan_vm,
        deposit_vm=deposit_vm,
        font_size=config.font_size,
        theme=config.theme,
    )
    window.show()

    exit_code = 1
    try:
        exit_code = app.exec()
    finally:
        history.close()
    logger.info("SmartCalc v3.0 exiting with code %d", exit_code)
    return exit_code


if __name__ == "__main__":
    sys.path.insert(0, os.path.dirname(__file__))
    sys.exit(main())

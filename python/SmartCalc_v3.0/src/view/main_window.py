"""Main application window: tab container for all calculator modes."""

import logging
import os
from pathlib import Path

from PyQt6.QtGui import QAction
from PyQt6.QtWidgets import QHBoxLayout, QMainWindow, QTabWidget, QWidget

from view.calc_widget import CalcWidget
from view.deposit_widget import DepositWidget
from view.help_dialog import HelpDialog
from view.history_widget import HistoryWidget
from view.loan_widget import LoanWidget
from viewmodel.calc_viewmodel import CalcViewModel
from viewmodel.deposit_viewmodel import DepositViewModel
from viewmodel.loan_viewmodel import LoanViewModel


_logger = logging.getLogger("smartcalc")


class MainWindow(QMainWindow):
    """Top-level window that hosts the tab bar and history sidebar.

    Layout:
        ┌──────────────────────────────┬────────────┐
        │  Tabs: Calc | Loan | Deposit │  History   │
        └──────────────────────────────┴────────────┘
    """

    def __init__(
        self,
        calc_vm: CalcViewModel,
        loan_vm: LoanViewModel,
        deposit_vm: DepositViewModel,
        font_size: int = 14,
        theme: str = "light",
    ) -> None:
        """Create the main window and wire all sub-components.

        Args:
            calc_vm: CalcViewModel instance.
            loan_vm: LoanViewModel instance.
            deposit_vm: DepositViewModel instance.
            font_size: Application font size from config.
            theme: Color theme — 'light' or 'dark'.

        """
        super().__init__()
        self.setWindowTitle("SmartCalc v3.0")
        self.setMinimumSize(1000, 650)

        self._apply_theme(theme, font_size)
        self._build_menu()

        central = QWidget()
        self.setCentralWidget(central)
        root = QHBoxLayout(central)

        self._tabs = QTabWidget()
        self._calc_widget = CalcWidget(calc_vm)
        self._tabs.addTab(self._calc_widget, "Калькулятор")
        self._tabs.addTab(LoanWidget(loan_vm), "Кредит")
        self._tabs.addTab(DepositWidget(deposit_vm), "Депозит")
        root.addWidget(self._tabs, stretch=3)

        self._history = HistoryWidget()
        self._history.expression_selected.connect(self._load_from_history)
        self._history.clear_requested.connect(calc_vm.clear_history)
        calc_vm.history_updated.connect(self._history.update_history)
        root.addWidget(self._history, stretch=1)

        calc_vm.refresh_history()

    def _build_menu(self) -> None:
        """Create the Help menu with a "Справка" action."""
        menu_bar = self.menuBar()
        if menu_bar is None:
            return
        help_menu = menu_bar.addMenu("Справка")
        if help_menu is None:
            return
        about_action = QAction("О программе", self)  # noqa: RUF001
        about_action.triggered.connect(self._show_help)
        help_menu.addAction(about_action)

    def _load_from_history(self, expression: str) -> None:
        """Load an expression and switch to the calculator tab.

        Args:
            expression: Previously evaluated expression string.

        """
        self._tabs.setCurrentWidget(self._calc_widget)
        self._calc_widget.load_expression(expression)

    def _show_help(self) -> None:
        """Open the help dialog."""
        HelpDialog(self).exec()

    def _apply_theme(self, theme: str, font_size: int) -> None:
        """Apply a stylesheet based on the chosen theme and font size.

        Args:
            theme: Color theme — 'light' or 'dark'.
            font_size: Application font size in points.

        """
        base_style = f"font-size: {font_size}px;"
        if theme == "dark":
            qss_path = os.path.join(os.path.dirname(__file__), "styles.qss")
            try:
                dark_style = Path(qss_path).read_text(encoding="utf-8")
            except OSError:
                _logger.warning("Dark theme stylesheet not found: %s", qss_path)
                dark_style = ""
            self.setStyleSheet(base_style + dark_style)
        else:
            self.setStyleSheet(base_style)

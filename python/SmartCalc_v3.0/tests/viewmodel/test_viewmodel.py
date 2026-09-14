"""Tests for all three ViewModel classes (Calc, Loan, Deposit).

Strategy: instantiate Qt signal emitters without a real window.  A single
QCoreApplication is created for the entire test session; individual signals
are captured with a plain list connected via signal.connect(list.append).
"""

import threading

import pytest
from PyQt6.QtCore import QCoreApplication

from model.calculator import Calculator
from model.deposit import DepositCalculator
from model.history import History
from model.loan import LoanCalculator
from model.results import DepositResult
from viewmodel.calc_viewmodel import CalcViewModel
from viewmodel.deposit_viewmodel import DepositViewModel
from viewmodel.loan_viewmodel import LoanViewModel
from viewmodel.signal import Signal


# ---------------------------------------------------------------------------
# Signal
# ---------------------------------------------------------------------------


class TestSignal:
    """Unit tests for the pure-Python Signal observer."""

    def test_disconnect_specific_callback(self) -> None:
        """Verify disconnect(cb) removes only that callback."""
        sig = Signal()
        received: list[int] = []
        cb = received.append
        sig.connect(cb)
        sig.disconnect(cb)
        sig.emit(1)
        assert received == []

    def test_disconnect_nonexistent_callback_is_silent(self) -> None:
        """Verify disconnect(cb) does not raise for an unregistered callback."""
        sig = Signal()
        sig.disconnect(lambda: None)  # should not raise

    def test_disconnect_no_arg_clears_all(self) -> None:
        """Verify disconnect() with no argument removes all subscribers."""
        sig = Signal()
        received: list[int] = []
        sig.connect(received.append)
        sig.connect(received.append)
        sig.disconnect()
        sig.emit(1)
        assert received == []


# ---------------------------------------------------------------------------
# CalcViewModel
# ---------------------------------------------------------------------------


@pytest.fixture
def calc_vm(qapp: QCoreApplication) -> CalcViewModel:
    """Return a CalcViewModel wired to fresh Calculator and History."""
    calc = Calculator()
    history = History()
    return CalcViewModel(calc, history)


class TestCalcViewModelProperties:
    """Read-only properties exposed for View binding."""

    def test_graph_y_limit(self, calc_vm: CalcViewModel) -> None:
        """Verify graph_y_limit mirrors Calculator.GRAPH_Y_LIMIT."""
        assert calc_vm.graph_y_limit == Calculator.GRAPH_Y_LIMIT

    def test_max_input_length(self, calc_vm: CalcViewModel) -> None:
        """Verify max_input_length mirrors Calculator.MAX_INPUT_LENGTH."""
        assert calc_vm.max_input_length == Calculator.MAX_INPUT_LENGTH

    def test_precision_default(self, calc_vm: CalcViewModel) -> None:
        """Verify default precision is 7."""
        assert calc_vm.precision == 7


class TestCalcViewModelDisplay:
    """Token appending, backspace, clear, and 255-char guard."""

    def test_append_emits_display(self, calc_vm: CalcViewModel) -> None:
        """Verify appending a token emits display_changed with new expr."""
        received: list[str] = []
        calc_vm.display_changed.connect(received.append)
        calc_vm.append_token("2")
        assert received == ["2"]

    def test_append_multiple_tokens(self, calc_vm: CalcViewModel) -> None:
        """Verify three sequential tokens accumulate in the expression."""
        calc_vm.clear()
        received: list[str] = []
        calc_vm.display_changed.connect(received.append)
        calc_vm.append_token("3")
        calc_vm.append_token("+")
        calc_vm.append_token("4")
        assert received[-1] == "3+4"

    def test_backspace_removes_last_char(self, calc_vm: CalcViewModel) -> None:
        """Verify backspace trims the last character from the expression."""
        calc_vm.clear()
        calc_vm.append_token("9")
        calc_vm.append_token("9")
        received: list[str] = []
        calc_vm.display_changed.connect(received.append)
        calc_vm.backspace()
        assert received[-1] == "9"

    def test_clear_resets_expression(self, calc_vm: CalcViewModel) -> None:
        """Verifies that clear() emits display_changed with an empty string."""
        calc_vm.append_token("5")
        received: list[str] = []
        calc_vm.display_changed.connect(received.append)
        calc_vm.clear()
        assert received[-1] == ""

    def test_append_over_255_emits_error(self, calc_vm: CalcViewModel) -> None:
        """Verifies that a 256th character is rejected via error_occurred."""
        calc_vm.clear()
        # Fill to exactly 255
        for _ in range(255):
            calc_vm.append_token("1")
        errors: list[str] = []
        calc_vm.error_occurred.connect(errors.append)
        calc_vm.append_token("1")  # 256th char — must be rejected
        assert errors, "Expected an error signal when exceeding 255 chars"

    def test_append_exactly_255_is_accepted(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verify exactly 255 characters are accepted without an error."""
        calc_vm.clear()
        errors: list[str] = []
        calc_vm.error_occurred.connect(errors.append)
        for _ in range(255):
            calc_vm.append_token("1")
        assert not errors


class TestCalcViewModelCalculate:
    """calculate() → result_changed / error_occurred signals."""

    def test_empty_expression_does_nothing(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verifies that calculate() on an empty expression emits no signals."""
        calc_vm.clear()
        results: list[str] = []
        calc_vm.result_changed.connect(results.append)
        calc_vm.calculate()
        assert results == []

    def test_valid_expression_emits_result(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verifies that 2+3 emits result_changed with the value 5."""
        calc_vm.clear()
        calc_vm.append_token("2")
        calc_vm.append_token("+")
        calc_vm.append_token("3")
        results: list[str] = []
        calc_vm.result_changed.connect(results.append)
        calc_vm.calculate()
        assert results and results[0] == "5"

    def test_invalid_expression_emits_error(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verify an invalid expression emits error_occurred, not a result."""
        calc_vm.clear()
        for ch in "sin((":
            calc_vm.append_token(ch)
        errors: list[str] = []
        calc_vm.error_occurred.connect(errors.append)
        calc_vm.calculate()
        assert errors

    def test_calculate_updates_history(self, calc_vm: CalcViewModel) -> None:
        """Verify a successful calculation triggers a history_updated emit."""
        calc_vm.clear()
        for ch in "1+1":
            calc_vm.append_token(ch)
        history_payloads: list[list[str]] = []
        calc_vm.history_updated.connect(history_payloads.append)
        calc_vm.calculate()
        assert history_payloads  # at least one emit


class TestCalcViewModelGraph:
    """plot_graph() → graph_ready / error_occurred signals."""

    def test_empty_expression_emits_error(self, calc_vm: CalcViewModel) -> None:
        """Verifies that plot_graph on an empty expression emits an error."""
        calc_vm.clear()
        errors: list[str] = []
        calc_vm.error_occurred.connect(errors.append)
        calc_vm.plot_graph(-10, 10)
        assert errors

    def test_valid_expression_emits_graph(self, calc_vm: CalcViewModel) -> None:
        """Verifies plot_graph on 'x' emits graph_ready with non-empty segments."""
        calc_vm.clear()
        for ch in "x":
            calc_vm.append_token(ch)
        graphs: list[list[tuple[list[float], list[float]]]] = []
        calc_vm.graph_ready.connect(graphs.append)
        calc_vm.plot_graph(-5, 5)
        assert graphs
        segments = graphs[0]
        assert any(len(seg_x) > 0 for seg_x, _ in segments)

    def test_invalid_range_emits_error(self, calc_vm: CalcViewModel) -> None:
        """Verify error_occurred when x_min > x_max (inverted range)."""
        calc_vm.clear()
        for ch in "x":
            calc_vm.append_token(ch)
        errors: list[str] = []
        calc_vm.error_occurred.connect(errors.append)
        calc_vm.plot_graph(10, -10)  # inverted range → ValueError
        assert errors


class TestCalcViewModelHistory:
    """History management: load, clear, refresh."""

    def test_load_from_history_sets_expression(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verify load_from_history emits the expression via display_changed."""
        received: list[str] = []
        calc_vm.display_changed.connect(received.append)
        calc_vm.load_from_history("sin(x)")
        assert received[-1] == "sin(x)"

    def test_clear_history_emits_empty_list(
        self, calc_vm: CalcViewModel
    ) -> None:
        """Verify clear_history emits history_updated with an empty list."""
        payloads: list[list[str]] = []
        calc_vm.history_updated.connect(payloads.append)
        calc_vm.clear_history()
        assert payloads and payloads[-1] == []

    def test_refresh_history_emits_list(self, calc_vm: CalcViewModel) -> None:
        """Verify refresh_history emits the current history list."""
        payloads: list[list[str]] = []
        calc_vm.history_updated.connect(payloads.append)
        calc_vm.refresh_history()
        assert payloads and isinstance(payloads[-1], list)


# ---------------------------------------------------------------------------
# LoanViewModel
# ---------------------------------------------------------------------------


@pytest.fixture
def loan_vm(qapp: QCoreApplication) -> LoanViewModel:
    """Return a LoanViewModel wired to a fresh LoanCalculator."""
    return LoanViewModel(LoanCalculator())


class TestLoanViewModel:
    """LoanViewModel signal behaviour for annuity and differentiated types."""

    def test_annuity_emits_result(self, loan_vm: LoanViewModel) -> None:
        """Verify result_ready is emitted with a positive monthly_payment."""
        results: list[dict] = []
        loan_vm.result_ready.connect(results.append)
        loan_vm.calculate(100_000, 12, 12.0, 0)  # 0 = annuity
        assert results
        r = results[0]
        assert r["monthly_payment"] is not None
        assert r["monthly_payment"] > 0

    def test_differentiated_emits_result(self, loan_vm: LoanViewModel) -> None:
        """Verify result_ready is emitted with a payments list."""
        results: list[dict] = []
        loan_vm.result_ready.connect(results.append)
        loan_vm.calculate(100_000, 12, 12.0, 1)  # 1 = differentiated
        assert results
        r = results[0]
        assert r["payments"] is not None
        assert r["first_payment"] is not None
        assert r["last_payment"] is not None

    def test_zero_principal_emits_error(self, loan_vm: LoanViewModel) -> None:
        """Verifies error_occurred is emitted when principal = 0."""
        errors: list[str] = []
        loan_vm.error_occurred.connect(errors.append)
        loan_vm.calculate(0, 12, 12.0, 0)
        assert errors

    def test_zero_months_emits_error(self, loan_vm: LoanViewModel) -> None:
        """Verifies error_occurred is emitted when months = 0."""
        errors: list[str] = []
        loan_vm.error_occurred.connect(errors.append)
        loan_vm.calculate(100_000, 0, 12.0, 0)
        assert errors

    def test_negative_rate_emits_error(self, loan_vm: LoanViewModel) -> None:
        """Verifies error_occurred is emitted when annual_rate is negative."""
        errors: list[str] = []
        loan_vm.error_occurred.connect(errors.append)
        loan_vm.calculate(100_000, 12, -1.0, 0)
        assert errors

    def test_invalid_index_emits_error(self, loan_vm: LoanViewModel) -> None:
        """Verify an out-of-range payment type index emits error_occurred."""
        errors: list[str] = []
        loan_vm.error_occurred.connect(errors.append)
        loan_vm.calculate(50_000, 6, 10.0, 99)
        assert errors  # should emit an error, not silently succeed


# ---------------------------------------------------------------------------
# DepositViewModel
# ---------------------------------------------------------------------------


@pytest.fixture
def deposit_vm(qapp: QCoreApplication) -> DepositViewModel:
    """Return a DepositViewModel wired to a fresh DepositCalculator."""
    return DepositViewModel(DepositCalculator())


class TestDepositViewModel:
    """DepositViewModel signal behaviour."""

    def test_basic_calculate_emits_result(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verify result_ready is emitted with a positive total_interest."""
        results: list[DepositResult] = []
        deposit_vm.result_ready.connect(results.append)
        deposit_vm.calculate(100_000, 12, 8.0, 13.0, 0, False)  # 0 = monthly
        assert results
        r = results[0]
        assert "total_interest" in r
        assert r["total_interest"] > 0

    def test_with_additions_emits_result(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verify result_ready is emitted when additions are provided."""
        results: list[DepositResult] = []
        deposit_vm.result_ready.connect(results.append)
        deposit_vm.calculate(
            100_000,
            12,
            8.0,
            13.0,
            0,  # monthly
            False,
            additions=[("3", "10000")],
        )
        assert results

    def test_with_withdrawals_emits_result(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verifies result_ready is emitted for scheduled withdrawals."""
        results: list[DepositResult] = []
        deposit_vm.result_ready.connect(results.append)
        deposit_vm.calculate(
            100_000,
            12,
            8.0,
            13.0,
            0,  # monthly
            False,
            withdrawals=[("6", "5000")],
        )
        assert results

    def test_zero_months_emits_error(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verifies error_occurred is emitted when months = 0."""
        errors: list[str] = []
        deposit_vm.error_occurred.connect(errors.append)
        deposit_vm.calculate(100_000, 0, 8.0, 13.0, 0, False)
        assert errors

    def test_negative_rate_emits_error(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verifies error_occurred is emitted when annual_rate is negative."""
        errors: list[str] = []
        deposit_vm.error_occurred.connect(errors.append)
        deposit_vm.calculate(100_000, 12, -1.0, 13.0, 0, False)
        assert errors

    def test_capitalize_true_returns_higher_amount(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """Verify capitalization yields a higher final_amount than payout."""
        no_cap: list[DepositResult] = []
        with_cap: list[DepositResult] = []
        deposit_vm.result_ready.connect(no_cap.append)
        deposit_vm.calculate(100_000, 12, 8.0, 0.0, 0, False)
        deposit_vm.result_ready.disconnect(no_cap.append)

        deposit_vm.result_ready.connect(with_cap.append)
        deposit_vm.calculate(100_000, 12, 8.0, 0.0, 0, True)

        assert with_cap[0]["final_amount"] >= no_cap[0]["final_amount"]


class TestDepositViewModelParseTableRows:
    """Unit tests for DepositViewModel._parse_table_rows (business logic)."""

    def test_valid_rows_are_parsed(self) -> None:
        """Valid text pairs are converted to DepositEntry objects."""
        from model.results import DepositEntry

        entries, has_warn = DepositViewModel._parse_table_rows(
            [("1", "10000"), ("3", "5000.50")], max_month=12
        )
        assert not has_warn
        assert entries == [
            DepositEntry(month=1, amount=10000.0),
            DepositEntry(month=3, amount=5000.50),
        ]

    def test_month_exceeding_max_is_skipped_and_warns(self) -> None:
        """Row with month > max_month is dropped and has_out_of_range is True."""
        entries, has_warn = DepositViewModel._parse_table_rows(
            [("5", "1000"), ("13", "2000")], max_month=12
        )
        assert has_warn
        assert len(entries) == 1
        assert entries[0]["month"] == 5

    def test_invalid_text_rows_are_skipped(self) -> None:
        """Rows with non-numeric text are silently ignored."""
        entries, has_warn = DepositViewModel._parse_table_rows(
            [("abc", "def"), ("", ""), ("2", "500")], max_month=12
        )
        assert not has_warn
        assert len(entries) == 1
        assert entries[0]["month"] == 2

    def test_zero_month_is_skipped(self) -> None:
        """Row with month = 0 fails the month >= 1 guard and is dropped."""
        entries, has_warn = DepositViewModel._parse_table_rows(
            [("0", "1000")], max_month=12
        )
        assert not has_warn
        assert entries == []

    def test_zero_amount_is_skipped(self) -> None:
        """Row with amount = 0 fails the amount > 0 guard and is dropped."""
        entries, has_warn = DepositViewModel._parse_table_rows(
            [("1", "0")], max_month=12
        )
        assert not has_warn
        assert entries == []

    def test_negative_amount_is_skipped(self) -> None:
        """Row with a negative amount is dropped."""
        entries, has_warn = DepositViewModel._parse_table_rows(
            [("1", "-500")], max_month=12
        )
        assert not has_warn
        assert entries == []

    def test_empty_rows_returns_empty(self) -> None:
        """Empty input produces empty output without warnings."""
        entries, has_warn = DepositViewModel._parse_table_rows([], max_month=12)
        assert not has_warn
        assert entries == []

    def test_warning_emitted_on_out_of_range_addition(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """calculate() emits a non-empty warning when a row exceeds the term."""
        warnings: list[str] = []
        deposit_vm.warning_occurred.connect(warnings.append)
        deposit_vm.calculate(
            100_000,
            6,
            8.0,
            13.0,
            0,
            False,
            additions=[("10", "1000")],  # month 10 > term 6
        )
        assert warnings and warnings[-1] != ""

    def test_no_warning_emitted_when_rows_are_valid(
        self, deposit_vm: DepositViewModel
    ) -> None:
        """calculate() emits an empty warning string when all rows are valid."""
        warnings: list[str] = []
        deposit_vm.warning_occurred.connect(warnings.append)
        deposit_vm.calculate(
            100_000,
            12,
            8.0,
            13.0,
            0,
            False,
            additions=[("3", "5000")],
        )
        assert warnings and warnings[-1] == ""


# ---------------------------------------------------------------------------
# Signal thread safety
# ---------------------------------------------------------------------------


class TestSignalThreadSafety:
    """Verify Signal is safe to use from multiple threads simultaneously."""

    def test_concurrent_emit_delivers_all(self) -> None:
        """100 concurrent emits each deliver exactly one value."""
        sig = Signal()
        results: list[int] = []
        lock = threading.Lock()

        def cb(v: int) -> None:
            with lock:
                results.append(v)

        sig.connect(cb)
        threads = [
            threading.Thread(target=sig.emit, args=(i,)) for i in range(100)
        ]
        for t in threads:
            t.start()
        for t in threads:
            t.join()

        assert len(results) == 100

    def test_concurrent_connect_disconnect_no_error(self) -> None:
        """50 threads each connect, emit, and disconnect without crashing."""
        sig = Signal()
        errors: list[Exception] = []

        def worker() -> None:
            try:

                def cb(_: object) -> None:
                    pass

                sig.connect(cb)
                sig.emit(1)
                sig.disconnect(cb)
            except Exception as exc:
                errors.append(exc)

        threads = [threading.Thread(target=worker) for _ in range(50)]
        for t in threads:
            t.start()
        for t in threads:
            t.join()

        assert not errors

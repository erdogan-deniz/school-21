"""Unit tests for model.calculator.Calculator.

Covers:
- Basic arithmetic and math functions
- Variable x substitution
- Edge cases and error handling
- Calculator initialisation (library loading)
- Scientific notation preprocessing
- Overflow handling
- Graph point generation
- Expression parsing edge cases
- Scientific notation preprocessor edge cases
- ln/log function behaviour edge cases
- Variable x across preprocessing layers
"""

import math
from pathlib import Path

import pytest

from model.calculator import Calculator


# ---------------------------------------------------------------------------
# Basic arithmetic
# ---------------------------------------------------------------------------


class TestBasicArithmetic:
    """Tests for the four basic arithmetic operations."""

    def test_addition(self, calc: Calculator) -> None:
        """Verifies 2+3 = 5."""
        assert math.isclose(calc.calculate("2+3"), 5.0)

    def test_subtraction(self, calc: Calculator) -> None:
        """Verifies 10-4 = 6."""
        assert math.isclose(calc.calculate("10-4"), 6.0)

    def test_multiplication(self, calc: Calculator) -> None:
        """Verifies 3*4 = 12."""
        assert math.isclose(calc.calculate("3*4"), 12.0)

    def test_division(self, calc: Calculator) -> None:
        """Verifies 8/2 = 4."""
        assert math.isclose(calc.calculate("8/2"), 4.0)

    def test_integer_division_result(self, calc: Calculator) -> None:
        """Verify 1/3 matches Python's result within 7-digit tolerance."""
        assert math.isclose(calc.calculate("1/3"), 1 / 3, rel_tol=1e-7)

    def test_operator_precedence(self, calc: Calculator) -> None:
        """Verifies * binds tighter than +: 2+2*2 = 6, not 8."""
        assert math.isclose(calc.calculate("2+2*2"), 6.0)

    def test_parentheses(self, calc: Calculator) -> None:
        """Verifies parentheses override default precedence: (2+2)*2 = 8."""
        assert math.isclose(calc.calculate("(2+2)*2"), 8.0)

    def test_power(self, calc: Calculator) -> None:
        """Verifies 2^10 = 1024."""
        assert math.isclose(calc.calculate("2^10"), 1024.0)

    def test_modulo(self, calc: Calculator) -> None:
        """Verifies 10 mod 3 = 1."""
        assert math.isclose(calc.calculate("10 mod 3"), 1.0)

    def test_mod_precedence(self, calc: Calculator) -> None:
        """Verify mod same precedence as *: 2 mod 3 * 4 = 8, not 2 mod 12."""
        assert math.isclose(calc.calculate("2 mod 3 * 4"), 8.0)

    def test_unary_minus(self, calc: Calculator) -> None:
        """Verifies unary minus: -5+10 = 5."""
        assert math.isclose(calc.calculate("-5+10"), 5.0)

    def test_unary_plus(self, calc: Calculator) -> None:
        """Verifies unary plus: +5 = 5."""
        assert math.isclose(calc.calculate("+5"), 5.0)


# ---------------------------------------------------------------------------
# Math functions
# ---------------------------------------------------------------------------


class TestMathFunctions:
    """Tests for all supported mathematical functions."""

    def test_sin_zero(self, calc: Calculator) -> None:
        """Verifies sin(0) = 0."""
        assert math.isclose(calc.calculate("sin(0)"), 0.0, abs_tol=1e-7)

    def test_cos_zero(self, calc: Calculator) -> None:
        """Verifies cos(0) = 1."""
        assert math.isclose(calc.calculate("cos(0)"), 1.0, rel_tol=1e-7)

    def test_tan_zero(self, calc: Calculator) -> None:
        """Verifies tan(0) = 0."""
        assert math.isclose(calc.calculate("tan(0)"), 0.0, abs_tol=1e-7)

    def test_asin_zero(self, calc: Calculator) -> None:
        """Verifies asin(0) = 0."""
        assert math.isclose(calc.calculate("asin(0)"), 0.0, abs_tol=1e-7)

    def test_acos_one(self, calc: Calculator) -> None:
        """Verifies acos(1) = 0."""
        assert math.isclose(calc.calculate("acos(1)"), 0.0, abs_tol=1e-7)

    def test_atan_zero(self, calc: Calculator) -> None:
        """Verifies atan(0) = 0."""
        assert math.isclose(calc.calculate("atan(0)"), 0.0, abs_tol=1e-7)

    def test_sqrt(self, calc: Calculator) -> None:
        """Verifies sqrt(9) = 3."""
        assert math.isclose(calc.calculate("sqrt(9)"), 3.0, rel_tol=1e-7)

    def test_ln(self, calc: Calculator) -> None:
        """Verifies ln(1) = 0 (natural logarithm)."""
        assert math.isclose(calc.calculate("ln(1)"), 0.0, abs_tol=1e-7)

    def test_log(self, calc: Calculator) -> None:
        """Verifies log(100) = 2 (base-10 decimal logarithm per spec)."""
        assert math.isclose(calc.calculate("log(100)"), 2.0, rel_tol=1e-7)

    def test_sin_pi_half(self, calc: Calculator) -> None:
        """Verifies sin(π/2) = 1."""
        pi_half = "1.5707963267948966"
        assert math.isclose(
            calc.calculate(f"sin({pi_half})"), 1.0, rel_tol=1e-7
        )


# ---------------------------------------------------------------------------
# Variable x
# ---------------------------------------------------------------------------


class TestVariableX:
    """Tests for expressions containing the variable x."""

    def test_x_value(self, calc: Calculator) -> None:
        """Verifies that x alone evaluates to the supplied x argument."""
        assert math.isclose(calc.calculate("x", x=5.0), 5.0)

    def test_x_in_expression(self, calc: Calculator) -> None:
        """Verifies 2*x+1 with x=3 evaluates to 7."""
        assert math.isclose(calc.calculate("2*x+1", x=3.0), 7.0)

    def test_sin_x(self, calc: Calculator) -> None:
        """Verifies sin(x) with x=π/2 evaluates to 1."""
        x = math.pi / 2
        assert math.isclose(calc.calculate("sin(x)", x=x), 1.0, rel_tol=1e-7)

    def test_x_zero_default(self, calc: Calculator) -> None:
        """Verifies that x defaults to 0 when no x argument is provided."""
        assert math.isclose(calc.calculate("x+1"), 1.0)


# ---------------------------------------------------------------------------
# Edge cases and error handling
# ---------------------------------------------------------------------------


class TestEdgeCases:
    """Tests for boundary conditions and error handling."""

    def test_invalid_expression_raises(self, calc: Calculator) -> None:
        """Verifies that a malformed expression (2++2) raises ValueError."""
        with pytest.raises(ValueError):
            calc.calculate("2++2")

    def test_empty_expression_raises(self, calc: Calculator) -> None:
        """Verifies that an empty string raises an exception."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("")

    def test_expression_too_long_raises(self, calc: Calculator) -> None:
        """Verifies that a 256-character expression raises ValueError."""
        with pytest.raises(ValueError):
            calc.calculate("1" * 256)

    def test_nested_parentheses(self, calc: Calculator) -> None:
        """Verifies nested parentheses: ((2+3)*4)-5 = 15."""
        assert math.isclose(calc.calculate("((2+3)*4)-5"), 15.0)

    def test_decimal_input(self, calc: Calculator) -> None:
        """Verifies decimal operands: 1.5+2.5 = 4."""
        assert math.isclose(calc.calculate("1.5+2.5"), 4.0, rel_tol=1e-7)

    def test_large_number(self, calc: Calculator) -> None:
        """Verifies 1000*1000 = 1 000 000."""
        assert math.isclose(calc.calculate("1000*1000"), 1_000_000.0)

    def test_precision_7_digits(self, calc: Calculator) -> None:
        """Verify 1/7 matches Python's result within 7-digit tolerance."""
        result = calc.calculate("1/7")
        assert math.isclose(result, 1 / 7, rel_tol=1e-7)


# ---------------------------------------------------------------------------
# Calculator initialisation
# ---------------------------------------------------------------------------


class TestCalculatorInit:
    """Tests for Calculator.__init__ error handling."""

    def test_missing_library_raises(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verifies FileNotFoundError when the shared library file is absent."""
        import model.lib_loader as loader_mod

        monkeypatch.setattr(
            loader_mod.os.path,  # type: ignore[attr-defined]
            "dirname",
            lambda _: str(tmp_path),
        )
        # Reset the global _lib to force a fresh load attempt (monkeypatch
        # restores the original value automatically after the test).
        monkeypatch.setattr(loader_mod, "_lib", None)
        with pytest.raises(FileNotFoundError):
            loader_mod.load_lib()

    def test_macos_dylib_name_selected(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verifies the .dylib extension is chosen when running on macOS."""
        import model.lib_loader as loader_mod

        monkeypatch.setattr(  # type: ignore[attr-defined]
            loader_mod.os, "name", "posix"
        )
        monkeypatch.setattr(  # type: ignore[attr-defined]
            loader_mod.platform, "system", lambda: "Darwin"
        )
        monkeypatch.setattr(
            loader_mod.os.path,
            "dirname",
            lambda _: str(tmp_path),  # type: ignore[attr-defined]
        )
        # Reset the global _lib to force a fresh load attempt (monkeypatch
        # restores the original value automatically after the test).
        monkeypatch.setattr(loader_mod, "_lib", None)
        with pytest.raises(FileNotFoundError) as exc_info:
            loader_mod.load_lib()
        assert "libsmartcalc.dylib" in str(exc_info.value)

    def test_linux_so_name_selected(
        self, tmp_path: Path, monkeypatch: pytest.MonkeyPatch
    ) -> None:
        """Verifies the .so extension is chosen when running on Linux."""
        import model.lib_loader as loader_mod

        monkeypatch.setattr(  # type: ignore[attr-defined]
            loader_mod.os, "name", "posix"
        )
        monkeypatch.setattr(  # type: ignore[attr-defined]
            loader_mod.platform, "system", lambda: "Linux"
        )
        monkeypatch.setattr(
            loader_mod.os.path,
            "dirname",
            lambda _: str(tmp_path),  # type: ignore[attr-defined]
        )
        # Reset the global _lib to force a fresh load attempt (monkeypatch
        # restores the original value automatically after the test).
        monkeypatch.setattr(loader_mod, "_lib", None)
        with pytest.raises(FileNotFoundError) as exc_info:
            loader_mod.load_lib()
        assert "libsmartcalc.so" in str(exc_info.value)


# ---------------------------------------------------------------------------
# Scientific notation
# ---------------------------------------------------------------------------


class TestScientificNotation:
    """Tests for exponential / scientific notation input."""

    def test_simple_positive_exponent(self, calc: Calculator) -> None:
        """Verifies 1e2 = 100."""
        assert math.isclose(calc.calculate("1e2"), 100.0, rel_tol=1e-7)

    def test_negative_exponent(self, calc: Calculator) -> None:
        """Verifies 1e-3 = 0.001."""
        assert math.isclose(calc.calculate("1e-3"), 0.001, rel_tol=1e-7)

    def test_decimal_mantissa(self, calc: Calculator) -> None:
        """Verifies 2.5e2 = 250."""
        assert math.isclose(calc.calculate("2.5e2"), 250.0, rel_tol=1e-7)

    def test_sci_in_expression(self, calc: Calculator) -> None:
        """Verify mixed sci-notation expression: 1e2+1e1 = 110."""
        assert math.isclose(calc.calculate("1e2+1e1"), 110.0, rel_tol=1e-7)

    def test_very_small_exponent_not_zero(self, calc: Calculator) -> None:
        """Verifies 1e-5 expands correctly so that sin(1e-5) ≠ 0."""
        result = calc.calculate("sin(1e-5)")
        assert not math.isclose(result, 0.0, abs_tol=1e-9)


# ---------------------------------------------------------------------------
# Overflow
# ---------------------------------------------------------------------------


class TestOverflow:
    """Tests for overflow / infinite result handling."""

    def test_expression_exceeds_limit_after_expansion_raises(
        self, calc: Calculator
    ) -> None:
        """Verify ValueError when sci-notation expansion exceeds 255 chars."""
        expr = "1e100+1e100+1e100"
        with pytest.raises(ValueError, match="characters after expansion"):
            calc.calculate(expr)

    def test_division_by_zero_raises(self, calc: Calculator) -> None:
        """Verifies that 1/0 raises ValueError or OverflowError."""
        with pytest.raises((ValueError, OverflowError)):
            calc.calculate("1/0")

    def test_infinity_expression_raises(self, calc: Calculator) -> None:
        """Verify infinity expression raises ValueError or OverflowError."""
        with pytest.raises((ValueError, OverflowError)):
            calc.calculate("1000000^1000000")


# ---------------------------------------------------------------------------
# Graph points
# ---------------------------------------------------------------------------


class TestGraphPoints:
    """Tests for the get_graph_points helper."""

    def test_returns_equal_length_lists(self, calc: Calculator) -> None:
        """Verifies that xs and ys always have the same number of elements."""
        xs, ys = calc.get_graph_points(
            "sin(x)", -math.pi, math.pi, num_points=100
        )
        assert len(xs) == len(ys)

    def test_values_in_range(self, calc: Calculator) -> None:
        """Verify all non-None y values lie within [-1.01, 1.01] for sin(x)."""
        _, ys = calc.get_graph_points("sin(x)", -math.pi, math.pi)
        valid = [y for y in ys if y is not None]
        assert all(-1.01 <= y <= 1.01 for y in valid)

    def test_invalid_range_raises(self, calc: Calculator) -> None:
        """Verifies ValueError when x_min > x_max."""
        with pytest.raises(ValueError):
            calc.get_graph_points("x", 10, 5)

    def test_discontinuity_produces_none(self, calc: Calculator) -> None:
        """Verify that x<0 points for sqrt(x) yield None."""
        xs, ys = calc.get_graph_points("sqrt(x)", -5.0, 5.0, num_points=100)
        assert None in ys
        assert any(y is not None for y in ys)


# ---------------------------------------------------------------------------
# Expression parsing edge cases
# ---------------------------------------------------------------------------


class TestExpressionParsing:
    """Tests for unusual but syntactically valid expressions."""

    def test_multiple_unary_minus(self, calc: Calculator) -> None:
        """Verifies --5 (double unary minus) is rejected by the C parser."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("--5")

    def test_unary_minus_in_parens(self, calc: Calculator) -> None:
        """Verifies (-5)+10 = 5."""
        assert math.isclose(calc.calculate("(-5)+10"), 5.0, abs_tol=1e-9)

    def test_unary_plus_in_parens(self, calc: Calculator) -> None:
        """Verifies (+5) = 5."""
        assert math.isclose(calc.calculate("(+5)"), 5.0, abs_tol=1e-9)

    def test_trailing_operator_raises(self, calc: Calculator) -> None:
        """Verifies that a trailing operator ('2+') raises an exception."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("2+")

    def test_mismatched_parens_raises(self, calc: Calculator) -> None:
        """Verifies that unmatched opening parenthesis raises an exception."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("(2+3")

    def test_consecutive_operators_raises(self, calc: Calculator) -> None:
        """Verify consecutive binary operators ('2++2') raise an exception."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate("2++2")

    def test_integer_result(self, calc: Calculator) -> None:
        """Verifies 4/2 = 2."""
        assert math.isclose(calc.calculate("4/2"), 2.0, abs_tol=1e-9)

    def test_negative_result(self, calc: Calculator) -> None:
        """Verifies 3-10 = -7."""
        assert math.isclose(calc.calculate("3-10"), -7.0, abs_tol=1e-9)

    def test_zero_result(self, calc: Calculator) -> None:
        """Verifies 5-5 = 0."""
        assert math.isclose(calc.calculate("5-5"), 0.0, abs_tol=1e-9)

    def test_deep_nesting(self, calc: Calculator) -> None:
        """Verifies (((2))) = 2 (three levels of redundant parentheses)."""
        assert math.isclose(calc.calculate("(((2)))"), 2.0, abs_tol=1e-9)


# ---------------------------------------------------------------------------
# Scientific notation preprocessor edge cases
# ---------------------------------------------------------------------------


class TestScientificNotationEdges:
    """Edge cases for the scientific notation preprocessor."""

    def test_uppercase_e(self, calc: Calculator) -> None:
        """Verifies uppercase 'E' is accepted: 1E3 = 1000."""
        assert math.isclose(calc.calculate("1E3"), 1000.0, rel_tol=1e-9)

    def test_positive_exponent_sign(self, calc: Calculator) -> None:
        """Verifies explicit '+' sign in exponent is accepted: 1e+2 = 100."""
        assert math.isclose(calc.calculate("1e+2"), 100.0, rel_tol=1e-9)

    def test_sci_in_function_arg(self, calc: Calculator) -> None:
        """Verify sci notation in function arg: sin(1e-5) ≈ math.sin(1e-5)."""
        assert math.isclose(
            calc.calculate("sin(1e-5)"), math.sin(1e-5), rel_tol=1e-5
        )

    def test_sci_not_mangled_in_function_name(self, calc: Calculator) -> None:
        """Verify 'asin' is not corrupted by the sci-notation regex."""
        assert math.isclose(calc.calculate("asin(0)"), 0.0, abs_tol=1e-9)

    def test_multiple_sci_in_one_expression(self, calc: Calculator) -> None:
        """Verify multiple sci numbers in one expression: 1e2+2e1+3e0=123."""
        assert math.isclose(
            calc.calculate("1e2 + 2e1 + 3e0"), 123.0, rel_tol=1e-9
        )


# ---------------------------------------------------------------------------
# ln/log function behaviour edge cases
# ---------------------------------------------------------------------------


class TestLogLnBehavior:
    """Edge cases for ln (natural) and log (base-10) function behavior."""

    def test_log_in_subexpression(self, calc: Calculator) -> None:
        """Verify log() works correctly in a subexpression: 2*log(100) = 4."""
        assert math.isclose(calc.calculate("2*log(100)"), 4.0, rel_tol=1e-6)

    def test_ln_in_subexpression(self, calc: Calculator) -> None:
        """Verifies ln(e) = 1."""
        e = "2.718281828459045"
        assert math.isclose(calc.calculate(f"ln({e})"), 1.0, rel_tol=1e-6)

    def test_log_of_sci_notation(self, calc: Calculator) -> None:
        """Verifies log(1e3) = log(1000) = 3."""
        assert math.isclose(calc.calculate("log(1e3)"), 3.0, rel_tol=1e-5)

    def test_ln_of_sci_notation(self, calc: Calculator) -> None:
        """Verifies ln(1e0) = ln(1) = 0."""
        assert math.isclose(calc.calculate("ln(1e0)"), 0.0, abs_tol=1e-9)

    def test_asin_not_swapped(self, calc: Calculator) -> None:
        """Verifies asin(0) is not mistaken for a log/ln token."""
        assert math.isclose(calc.calculate("asin(0)"), 0.0, abs_tol=1e-9)

    def test_acos_not_swapped(self, calc: Calculator) -> None:
        """Verifies acos(1) is not mistaken for a log/ln token."""
        assert math.isclose(calc.calculate("acos(1)"), 0.0, abs_tol=1e-9)


# ---------------------------------------------------------------------------
# Variable x across preprocessing layers
# ---------------------------------------------------------------------------


class TestVariableXPreprocessing:
    """Tests for correct variable substitution across preprocessing."""

    def test_x_with_sci_coefficient(self, calc: Calculator) -> None:
        """Verifies sci coefficient multiplied by x: 1e2*x with x=2 = 200."""
        assert math.isclose(calc.calculate("1e2*x", x=2.0), 200.0, rel_tol=1e-9)

    def test_log_of_x(self, calc: Calculator) -> None:
        """Verifies log(x) with x=100 = 2."""
        assert math.isclose(
            calc.calculate("log(x)", x=100.0), 2.0, rel_tol=1e-6
        )

    def test_ln_of_x(self, calc: Calculator) -> None:
        """Verify ln(x) with x=e = 1."""
        assert math.isclose(
            calc.calculate("ln(x)", x=math.e), 1.0, rel_tol=1e-6
        )


# ---------------------------------------------------------------------------
# Bug fixes
# ---------------------------------------------------------------------------


class TestGetGraphPointsEdgeCases:
    """Tests for get_graph_points edge cases — bug fix coverage."""

    def test_zero_num_points_raises_value_error(
        self, calc: Calculator
    ) -> None:
        """Verify ValueError (not ZeroDivisionError) when num_points=0."""
        with pytest.raises(ValueError):
            calc.get_graph_points("x", -1.0, 1.0, num_points=0)

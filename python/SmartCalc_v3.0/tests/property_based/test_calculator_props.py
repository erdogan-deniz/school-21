"""Property-based and parametrized tests for model.calculator.Calculator.

Uses Hypothesis for mathematical identity checks and pytest.mark.parametrize
for an exhaustive table of known (expression, result) pairs.
"""

import math
from decimal import Decimal

import pytest
from hypothesis import HealthCheck, assume, given, settings
from hypothesis import strategies as st

from model.calculator import Calculator


def _fmt(x: float) -> str:
    """Format a float for safe embedding in a calculator expression string.

    - Wraps negative numbers in parentheses so that C-parser unary/binary
      operator ambiguities (like a*-b) are avoided.
    - Discards (via assume) values whose expanded scientific notation would
      exceed the C library's internal string-to-float buffer limits.
    """
    s = repr(x)
    if "e" in s.lower():
        expanded = format(Decimal(s.lstrip("-")), "f")
        if len(expanded) > 200:
            assume(False)
    if s.startswith("-"):
        return "(" + s + ")"
    return s


# ---------------------------------------------------------------------------
# 1. Property-based tests — mathematical identities
# ---------------------------------------------------------------------------


class TestCalculatorProperties:
    """Mathematical laws that must hold for arbitrary floating-point inputs."""

    @given(
        st.floats(
            min_value=-1e4, max_value=1e4, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=500,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_pythagorean_identity(self, calc: Calculator, x: float) -> None:
        """sin²(x) + cos²(x) = 1 for all x."""
        sx = calc.calculate(f"sin({_fmt(x)})")
        cx = calc.calculate(f"cos({_fmt(x)})")
        assert math.isclose(sx**2 + cx**2, 1.0, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=-1e4, max_value=1e4, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_sin_antisymmetry(self, calc: Calculator, x: float) -> None:
        """sin(-x) = -sin(x)."""
        pos = calc.calculate(f"sin({_fmt(x)})")
        neg = calc.calculate(f"sin({_fmt(-x)})")
        assert math.isclose(pos, -neg, rel_tol=1e-6, abs_tol=1e-10)

    @given(
        st.floats(
            min_value=-1e4, max_value=1e4, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_cos_symmetry(self, calc: Calculator, x: float) -> None:
        """cos(-x) = cos(x)."""
        pos = calc.calculate(f"cos({_fmt(x)})")
        neg = calc.calculate(f"cos({_fmt(-x)})")
        assert math.isclose(pos, neg, rel_tol=1e-6, abs_tol=1e-10)

    @given(
        st.floats(
            min_value=-10.0,
            max_value=10.0,
            allow_nan=False,
            allow_infinity=False,
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_double_angle_sin(self, calc: Calculator, x: float) -> None:
        """sin(2x) = 2·sin(x)·cos(x)."""
        lhs = calc.calculate(f"sin({_fmt(2 * x)})")
        sx = calc.calculate(f"sin({_fmt(x)})")
        cx = calc.calculate(f"cos({_fmt(x)})")
        assert math.isclose(lhs, 2 * sx * cx, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=1e-6, max_value=1e6, allow_nan=False, allow_infinity=False
        ),
        st.floats(
            min_value=1e-6, max_value=1e6, allow_nan=False, allow_infinity=False
        ),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_log_product_rule(
        self, calc: Calculator, a: float, b: float
    ) -> None:
        """log(a·b) = log(a) + log(b) for a,b > 0."""
        product = a * b
        assume(math.isfinite(product) and product > 0)
        lhs = calc.calculate(f"log({_fmt(product)})")
        rhs = calc.calculate(f"log({_fmt(a)})") + calc.calculate(
            f"log({_fmt(b)})"
        )
        assert math.isclose(lhs, rhs, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=1e-6, max_value=1e6, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_log_power_rule(self, calc: Calculator, a: float) -> None:
        """log(a²) = 2·log(a) for a > 0."""
        lhs = calc.calculate(f"log({_fmt(a * a)})")
        rhs = 2 * calc.calculate(f"log({_fmt(a)})")
        assert math.isclose(lhs, rhs, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=1e-6, max_value=1e4, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_ln_log_relation(self, calc: Calculator, a: float) -> None:
        """ln(a) = log(a) · ln(10).  Verifies the two bases are consistent."""
        ln_a = calc.calculate(f"ln({_fmt(a)})")
        log_a = calc.calculate(f"log({_fmt(a)})")
        assert math.isclose(
            ln_a, log_a * math.log(10), rel_tol=1e-5, abs_tol=1e-9
        )

    @given(
        st.floats(
            min_value=0.0, max_value=1e6, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_sqrt_square(self, calc: Calculator, x: float) -> None:
        """sqrt(x)² = x for x ≥ 0."""
        sq = calc.calculate(f"sqrt({_fmt(x)})")
        assert math.isclose(sq * sq, x, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=-1e6, max_value=1e6, allow_nan=False, allow_infinity=False
        ),
        st.floats(
            min_value=-1e6, max_value=1e6, allow_nan=False, allow_infinity=False
        ),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_addition_commutativity(
        self, calc: Calculator, a: float, b: float
    ) -> None:
        """A + b = b + a."""
        lhs = calc.calculate(f"{_fmt(a)}+{_fmt(b)}")
        rhs = calc.calculate(f"{_fmt(b)}+{_fmt(a)}")
        assert math.isclose(lhs, rhs, rel_tol=1e-9, abs_tol=1e-12)

    @given(
        st.floats(
            min_value=-1e4, max_value=1e4, allow_nan=False, allow_infinity=False
        ),
        st.floats(
            min_value=-1e4, max_value=1e4, allow_nan=False, allow_infinity=False
        ),
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_multiplication_commutativity(
        self, calc: Calculator, a: float, b: float
    ) -> None:
        """A * b = b * a."""
        prod = a * b
        assume(math.isfinite(prod))
        lhs = calc.calculate(f"{_fmt(a)}*{_fmt(b)}")
        rhs = calc.calculate(f"{_fmt(b)}*{_fmt(a)}")
        assert math.isclose(lhs, rhs, rel_tol=1e-9, abs_tol=1e-12)

    @given(
        st.floats(
            min_value=-1e6, max_value=1e6, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_additive_inverse(self, calc: Calculator, x: float) -> None:
        """X + (-x) = 0."""
        result = calc.calculate(f"{_fmt(x)}+({_fmt(-x)})")
        assert math.isclose(result, 0.0, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=-1e4,
            max_value=1e4,
            allow_nan=False,
            allow_infinity=False,
            exclude_min=True,
        ).filter(lambda x: abs(x) > 1e-9)
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_multiplicative_inverse(self, calc: Calculator, x: float) -> None:
        """X * (1/x) = 1 for x ≠ 0."""
        result = calc.calculate(f"{_fmt(x)}*(1/{_fmt(x)})")
        assert math.isclose(result, 1.0, rel_tol=1e-5, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=-1.0, max_value=1.0, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_asin_sin_roundtrip(self, calc: Calculator, x: float) -> None:
        """sin(asin(x)) = x for x in [-1, 1]."""
        result = calc.calculate(f"sin(asin({_fmt(x)}))")
        assert math.isclose(result, x, rel_tol=1e-6, abs_tol=1e-9)

    @given(
        st.floats(
            min_value=-1.0, max_value=1.0, allow_nan=False, allow_infinity=False
        )
    )
    @settings(
        max_examples=300,
        suppress_health_check=[HealthCheck.function_scoped_fixture],
    )
    def test_acos_cos_roundtrip(self, calc: Calculator, x: float) -> None:
        """cos(acos(x)) = x for x in [-1, 1]."""
        result = calc.calculate(f"cos(acos({_fmt(x)}))")
        assert math.isclose(result, x, rel_tol=1e-6, abs_tol=1e-9)


# ---------------------------------------------------------------------------
# 2. Parametrized tests — specific inputs with known results
# ---------------------------------------------------------------------------


class TestCalculatorParametrized:
    """Exhaustive table of (expression, expected) pairs."""

    @pytest.mark.parametrize(
        "expr,expected",
        [
            # Arithmetic
            ("1+2+3+4+5", 15.0),
            ("100-37", 63.0),
            ("7*8", 56.0),
            ("144/12", 12.0),
            ("2^8", 256.0),
            ("(-3)^2", 9.0),
            ("(-2)^3", -8.0),
            ("17 mod 5", 2.0),
            ("1000 mod 7", 6.0),
            # Nested
            ("(1+2)*(3+4)", 21.0),
            ("((10-3)*2)^2", 196.0),
            ("10/(2+3)", 2.0),
            # Trig
            ("sin(0)", 0.0),
            ("cos(0)", 1.0),
            ("tan(0)", 0.0),
            ("sin(3.14159265358979/6)", 0.5),
            ("cos(3.14159265358979/3)", 0.5),
            # Log / ln
            ("log(1)", 0.0),
            ("log(10)", 1.0),
            ("log(100)", 2.0),
            ("log(1000)", 3.0),
            ("ln(1)", 0.0),
            ("ln(2.718281828459045)", 1.0),
            # Sqrt
            ("sqrt(0)", 0.0),
            ("sqrt(1)", 1.0),
            ("sqrt(4)", 2.0),
            ("sqrt(9)", 3.0),
            ("sqrt(144)", 12.0),
            ("sqrt(2)*sqrt(2)", 2.0),
            # Mixed
            ("sqrt(sin(0)^2+cos(0)^2)", 1.0),
            ("log(sqrt(100))", 1.0),
            ("ln(sqrt(2.718281828459045))", 0.5),
            # Fractions
            ("1/3+1/3+1/3", 1.0),
            ("1/6+1/6+1/6+1/6+1/6+1/6", 1.0),
            # Sci notation
            ("1e3/1e1", 100.0),
            ("5e2-4e2", 100.0),
        ],
    )
    def test_known_result(
        self, calc: Calculator, expr: str, expected: float
    ) -> None:
        """Verify each expression evaluates to its expected value."""
        result = calc.calculate(expr)
        assert math.isclose(result, expected, rel_tol=1e-5, abs_tol=1e-7), (
            f"{expr!r}: got {result}, expected {expected}"
        )

    @pytest.mark.parametrize(
        "expr",
        [
            "2++2",
            "2**2",
            "(/3)",
            "()",
            "2+",
            "+",
            "((2+3)",
            "2+3)",
            "abc",
        ],
    )
    def test_invalid_expressions_raise(
        self, calc: Calculator, expr: str
    ) -> None:
        """Parametrized check: each malformed expression raises an exception."""
        with pytest.raises((ValueError, Exception)):
            calc.calculate(expr)

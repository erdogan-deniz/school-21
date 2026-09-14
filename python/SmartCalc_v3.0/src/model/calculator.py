"""Calculator model: ctypes wrapper around the C shared library."""

import ctypes
import math
import os
import re
from decimal import Decimal, InvalidOperation
from typing import ClassVar

from model.lib_loader import load_lib


class Calculator:
    """Wrap the C SmartCalc v1.0 shared library via ctypes.

    The underlying C function signature is:
        long double s21_calculator(char* string, long double* x)

    Returns NaN on invalid expression.
    """

    MAX_INPUT_LENGTH: ClassVar[int] = 255
    # Graph y-values outside this range are treated as discontinuities and
    # rendered as gaps.  The same constant is used in calc_widget.py for the
    # spinbox range so both layers stay in sync.
    GRAPH_Y_LIMIT: ClassVar[int] = 1_000_000

    # Matches scientific notation numbers: 1e5, 2.5e-3, 1E+10, etc.
    # Negative lookbehind prevents matching inside identifiers like 'acos'.
    _SCI_RE: ClassVar[re.Pattern[str]] = re.compile(
        r"(?<![a-zA-Z])(\d+\.?\d*[eE][+-]?\d+)"
    )

    def __init__(self) -> None:
        """Load the shared library and configure ctypes argtypes/restype.

        Raises:
            FileNotFoundError: If the compiled shared library is absent.

        """
        self._lib: ctypes.CDLL = load_lib()
        # MSVC x64 compiles long double as 64-bit double; GCC uses 80-bit.
        # Use c_double on Windows for correct ABI compatibility.
        float_type = ctypes.c_double if os.name == "nt" else ctypes.c_longdouble
        self._lib.s21_calculator.restype = float_type
        self._lib.s21_calculator.argtypes = [
            ctypes.c_char_p,
            ctypes.POINTER(float_type),
        ]
        self.float_type: type[ctypes.c_double] | type[ctypes.c_longdouble] = (
            float_type
        )

    def calculate(self, expression: str, x: float = 0.0) -> float:
        """Evaluate an arithmetic expression.

        Args:
            expression: Infix notation string, up to 255 characters.
                Supports: +, -, *, /, ^, mod, sin, cos, tan,
                asin, acos, atan, sqrt, ln, log, and variable x.
                Scientific notation is accepted (e.g. 1e5, 2.5e-3).
                ln(x) returns the natural logarithm; log(x) returns base-10.
            x: Value to substitute for variable 'x'. Defaults to 0.

        Returns:
            Result of the expression as a float.

        Raises:
            ValueError: If the expression is invalid or causes a math error.
            OverflowError: If the result exceeds the allowed range.

        """
        if len(expression) > self.MAX_INPUT_LENGTH:
            raise ValueError(
                f"Expression exceeds {self.MAX_INPUT_LENGTH} characters."
            )

        # Preprocess before handing to the C library.
        preprocessed = self._expand_scientific_notation(expression)

        if len(preprocessed) > self.MAX_INPUT_LENGTH:
            raise ValueError(
                f"Expression exceeds {self.MAX_INPUT_LENGTH} "
                "characters after expansion."
            )

        x_val = self.float_type(x)
        raw = self._lib.s21_calculator(
            preprocessed.encode("utf-8"),
            ctypes.byref(x_val),
        )
        result = float(raw)

        if math.isnan(result):
            raise ValueError(f"Invalid expression: {expression!r}")
        if math.isinf(result):
            raise OverflowError("Result is out of range (infinity).")

        return result

    def get_graph_points(
        self,
        expression: str,
        x_min: float,
        x_max: float,
        num_points: int = 500,
    ) -> tuple[list[float], list[float | None]]:
        """Compute (x, y) points for plotting a function f(x).

        Args:
            expression: Expression with variable x.
            x_min: Start of the definition domain.
            x_max: End of the definition domain.
            num_points: Number of sample points. Defaults to 500.

        Returns:
            Tuple (xs, ys) where None values mark discontinuities.

        Raises:
            ValueError: If x_min >= x_max.

        """
        if x_min >= x_max:
            raise ValueError("x_min must be less than x_max.")
        if num_points <= 0:
            raise ValueError("num_points must be a positive integer.")

        step = (x_max - x_min) / num_points
        xs: list[float] = []
        ys: list[float | None] = []

        for i in range(num_points + 1):
            x = x_min + i * step
            xs.append(x)
            try:
                y = self.calculate(expression, x)
                limit = self.GRAPH_Y_LIMIT
                ys.append(y if -limit <= y <= limit else None)
            except (ValueError, OverflowError):
                ys.append(None)

        return xs, ys

    @staticmethod
    def _expand_scientific_notation(expression: str) -> str:
        """Convert scientific notation numbers to decimal form for the C parser.

        The C library parser does not support exponential notation. This method
        rewrites numbers like 1e5 or 2.5e-3 to their decimal equivalents,
        capped at 15 decimal places to stay within the C library's internal
        string-to-float buffer limits.

        Args:
            expression: Raw expression string possibly containing sci notation.

        Returns:
            Expression with all scientific notation expanded to decimal.

        """
        quant = Decimal("1e-15")  # 15 decimal places — enough for float64

        def _replace(match: re.Match[str]) -> str:
            """Convert one regex match of a sci-notation token to decimal.

            Args:
                match: Regex match object containing the sci-notation token.

            Returns:
                Decimal string representation of the matched number.

            """
            d = Decimal(match.group(0))
            try:
                # Quantize to 15 dp: prevents C-library buffer overflow for
                # tiny values like 1e-53 (which would otherwise expand to
                # 71 chars).  Quantize fails for very large exponents (e.g.
                # 1e100 needs 115 significant digits); in that case fall back
                # to full expansion and let the post-expansion length guard
                # reject it.
                return format(d.quantize(quant), "f")
            except InvalidOperation:
                return format(d, "f")

        return Calculator._SCI_RE.sub(_replace, expression)

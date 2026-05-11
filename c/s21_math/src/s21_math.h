/**
 * @file s21_math.h
 * @brief Own implementation of the C standard `math.h` library.
 *
 * `s21_math` is a drop-in subset of the C11 `<math.h>` header:
 * trigonometric, logarithmic, exponential, rounding, and absolute-value
 * functions, all prefixed with `s21_` to coexist with the standard
 * library in the same translation unit.
 *
 * Accuracy contract (verified by `unit_test.c` against the system
 * `<math.h>`):
 * - 16 significant digits overall.
 * - 6 decimal places in the fractional part.
 *
 * Reference: ISO/IEC 9899:2011 (C11) §7.12 *Mathematics `<math.h>`*.
 *
 * @copyright MIT for the repository as a whole; the School 21
 *            placeholder licence file inside this subproject is
 *            preserved as educational attribution.
 */

#ifndef S21_MATH
#define S21_MATH

#include <float.h>
#include <stdio.h>

/** @name Numeric constants
 *  Compile-time constants used throughout the library and by callers.
 *  @{
 */

/** Convergence threshold for the Taylor-series approximations used in
 *  the trig / log / exp implementations. */
#define S21_EPS 1e-9

/** Quiet NaN sentinel (matches `<math.h>` `NAN` in comparisons). */
#define S21_NAN 0.0 / 0.0

/** Signed-negative NaN sentinel used by `s21_asin` / `s21_acos` for
 *  out-of-domain inputs. */
#define S21_NAN2 -0.0 / 0.0

/** Positive infinity sentinel (matches `<math.h>` `INFINITY`). */
#define S21_INF 1.0 / 0.0

/** Negative infinity sentinel. */
#define S21__INF -1.0 / 0.0

/** π to 20 significant digits (more than `long double` precision). */
#define S21_PI 3.14159265358979323846

/** @} */

/** @name Absolute value
 *  @{
 */

/**
 * @brief Integer absolute value.
 * @param x Input integer (may be `INT_MIN`).
 * @return `|x|` as `int`; behaviour at `INT_MIN` matches `<stdlib.h>`
 *         `abs` (implementation-defined — typically wraps).
 */
int s21_abs(int);

/**
 * @brief Floating-point absolute value.
 * @param x Input `double`.
 * @return `|x|` as `long double`; NaN propagates.
 */
long double s21_fabs(double);

/** @} */

/** @name Power and logarithm
 *  @{
 */

/**
 * @brief Compute `base` raised to `exp`.
 *
 * Handles integer exponents fast-path; falls back to
 * `exp(exp * log(base))` for non-integer exponents. Negative `base`
 * with non-integer `exp` returns NaN per IEEE 754.
 *
 * @param base Base (any finite real, including 0).
 * @param exp  Exponent (any finite real).
 * @return `base^exp` as `long double`.
 */
long double s21_pow(double, double);

/**
 * @brief Natural logarithm (base e).
 * @param x Strictly positive `double`.
 * @return `ln(x)` as `long double`; returns `-INF` at 0,
 *         NaN at negatives.
 */
long double s21_log(double);

/**
 * @brief e raised to the given power.
 * @param x Exponent (any finite real).
 * @return `e^x` as `long double`; returns `INF` on overflow.
 */
long double s21_exp(double);

/**
 * @brief Square root.
 * @param x Non-negative `double`.
 * @return `√x` as `long double`; returns NaN for negative input.
 */
long double s21_sqrt(double);

/** @} */

/** @name Rounding
 *  @{
 */

/**
 * @brief Smallest integer not less than `x`.
 * @param x Input `double`.
 * @return `⌈x⌉` as `long double`.
 */
long double s21_ceil(double);

/**
 * @brief Largest integer not greater than `x`.
 * @param x Input `double`.
 * @return `⌊x⌋` as `long double`.
 */
long double s21_floor(double);

/**
 * @brief Floating-point remainder of `x / y` (IEEE 754 `fmod`).
 *
 * Returns `x - (n * y)` where `n` is the integer quotient of `x / y`
 * truncated toward zero. Sign of result matches sign of `x`.
 *
 * @param x Numerator (any finite real).
 * @param y Divisor (any non-zero finite real).
 * @return Remainder as `long double`; NaN if `y == 0`.
 */
long double s21_fmod(double, double);

/** @} */

/** @name Trigonometry — direct
 *  All inputs in radians. Range reduction folds into `[0, 2π)` for
 *  accuracy preservation.
 *  @{
 */

/**
 * @brief Cosine.
 * @param x Angle in radians.
 * @return `cos(x)`.
 */
long double s21_cos(double);

/**
 * @brief Sine.
 * @param x Angle in radians.
 * @return `sin(x)`.
 */
long double s21_sin(double);

/**
 * @brief Tangent.
 * @param x Angle in radians.
 * @return `tan(x)`; NaN at `π/2 + kπ`.
 */
long double s21_tan(double);

/** @} */

/** @name Trigonometry — inverse
 *  All outputs in radians.
 *  @{
 */

/**
 * @brief Arc cosine.
 * @param x In `[-1, 1]`.
 * @return `acos(x)` in `[0, π]`; NaN out of domain.
 */
long double s21_acos(double);

/**
 * @brief Arc sine.
 * @param x In `[-1, 1]`.
 * @return `asin(x)` in `[-π/2, π/2]`; NaN out of domain.
 */
long double s21_asin(double);

/**
 * @brief Arc tangent.
 * @param x Any finite real.
 * @return `atan(x)` in `(-π/2, π/2)`.
 */
long double s21_atan(double);

/** @} */

/** @name Combinatorics (helper, beyond `<math.h>` proper)
 *  @{
 */

/**
 * @brief Factorial: `n!`.
 *
 * Used internally by the Taylor-series approximations. Returns
 * `long double` to extend the representable range.
 *
 * @param n Non-negative integer.
 * @return `n!` as `long double`; `1.0` for `n ≤ 1`.
 */
long double s21_factorial(int);

/** @} */

#endif

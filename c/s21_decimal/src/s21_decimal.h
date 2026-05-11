/**
 * @file s21_decimal.h
 * @brief Fixed-precision decimal arithmetic library — modeled on .NET
 *        `System.Decimal`.
 *
 * `s21_decimal` represents decimal numbers in the range
 * `±79,228,162,514,264,337,593,543,950,335` with up to 28 decimal places
 * of fraction. Internally a 4-element `int[4]` array: bits[0..2] hold a
 * 96-bit integer mantissa, bits[3] packs the scale factor (10^N divisor,
 * `N ∈ [0, 28]`) and the sign bit.
 *
 * Use this library when IEEE 754 `float`/`double` rounding error is
 * unacceptable — typically financial calculations.
 *
 * Return-code convention (arithmetic operators):
 * - `0` — OK.
 * - `1` — number too large (overflow toward +∞).
 * - `2` — number too small (overflow toward −∞).
 * - `3` — division by zero.
 *
 * Return-code convention (comparison operators):
 * - `0` — FALSE.
 * - `1` — TRUE.
 *
 * Return-code convention (converters / other):
 * - `0` — OK.
 * - `1` — calculation / conversion error.
 *
 * Reference: .NET `System.Decimal` documentation.
 */

#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include "./s21_util/s21_util.h"

/** @name Arithmetic operators
 *  Each writes its result into `*result` and returns the overflow/zero-div
 *  status code described in the file header.
 *  @{
 */

/** @brief Addition: `*result = value_1 + value_2`. */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/** @brief Subtraction: `*result = value_1 - value_2`. */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/** @brief Multiplication: `*result = value_1 * value_2`. Result is
 *         bank-rounded if it overflows the 96-bit mantissa. */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/** @brief Division: `*result = value_1 / value_2`. Returns code `3` if
 *         `value_2 == 0`. */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/** @brief Modulo: `*result = value_1 mod value_2`. If overflow occurs,
 *         the fractional part is discarded. */
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/** @} */

/** @name Comparison operators
 *  Each returns `1` for TRUE, `0` for FALSE.
 *  @{
 */

/** @brief `value1 < value2`. */
int s21_is_less(s21_decimal value1, s21_decimal value2);

/** @brief `value1 ≤ value2`. */
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);

/** @brief `value1 > value2`. */
int s21_is_greater(s21_decimal value1, s21_decimal value2);

/** @brief `value1 ≥ value2`. */
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);

/** @brief `value1 == value2`. */
int s21_is_equal(s21_decimal value1, s21_decimal value2);

/** @brief `value1 != value2`. */
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);

/** @} */

/** @name Converters and parsers
 *  @{
 */

/** @brief Convert `int` → `s21_decimal`. Always succeeds (returns `0`). */
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/** @brief Convert `float` → `s21_decimal`. Returns `1` if `|src|` is out
 *         of range or `0 < |src| < 1e-28`. Rounds to ≤ 7 significant digits. */
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/** @brief Convert `s21_decimal` → `int`. Fractional part discarded (toward 0). */
int s21_from_decimal_to_int(s21_decimal src, int *dst);

/** @brief Convert `s21_decimal` → `float`. May lose precision. */
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/** @} */

/** @name Other functions
 *  Each writes its result into `*result` and returns `0` on success.
 *  @{
 */

/** @brief Round down to the nearest integer (toward `-INF`). */
int s21_floor(s21_decimal value, s21_decimal *result);

/** @brief Round to the nearest integer (banker's rounding). */
int s21_round(s21_decimal value, s21_decimal *result);

/** @brief Drop fractional part (toward zero, preserving trailing zeros). */
int s21_truncate(s21_decimal value, s21_decimal *result);

/** @brief Multiply by −1 (sign flip). */
int s21_negate(s21_decimal value, s21_decimal *result);

/** @} */

#endif  //  SRC_S21_DECIMAL_H_

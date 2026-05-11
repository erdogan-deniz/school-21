/**
 * @file s21_validation.h
 * @brief Pre-parse expression validator — rejects malformed input
 *        before the shunting-yard parser sees it.
 *
 * The validator is organised by failure mode rather than by token
 * type: each function spots one class of error (empty brackets,
 * glued values, double symbols, etc.) and returns @ref OK or
 * @ref ERROR. `s21_validation` is the umbrella entry point.
 */

#ifndef SRC_VALIDATION_S21_VALIDATION_H_
#define SRC_VALIDATION_S21_VALIDATION_H_

#define INPUT_MAX_LENGTH 255  ///< Maximum supported expression length.

#define OK 1     ///< Validation success.
#define ERROR 0  ///< Validation failure.

#include "../additional/s21_additional.h"
#include "../s21_calculator.h"

/** @brief Main entry — run every per-class check on @p string. */
int s21_validation(char *string);

// Function validations:
/** @brief `acos` / `asin` / `atan` argument range check. */
int s21_acos_asin_atan_validation(char *string);
/** @brief `cos` argument check. */
int s21_cos_validation(char *string);
/** @brief `ln` / `log` argument positivity check. */
int s21_ln_log_validation(char *string);
/** @brief `sin` / `sqrt` argument check. */
int s21_sin_sqrt_validation(char *string);
/** @brief `tan` argument check (no `π/2 + kπ`). */
int s21_tan_validation(char *string);

// Other validations:
/** @brief Detects `+*`, `*/` and other illegal binary-op sequences. */
int s21_binary_operator_validation(char *string);
/** @brief Detects numeric literals with two decimal points. */
int s21_double_number_validation(char *string);
/** @brief Detects `==`, `++`, etc. — doubled non-numeric symbols. */
int s21_double_symbol_validation(char *string);
/** @brief Detects `()` — empty bracket pairs. */
int s21_empty_brackets_validation(char *string);
/** @brief Detects two glued numeric literals without an operator. */
int s21_glued_values_validation(char *string);
/** @brief Verifies every `(` has a matching `)`. */
int s21_is_equality_brackets(char *string);
/** @brief Catch-all: only contains characters the parser accepts. */
int s21_is_valid_string(char *string);
/** @brief `mod` operator placement check. */
int s21_mod_validation(char *string);
/** @brief Numeric-literal sanity check (sign, digits, point). */
int s21_number_validation(char *string);
/** @brief Unary `+` / `-` placement (only after `(` or another op). */
int s21_unary_operator_validation(char *string);

#endif  // SRC_VALIDATION_S21_VALIDATION_H_

/**
 * @file s21_additional.h
 * @brief Small utilities shared by the parser, stack/list containers,
 *        and validation routines.
 *
 * Three groups:
 *  - **Transform**: char/string ↔ numeric conversions used by the
 *    parser to build token values.
 *  - **Stack/list helpers**: priority lookup, unary-token detection,
 *    value getters / setters on list nodes.
 *  - **Validation**: predicate helpers (`is_int`, `is_sign`,
 *    `have_x`, …) reused by the validator's per-class checks.
 */

#ifndef SRC_ADDITIONAL_S21_ADDITIONAL_H_
#define SRC_ADDITIONAL_S21_ADDITIONAL_H_

#include "../list/s21_list.h"

#define empty 0

// Status:
#define OK 1     ///< Generic success code.
#define ERROR 0  ///< Generic failure code.

// Transform types:
/** @brief Convert a digit character `'0'..'9'` to its integer value. */
int s21_char_to_int(char digit);
/** @brief Allocate a 2-byte string `{symbol, '\0'}`. Caller frees. */
char* s21_char_to_string(char symbol);  // free() result
/** @brief Parse an integer from @p string (no overflow check). */
int s21_string_to_int(char* string);
/** @brief Parse a `long double` from @p string. */
long double s21_string_to_long_double(char* string);

// Functions for stack:
/** @brief Lookup the @ref s21_token_priority for the given token text. */
s21_token_priority s21_get_priority_token(char* token);
/** @brief Returns 1 iff @p token represents a unary `+` / `-`. */
int s21_is_unary_token(char* token);

// Functions for list:
/** @brief Read the cached value off a list node. */
long double s21_get_value(s21_list* list);
/** @brief Write @p value into a list node, returning it. */
s21_list* s21_set_value(s21_list* list, long double value);  // s21_free_list()

// Validation functions:
/** @brief Count `.` characters in @p string (numeric-literal check). */
int s21_count_points(char* string);
/** @brief Returns 1 iff @p string contains at least one digit. */
int s21_have_number(char* string);
/** @brief Returns 1 iff @p string contains the literal `x`. */
int s21_have_x(char* string);
/** @brief Returns 1 iff @p string is an integer (digits only). */
int s21_is_int(char* string);
/** @brief Returns 1 iff @p symbol is `+` or `-`. */
int s21_is_sign(char symbol);
/** @brief Returns 1 iff @p symbol is in the parser's accepted alphabet. */
int s21_is_valid_symbol(char symbol);

#endif  // SRC_ADDITIONAL_S21_ADDITIONAL_H_

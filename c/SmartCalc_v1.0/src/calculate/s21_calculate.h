/**
 * @file s21_calculate.h
 * @brief RPN evaluator — consumes the token list produced by the
 *        parser and folds it into a single `long double` result.
 */

#ifndef SRC_CALCULATE_S21_CALCULATE_H_
#define SRC_CALCULATE_S21_CALCULATE_H_

#define CALCULATION_ERROR 0  ///< `*status` value on domain / parse error.

#include "../additional/s21_additional.h"
#include "../list/s21_list.h"

/**
 * @brief Evaluate the RPN token list @p list.
 * @param list   Doubly-linked list of tokens (output of `s21_parser`
 *               + `s21_stack_to_list`).
 * @param status Out-param flag — set to @ref CALCULATION_ERROR on
 *               failure, left unchanged on success.
 * @return The numeric result, or `NAN` on error.
 */
long double s21_calculate(s21_list* list, int* status);

#endif  // SRC_CALCULATE_S21_CALCULATE_H_

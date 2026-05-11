/**
 * @file s21_transform.h
 * @brief Pre-parse string normalisation — strips whitespace so the
 *        validator and parser see a canonical input.
 */

#ifndef SRC_TRANSFORM_S21_TRANSFORM_H_
#define SRC_TRANSFORM_S21_TRANSFORM_H_

#include "../s21_calculator.h"

/**
 * @brief Return a new string with every space character removed.
 * @param string Source infix expression.
 * @return Heap-allocated stripped copy. Caller frees with `free`.
 */
char* s21_delete_spaces(char* string);

#endif  // SRC_TRANSFORM_S21_TRANSFORMA_H_

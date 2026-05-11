/**
 * @file s21_parser.h
 * @brief Infix → RPN parser (Dijkstra's shunting-yard).
 *
 * Returns a token stack whose top is the *last* RPN token; the
 * evaluator (`s21_calculate`) consumes it in reverse via
 * `s21_stack_to_list`.
 */

#ifndef SRC_PARSER_S21_PARSER_H_
#define SRC_PARSER_S21_PARSER_H_

#include "../additional/s21_additional.h"
#include "../stack/s21_stack.h"

/**
 * @brief Parse @p string and emit the RPN token stream as a stack.
 * @param string Null-terminated infix expression (already validated
 *               and stripped of whitespace).
 * @return Owning pointer to the RPN token stack. Caller frees with
 *         `s21_pop_stack` (drains node by node).
 */
s21_stack* s21_parser(char* string);

#endif  // SRC_PARSER_S21_PARSER_H_

/**
 * @file s21_stack.h
 * @brief Singly-linked token stack used by the shunting-yard parser.
 *
 * Each node owns a heap-allocated `token` string plus a priority
 * level (see @ref s21_token_priority). The stack is LIFO: `push`
 * prepends a new top, `pop` removes the top and returns the new
 * top.
 */

#ifndef SRC_STACK_S21_STACK_H_
#define SRC_STACK_S21_STACK_H_

#include "../s21_calculator.h"

/**
 * @brief Shunting-yard operator priorities (low → high).
 *
 * Higher value = binds tighter. `brace` is the sentinel "always stays
 * on the stack" priority; `func` is the trigonometric / log /
 * sqrt level above plain operators.
 */
typedef enum s21_token_priority {
  none,                ///< Sentinel — no priority assigned yet.
  brace,               ///< `(` — keeps lower-priority ops above it.
  number_or_x,         ///< Numeric literal / `x` placeholder.
  plus_or_minus,       ///< Binary `+`, `-`.
  unary,               ///< Unary `+`, `-`.
  mult_or_div_or_mod,  ///< `*`, `/`, `mod`.
  pows,                ///< `^` exponentiation.
  func,                ///< `sin`, `cos`, …, `sqrt`, `log`, `ln`.
} s21_token_priority;

/**
 * @brief Stack node — token, its priority, and a unary-marker flag.
 */
typedef struct s21_stack {
  int is_unary;                       ///< 1 if `+` / `-` was unary at parse time.
  char* token;                        ///< Heap-allocated token string.
  s21_token_priority token_priority;  ///< Operator priority for ordering.
  struct s21_stack* prev;             ///< Pointer to the node below in the stack.
} s21_stack;

// Main functions:
/** @brief Pop the top node, free its token, return the new top. */
s21_stack* s21_pop_stack(s21_stack* stack);
/** @brief Push a new node on top with @p token (copies the string). */
s21_stack* s21_push_stack(s21_stack* stack, char* token);

// Support functions:
/** @brief Zero out a node's fields without freeing it. */
s21_stack* s21_clear_node_stack(s21_stack* stack);
/** @brief Allocate a node, returning it linked above @p stack. */
s21_stack* s21_create_node_stack(s21_stack* stack);
/** @brief Allocate a fresh empty stack (head sentinel). */
s21_stack* s21_create_stack(s21_stack* stack);
/** @brief Copy @p token into the top node and set its priority. */
s21_stack* s21_fill_node_stack(s21_stack* stack, char* token);
/** @brief Lookup the priority of the top node. */
s21_token_priority s21_get_node_priority(s21_stack* stack);

#endif  // SRC_STACK_S21_STACK_H_

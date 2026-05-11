/**
 * @file s21_list.h
 * @brief Doubly-linked token list — RPN representation consumed by
 *        the calculator after the stack is reversed.
 *
 * The list mirrors @ref s21_stack but adds an evaluated `value`
 * cache per node — the evaluator folds numeric operands as it walks
 * the list, replacing a triple (left, op, right) with a single
 * value-bearing node.
 */

#ifndef SRC_LIST_S21_LIST_H_
#define SRC_LIST_S21_LIST_H_

#define NEXT 1   ///< Sentinel for forward iteration helpers.
#define PREV -1  ///< Sentinel for backward iteration helpers.

#define empty 0

#include "../stack/s21_stack.h"

/**
 * @brief Doubly-linked list node — RPN token plus its numeric value
 *        (filled during evaluation).
 */
typedef struct s21_list {
  char token[255];          ///< Fixed-capacity token buffer.
  long double value;        ///< Evaluated value (numeric tokens / partial folds).
  struct s21_list* next;    ///< Successor node, NULL at the tail.
  struct s21_list* prev;    ///< Predecessor node, NULL at the head.
} s21_list;

// Main functions:
/** @brief Free the entire list. Returns NULL. */
s21_list* s21_free_list(s21_list* list);
/** @brief Free one node and unlink it; returns the surviving neighbour. */
s21_list* s21_free_node_list(s21_list* list);
/** @brief Remove the head node, return the new head. */
s21_list* s21_pop_list(s21_list* list);
/** @brief Append @p token at the tail. */
s21_list* s21_push_list(s21_list* list, char* token);

// Support functions:
/** @brief Zero-fill the node fields, no free. */
s21_list* s21_clear_node_list(s21_list* list);
/** @brief Allocate a fresh empty list (head sentinel). */
s21_list* s21_create_list(s21_list* list);
/** @brief Allocate a node and link it as the new tail of @p list. */
s21_list* s21_create_node_list(s21_list* list);
/** @brief Copy @p token into the tail node. */
s21_list* s21_fill_node_list(s21_list* list, char* token);
/** @brief Substitute every `x` token with the value at @p x. */
s21_list* s21_put_x_value(s21_list* list, long double* x);
/** @brief Number of nodes in the list. */
int s21_size_list(s21_list* list);
/** @brief Drain @p stack into a fresh list — reverses LIFO into FIFO. */
s21_list* s21_stack_to_list(s21_stack* stack);

#endif  // SRC_LIST_S21_LIST_H_

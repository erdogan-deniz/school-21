#ifndef SRC_STACK_S21_STACK_H_
#define SRC_STACK_S21_STACK_H_

#include "../s21_calculator.h"

typedef enum s21_token_priority {
  none,
  brace,
  number_or_x,
  plus_or_minus,
  unary,
  mult_or_div_or_mod,
  pows,
  func,
} s21_token_priority;

typedef struct s21_stack {
  int is_unary;
  char* token;
  s21_token_priority token_priority;
  struct s21_stack* prev;
} s21_stack;

// Main functions:
s21_stack* s21_free_stack(s21_stack* stack);
s21_stack* s21_pop_stack(s21_stack* stack);
s21_stack* s21_push_stack(s21_stack* stack, char* token);

// Support functions:
s21_stack* s21_clear_node_stack(s21_stack* stack);
s21_stack* s21_create_node_stack(s21_stack* stack);
s21_stack* s21_create_stack(s21_stack* stack);
s21_stack* s21_fill_node_stack(s21_stack* stack, char* token);
s21_token_priority s21_get_node_priority(s21_stack* stack);

#endif  // SRC_STACK_S21_STACK_H_
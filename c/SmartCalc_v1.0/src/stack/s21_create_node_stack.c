#include "s21_stack.h"

s21_stack *s21_create_node_stack(s21_stack *stack) {
  if (stack) {
    s21_stack *prev = stack;

    stack = (s21_stack *)malloc(sizeof(s21_stack));
    stack->is_unary = false;
    stack->token = (char *)calloc(255, sizeof(char));
    stack->token_priority = none;
    stack->prev = prev;
  }

  return stack;
}

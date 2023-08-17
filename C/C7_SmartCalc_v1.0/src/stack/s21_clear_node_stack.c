#include "s21_stack.h"

s21_stack *s21_clear_node_stack(s21_stack *stack) {
  if (stack) {
    stack->token_priority = none;
    stack->is_unary = false;
    stack->prev = NULL;
    memset(stack->token, '\0', 255);
  }

  return stack;
}

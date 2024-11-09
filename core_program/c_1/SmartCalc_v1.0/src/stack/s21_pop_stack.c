#include "s21_stack.h"

s21_stack *s21_pop_stack(s21_stack *stack) {
  if (stack) {
    if (stack->prev) {
      s21_stack *prev = stack->prev;

      stack = s21_clear_node_stack(stack);
      free(stack->token);
      free(stack);
      stack = prev;
    } else {
      stack = s21_clear_node_stack(stack);
      free(stack->token);
      free(stack);
      stack = NULL;
    }
  }

  return stack;
}

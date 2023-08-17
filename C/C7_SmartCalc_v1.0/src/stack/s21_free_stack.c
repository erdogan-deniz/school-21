#include "s21_stack.h"

s21_stack *s21_free_stack(s21_stack *stack) {
  if (stack) {
    s21_stack *prev = NULL;

    if (stack)
      while (stack) {
        prev = stack->prev;
        stack = s21_pop_stack(stack);
        stack = prev;
      }
  }

  return stack;
}
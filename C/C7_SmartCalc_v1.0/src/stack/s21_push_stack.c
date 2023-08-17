#include "s21_stack.h"

s21_stack *s21_push_stack(s21_stack *stack, char *token) {
  if (token) {
    if (stack) {
      stack = s21_create_node_stack(stack);
    } else {
      stack = s21_create_stack(stack);
    }

    stack = s21_fill_node_stack(stack, token);
  }

  return stack;
}
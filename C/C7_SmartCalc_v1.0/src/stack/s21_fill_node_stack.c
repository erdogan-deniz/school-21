#include "../additional/s21_additional.h"
#include "s21_stack.h"

s21_stack *s21_fill_node_stack(s21_stack *stack, char *token) {
  if (stack && token) {
    stack->token_priority = s21_get_priority_token(token);
    stack->is_unary = s21_is_unary_token(token);
    strcpy(stack->token, token);
  }

  return stack;
}
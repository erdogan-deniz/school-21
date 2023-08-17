#include "s21_stack.h"

s21_token_priority s21_get_node_priority(s21_stack *stack) {
  return stack ? stack->token_priority : none;
}
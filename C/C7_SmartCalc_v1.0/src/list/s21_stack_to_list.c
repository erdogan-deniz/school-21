#include "s21_list.h"

s21_list* s21_stack_to_list(s21_stack* stack) {
  s21_list* list = NULL;

  if (stack)
    while (stack) {
      list = s21_push_list(list, stack->token);
      stack = s21_pop_stack(stack);
    }

  return list;
}
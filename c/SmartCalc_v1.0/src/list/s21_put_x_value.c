#include "../additional/s21_additional.h"
#include "s21_list.h"

s21_list* s21_put_x_value(s21_list* list, long double* x) {
  if (list && x) {
    while (list->next) list = list->next;

    while (list->prev) {
      if (list->token[0] == 'x') list = s21_set_value(list, *x);

      list = list->prev;
    }

    if (list->token[0] == 'x') list = s21_set_value(list, *x);
  }

  return list;
}
#include "s21_additional.h"

s21_list* s21_set_value(s21_list* list, long double value) {
  if (list) {
    list->value = value;
    memset(list->token, '\0', 255);
  }

  return list;
}
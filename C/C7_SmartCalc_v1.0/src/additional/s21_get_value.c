#include "s21_additional.h"

long double s21_get_value(s21_list* list) {
  long double value = empty;

  if (list) {
    if (list->value)
      value = list->value;
    else
      value = s21_string_to_long_double(list->token);
  }

  return value;
}

#include "s21_list.h"

s21_list* s21_free_list(s21_list* list) {
  if (list)
    while (list) list = s21_pop_list(list);

  return list;
}
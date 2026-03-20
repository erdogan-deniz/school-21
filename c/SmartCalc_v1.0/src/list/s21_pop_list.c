#include "s21_list.h"

s21_list* s21_pop_list(s21_list* list) {
  if (list) {
    s21_list* pointer = NULL;

    if (list->prev || list->next) {
      while (list->prev) list = list->prev;

      pointer = list->next;
      pointer->prev = NULL;
    }

    list = s21_clear_node_list(list);
    free(list);
    list = pointer;
  }

  return list;
}
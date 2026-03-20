#include "s21_list.h"

s21_list* s21_clear_node_list(s21_list* list) {
  if (list) {
    list->value = 0;
    list->prev = NULL;
    list->next = NULL;
    memset(list->token, '\0', 255);
  }

  return list;
}

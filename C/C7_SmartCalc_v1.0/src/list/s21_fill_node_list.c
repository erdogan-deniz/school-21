#include "s21_list.h"

s21_list* s21_fill_node_list(s21_list* list, char* token) {
  if (list) {
    strcpy(list->token, token);
    list->value = empty;
  }

  return list;
}
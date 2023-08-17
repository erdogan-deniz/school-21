#include "s21_list.h"

s21_list* s21_push_list(s21_list* list, char* token) {
  if (list) {
    list = s21_create_node_list(list);
    list = s21_fill_node_list(list, token);
  } else {
    list = s21_create_list(list);
    list = s21_fill_node_list(list, token);
  }

  return list;
}
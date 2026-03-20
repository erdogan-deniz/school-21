#include "s21_list.h"

s21_list* s21_create_node_list(s21_list* list) {
  if (list) {
    while (list->prev) list = list->prev;

    s21_list* prev = list;

    list = (s21_list*)malloc(sizeof(s21_list));
    prev->prev = list;
    list->next = prev;
    list->prev = NULL;
    list->value = 0;
    memset(list->token, '\0', 255);
  }

  return list;
}
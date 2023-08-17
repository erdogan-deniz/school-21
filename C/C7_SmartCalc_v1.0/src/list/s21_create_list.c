#include "s21_list.h"

s21_list* s21_create_list(s21_list* list) {
  if (!list) {
    list = (s21_list*)malloc(sizeof(s21_list));
    list->next = NULL;
    list->prev = NULL;
    list->value = 0;
    memset(list->token, '\0', 255);
  }

  return list;
}
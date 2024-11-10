#include "s21_list.h"

s21_list* s21_free_node_list(s21_list* list) {
  if (list) {
    int neighbour = empty;
    s21_list* ptr_next = list->next;
    s21_list* ptr_prev = list->prev;

    free(list);

    if (ptr_next) {
      ptr_next->prev = ptr_prev;
      neighbour = NEXT;
    }

    if (ptr_prev) {
      ptr_prev->next = ptr_next;
      neighbour = PREV;
    }

    switch (neighbour) {
      case PREV:
        list = ptr_prev;
        break;
      case NEXT:
        list = ptr_next;
        break;
      default:
        list = NULL;
    }
  }

  return list;
}
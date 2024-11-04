#include "s21_list.h"

int s21_size_list(s21_list* list) {
  int size = empty;

  if (list) {
    if (list->next)
      while (list->next) list = list->next;

    if (list->prev)
      while (list->prev) {
        ++size;
        list = list->prev;
      }

    ++size;
  }

  return size;
}

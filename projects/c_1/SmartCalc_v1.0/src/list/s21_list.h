#ifndef SRC_LIST_S21_LIST_H_
#define SRC_LIST_S21_LIST_H_

#define NEXT 1
#define PREV -1

#define empty 0

#include "../stack/s21_stack.h"

typedef struct s21_list {
  char token[255];
  long double value;
  struct s21_list* next;
  struct s21_list* prev;
} s21_list;

// Main functions:
s21_list* s21_free_list(s21_list* list);
s21_list* s21_free_node_list(s21_list* list);
s21_list* s21_pop_list(s21_list* list);
s21_list* s21_push_list(s21_list* list, char* token);

// Support functions:
s21_list* s21_clear_node_list(s21_list* list);
s21_list* s21_create_list(s21_list* list);
s21_list* s21_create_node_list(s21_list* list);
s21_list* s21_fill_node_list(s21_list* list, char* token);
s21_list* s21_put_x_value(s21_list* list, long double* x);
int s21_size_list(s21_list* list);
s21_list* s21_stack_to_list(s21_stack* stack);

#endif  // SRC_LIST_S21_LIST_H_

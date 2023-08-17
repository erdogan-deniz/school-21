#include "s21_main.h"

long double s21_calculator(char* string, long double* x) {
  s21_stack* stack = NULL;
  s21_list* list = NULL;
  long double result = empty;
  int status = s21_validation(string);

  if (status) {
    stack = s21_parser(string);
    list = s21_stack_to_list(stack);

    if (x) list = s21_put_x_value(list, x);

    result = s21_calculate(list, &status);
  }

  return status ? result : NAN;
}
#include "s21_calculate.h"

long double s21_calculate(s21_list* list, int* status) {
  long double result = empty;

  while (s21_size_list(list) > 1)
    if (!strcmp(list->token, "cos")) {
      list->prev = s21_set_value(list->prev, cos(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "sin")) {
      list->prev = s21_set_value(list->prev, sin(s21_get_value(list->prev)));

      if (list) list = s21_free_node_list(list);

    } else if (!strcmp(list->token, "tan")) {
      list->prev = s21_set_value(list->prev, tan(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "acos")) {
      list->prev = s21_set_value(list->prev, acos(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "asin")) {
      list->prev = s21_set_value(list->prev, asin(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "atan")) {
      list->prev = s21_set_value(list->prev, atan(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "sqrt")) {
      if (s21_get_value(list->prev) < 0) {
        *status = CALCULATION_ERROR;
        break;
      }

      list->prev = s21_set_value(list->prev, sqrt(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "ln")) {
      if (s21_get_value(list->prev) <= 0) {
        *status = CALCULATION_ERROR;
        break;
      }

      list->prev = s21_set_value(list->prev, log10(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "log")) {
      if (s21_get_value(list->prev) <= 0) {
        *status = CALCULATION_ERROR;
        break;
      }

      list->prev = s21_set_value(list->prev, log(s21_get_value(list->prev)));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "+")) {
      list->prev->prev =
          s21_set_value(list->prev->prev, s21_get_value(list->prev) +
                                              s21_get_value(list->prev->prev));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "-")) {
      list->prev->prev =
          s21_set_value(list->prev->prev, s21_get_value(list->prev->prev) -
                                              s21_get_value(list->prev));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "*")) {
      list->prev->prev =
          s21_set_value(list->prev->prev, s21_get_value(list->prev->prev) *
                                              s21_get_value(list->prev));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "/")) {
      if (s21_get_value(list->prev) == 0) {
        *status = CALCULATION_ERROR;
        break;
      }

      list->prev->prev =
          s21_set_value(list->prev->prev, s21_get_value(list->prev->prev) /
                                              s21_get_value(list->prev));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "^")) {
      list->prev->prev = s21_set_value(
          list->prev->prev,
          pow(s21_get_value(list->prev->prev), s21_get_value(list->prev)));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "mod")) {
      if (s21_get_value(list->prev) == 0) {
        *status = CALCULATION_ERROR;
        break;
      }

      list->prev->prev = s21_set_value(
          list->prev->prev,
          fmod(s21_get_value(list->prev->prev), s21_get_value(list->prev)));
      list = s21_free_node_list(list);
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "+u")) {
      list->prev = s21_set_value(list->prev, s21_get_value(list->prev));
      list = s21_free_node_list(list);
    } else if (!strcmp(list->token, "-u")) {
      list->prev = s21_set_value(list->prev, -s21_get_value(list->prev));
      list = s21_free_node_list(list);
    } else {
      if (list->next) list = list->next;
    }

  if (list) {
    result = s21_get_value(list);
    list = s21_free_list(list);
  }

  return result;
}
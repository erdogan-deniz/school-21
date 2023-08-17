#include "s21_validation.h"

int s21_unary_operator_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (string[i] == '+' || string[i] == '-') {
        if (strlen(string) - i - 1 > 0) {
          if (string[i + 1] == 'm' || string[i + 1] == ')') status = ERROR;
        } else {
          status = ERROR;
        }
      }

  return status;
}
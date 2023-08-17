#include "s21_validation.h"

int s21_empty_brackets_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string) - 1; ++i)
      if (string[i] == '(' && string[i + 1] == ')') {
        status = ERROR;
        break;
      }

  return status;
}
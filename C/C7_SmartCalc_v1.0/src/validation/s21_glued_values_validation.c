#include "s21_validation.h"

int s21_glued_values_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string) - 1; ++i)
      if (isdigit(string[i]) || string[i] == 'x' || string[i] == ')') {
        if (string[i + 1] == 'x' || string[i + 1] == '(' ||
            (isalpha(string[i + 1]) && string[i + 1] != 'm')) {
          status = ERROR;
          break;
        } else if (string[i] == 'x' || string[i] == ')')
          if (isdigit(string[i + 1]) || string[i + 1] == 'x' ||
              string[i + 1] == '(' ||
              (isalpha(string[i + 1]) && string[i + 1] != 'm')) {
            status = ERROR;
            break;
          }
      }

  return status;
}
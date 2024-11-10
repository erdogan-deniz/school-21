#include "s21_validation.h"

int s21_double_number_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (isdigit(string[i])) {
        int spaces = empty;

        while (i < strlen(string) && (isdigit(string[i]) || string[i] == '.'))
          ++i;

        while (i < strlen(string) && string[i] == ' ') {
          ++spaces;
          ++i;
        }

        if (spaces && isdigit(string[i])) status = ERROR;
      }

  return status;
}
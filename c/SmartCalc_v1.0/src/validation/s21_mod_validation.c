#include "s21_validation.h"

int s21_mod_validation(char *string) {
  int status = OK;

  if (string) {
    for (size_t i = 0; i + 2 < strlen(string); ++i)
      if (string[i] == 'm')
        if ((string[i + 1] != 'o') || (string[i + 2] != 'd') ||
            ((strlen(string) - i) < 3) || i == 0) {
          status = ERROR;
          break;
        }
  }

  return status;
}
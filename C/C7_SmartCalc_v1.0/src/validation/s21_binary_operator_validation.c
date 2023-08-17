#include "s21_validation.h"

int s21_binary_operator_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if ((s21_is_sign(string[i]) || string[i] == 'm') && string[i] != '+' &&
          string[i] != '-') {
        if (i > 0) {
          if (string[i] == 'm' &&
              (!(string[i - 1] == ')' || string[i - 1] == 'x' ||
                 isdigit(string[i - 1])) ||
               !(string[i + 3] == '(' || string[i + 3] == 'x' ||
                 isdigit(string[i + 3]) || isalpha(string[i + 1])))) {
            status = ERROR;
          } else if (!(string[i - 1] == ')' || string[i - 1] == 'x' ||
                       isdigit(string[i - 1])) ||
                     !(string[i + 1] == '(' || string[i + 1] == 'x' ||
                       isdigit(string[i + 1]) || isalpha(string[i + 1]))) {
            status = ERROR;
          }
        } else {
          status = ERROR;
        }
      }

  return status;
}
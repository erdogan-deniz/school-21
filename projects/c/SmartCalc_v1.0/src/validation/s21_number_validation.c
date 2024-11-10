#include "s21_validation.h"

int s21_number_validation(char *string) {
  int status = OK;

  if (string) {
    char number[20] = {0};

    for (size_t i = 0; i < strlen(string); ++i)
      if (isdigit(string[i]) || string[i] == '.') {
        while ((i < strlen(string)) &&
               (isdigit(string[i]) || string[i] == '.')) {
          char *symbol = s21_char_to_string(string[i]);

          strcat(number, symbol);
          free(symbol);
          ++i;
        }

        if (!(s21_have_number(number) && (s21_count_points(number) < 2) &&
              (number[0] != '.') && (number[strlen(number) - 1] != '.'))) {
          status = ERROR;
          break;
        }

        memset(number, '\0', 20);
      }
  }

  return status;
}
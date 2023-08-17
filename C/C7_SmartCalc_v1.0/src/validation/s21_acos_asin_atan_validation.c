#include "s21_validation.h"

int s21_acos_asin_atan_validation(char *string) {
  int status = OK;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (string[i] == 'a')
        if (i > 0 && string[i - 1] != 't') {
          char function[255] = {0};

          while (i < strlen(string)) {
            char *symbol = s21_char_to_string(string[i]);

            strcat(function, symbol);
            free(symbol);
            ++i;

            if (string[i - 1] == '(') break;
          }

          if ((i > 254) ||
              (strcmp(function, "acos(") && strcmp(function, "asin(") &&
               strcmp(function, "atan("))) {
            status = ERROR;
            break;
          }
        }

  return status;
}
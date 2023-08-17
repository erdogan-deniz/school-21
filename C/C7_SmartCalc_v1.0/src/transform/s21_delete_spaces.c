#include "../additional/s21_additional.h"
#include "s21_transform.h"

char* s21_delete_spaces(char* string) {
  char* result = NULL;

  if (string) {
    char* new_string = (char*)calloc(255, sizeof(char));

    for (size_t i = 0; i < strlen(string); ++i) {
      if (string[i] != ' ') {
        char* symbol = s21_char_to_string(string[i]);

        strcat(new_string, symbol);
        free(symbol);
      }
    }

    if (strlen(new_string))
      result = new_string;
    else
      free(new_string);
  }

  return result;
}
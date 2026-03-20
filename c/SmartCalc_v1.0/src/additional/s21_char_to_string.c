#include "s21_additional.h"

char* s21_char_to_string(char symbol) {
  char* string = NULL;

  if (symbol) {
    string = (char*)calloc(2, sizeof(char));
    string[0] = symbol;
    string[1] = '\0';
  }

  return string;
}
#include "s21_additional.h"

int s21_char_to_int(char symbol) {
  int integer = empty;

  if (symbol) {
    if (symbol == '1')
      integer = 1;
    else if (symbol == '2')
      integer = 2;
    else if (symbol == '3')
      integer = 3;
    else if (symbol == '4')
      integer = 4;
    else if (symbol == '5')
      integer = 5;
    else if (symbol == '6')
      integer = 6;
    else if (symbol == '7')
      integer = 7;
    else if (symbol == '8')
      integer = 8;
    else if (symbol == '9')
      integer = 9;
  }

  return integer;
}
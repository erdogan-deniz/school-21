#include "s21_additional.h"

int s21_is_valid_symbol(char symbol) {
  int answer = false;

  if (symbol)
    if ((symbol > 39 && symbol < 44) || (symbol > 44 && symbol < 58) ||
        symbol == 94 || symbol == 97 || (symbol > 98 && symbol < 101) ||
        symbol == 103 || symbol == 105 || (symbol > 107 && symbol < 112) ||
        (symbol > 112 && symbol < 117) || symbol == 120)
      answer = true;

  return answer;
}
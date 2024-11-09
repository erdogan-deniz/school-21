#include "s21_additional.h"

int s21_is_sign(char symbol) {
  int answer = false;

  if (symbol)
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
        symbol == '^')
      answer = true;

  return answer;
}
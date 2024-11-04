#include "s21_additional.h"

int s21_is_unary_token(char* token) {
  int answer = false;

  if (token && (strlen(token) == 2))
    if ((token[0] == '+' || token[0] == '-') && token[1] == 'u') answer = true;

  return answer;
}
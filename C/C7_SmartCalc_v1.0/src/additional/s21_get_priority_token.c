#include "s21_additional.h"

s21_token_priority s21_get_priority_token(char *token) {
  s21_token_priority priority = none;

  if (token) {
    if (!strcmp("cos", token) || !strcmp("sin", token) ||
        !strcmp("tan", token) || !strcmp("acos", token) ||
        !strcmp("asin", token) || !strcmp("atan", token) ||
        !strcmp("sqrt", token) || !strcmp("ln", token) || !strcmp("log", token))
      priority = func;
    else if (!strcmp("^", token))
      priority = pows;
    else if (!strcmp("*", token) || !strcmp("/", token) || !strcmp("m", token))
      priority = mult_or_div_or_mod;
    else if (!strcmp("-u", token) || !strcmp("+u", token))
      priority = unary;
    else if (!strcmp("-", token) || !strcmp("+", token))
      priority = plus_or_minus;
    else if (isdigit(token[0]) || !strcmp("x", token))
      priority = number_or_x;
    else if (!strcmp("(", token) || !strcmp(")", token))
      priority = brace;
  }

  return priority;
}
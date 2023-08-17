#include "s21_parser.h"

s21_stack* s21_parser(char* string) {
  s21_stack* stack = NULL;
  s21_stack* final_stack = NULL;

  if (string) {
    for (size_t i = 0; (i < strlen(string)) && string[i] != '\0'; ++i) {
      if (string[i] == 'x') {  // X
        final_stack = s21_push_stack(final_stack, "x");
        continue;
      }

      if (isdigit(string[i])) {  // Digits
        char* number = (char*)calloc(64, sizeof(char));

        while (isdigit(string[i]) || string[i] == '.') {
          char* symbol = s21_char_to_string(string[i]);

          strcat(number, symbol);
          free(symbol);
          ++i;
        }

        --i;
        final_stack = s21_push_stack(final_stack, number);
        free(number);
        continue;
      }

      if ((isalpha(string[i]) && string[i] != 'm') ||
          (string[i] == '(')) {  // Functions and brackets
        if (string[i] == '(') {
          stack = s21_push_stack(stack, "(");
        } else {
          char* function = (char*)calloc(10, sizeof(char));

          while (isalpha(string[i])) {
            char* symbol = s21_char_to_string(string[i]);

            strcat(function, symbol);
            free(symbol);
            ++i;
          }

          --i;
          stack = s21_push_stack(stack, function);
          free(function);
        }

        continue;
      }

      if (s21_is_sign(string[i]) || string[i] == 'm') {  // Operators
        if (string[i] == '-' || string[i] == '+')
          if (i == 0 || (i != 0 && (string[i - 1] == '(' ||
                                    s21_is_sign(string[i - 1])))) {
            if (string[i] == '+') {
              stack = s21_push_stack(stack, "+u");
            } else {
              stack = s21_push_stack(stack, "-u");
            }

            continue;
          }

        while (stack) {
          char* symbol = s21_char_to_string(string[i]);

          while (s21_get_node_priority(stack) >=
                 s21_get_priority_token(symbol)) {
            final_stack = s21_push_stack(final_stack, stack->token);
            stack = s21_pop_stack(stack);
            break;
          }

          if (s21_get_node_priority(stack) < s21_get_priority_token(symbol)) {
            free(symbol);
            break;
          } else {
            free(symbol);
          }
        }

        if (string[i] == 'm') {
          stack = s21_push_stack(stack, "mod");
          i += 2;
        } else {
          char* operator= operator= s21_char_to_string(string[i]);

          stack = s21_push_stack(stack, operator);
          free(operator);
        }

        continue;
      }

      if (string[i] == ')' && stack) {
        while (stack->token[0] != '(') {
          final_stack = s21_push_stack(final_stack, stack->token);
          stack = s21_pop_stack(stack);
        }

        stack = s21_pop_stack(stack);

        while (stack && (stack->token_priority == func)) {
          final_stack = s21_push_stack(final_stack, stack->token);
          stack = s21_pop_stack(stack);
        }
      }
    }

    while (stack) {
      final_stack = s21_push_stack(final_stack, stack->token);
      stack = s21_pop_stack(stack);
    }
  }

  return final_stack;
}
#include "s21_validation.h"

#include "../transform/s21_transform.h"

int s21_validation(char *string) {
  int status = OK;

  if (string) {
    char *new_string = s21_delete_spaces(string);

    status = s21_double_number_validation(string);

    if (status &&
        (!new_string || (strlen(new_string) > INPUT_MAX_LENGTH) ||
         !s21_acos_asin_atan_validation(new_string) ||
         !s21_cos_validation(new_string) ||
         !s21_ln_log_validation(new_string) ||
         !s21_sin_sqrt_validation(new_string) ||
         !s21_tan_validation(new_string) ||
         !s21_double_symbol_validation(new_string) ||
         !s21_glued_values_validation(new_string) ||
         !s21_empty_brackets_validation(new_string) ||
         !s21_is_equality_brackets(new_string) ||
         !s21_is_valid_string(new_string) || !s21_mod_validation(new_string) ||
         !s21_number_validation(new_string) ||
         !s21_binary_operator_validation(new_string) ||
         !s21_unary_operator_validation(new_string)))
      status = ERROR;

    free(new_string);
  }

  return status;
}
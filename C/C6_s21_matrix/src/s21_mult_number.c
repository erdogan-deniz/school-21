#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int exit_code = OK;

  if (s21_is_matrix_exists(A) && result) {
    exit_code = s21_create_matrix(A->rows, A->columns, result);
    if (exit_code != CALLOC_ERROR) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}
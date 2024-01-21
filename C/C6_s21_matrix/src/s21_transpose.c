#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int exit_code = OK;

  if (s21_is_matrix_exists(A) && result) {
    exit_code = s21_create_matrix(A->columns, A->rows, result);

    if (!exit_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}
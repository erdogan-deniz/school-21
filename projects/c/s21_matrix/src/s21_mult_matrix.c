#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = OK;

  if (s21_is_matrix_exists(A) && s21_is_matrix_exists(B) && result) {
    if (A->columns == B->rows) {
      exit_code = s21_create_matrix(A->rows, B->columns, result);
      if (!exit_code) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int m = 0; m < B->rows; m++) {
              result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
            }
          }
        }
      }
    } else {
      exit_code = CALC_ERROR;
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}
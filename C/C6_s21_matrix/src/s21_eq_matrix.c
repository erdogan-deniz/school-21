#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int exit_code = SUCCESS;

  if (!s21_is_matrix_exists(A) || !s21_is_matrix_exists(B) ||
      ((A->rows != B->rows) || (A->columns != B->columns))) {
    exit_code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) exit_code = FAILURE;
      }
    }
  }

  return exit_code;
}
#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int exit_code = OK;

  if (s21_is_matrix_exists(A) && result) {
    if (A->rows == A->columns) {
      double determinant = 0.0;
      s21_determinant(A, &determinant);

      if (fabs(determinant - 0.0) > EPS) {
        if (A->rows == 1) {
          s21_create_matrix(1, 1, result);
          result->matrix[0][0] = 1 / A->matrix[0][0];
        } else {
          matrix_t A_calc = {0};
          s21_calc_complements(A, &A_calc);

          matrix_t A_transpose = {0};
          s21_transpose(&A_calc, &A_transpose);

          s21_mult_number(&A_transpose, 1.0 / determinant, result);

          s21_remove_matrix(&A_calc);
          s21_remove_matrix(&A_transpose);
        }
      } else {
        exit_code = CALC_ERROR;
      }
    } else {
      exit_code = CALC_ERROR;
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}
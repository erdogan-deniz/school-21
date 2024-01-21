#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    if (A->matrix) {
      free(A->matrix);
      A->matrix = NULL;
    }

    A->rows = 0;
    A->columns = 0;
  }
}
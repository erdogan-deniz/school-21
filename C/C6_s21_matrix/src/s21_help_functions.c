#include "s21_matrix.h"

bool s21_is_matrix_exists(matrix_t *A) {
  return (A && A->rows > 0 && A->columns > 0 && A->matrix);
}

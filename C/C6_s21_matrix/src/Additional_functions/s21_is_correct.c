#include "../s21_matrix.h"

int s21_is_correct(matrix_t *A) {
    return (A && A->rows > 0 && A->columns > 0 && A->matrix) ? SUCCESS : FAILURE;
}

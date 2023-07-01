#include "../s21_matrix.h"

int s21_is_empty(matrix_t *A) {
    int key = SUCCESS;

    if (A->rows > 0 || A->columns > 0 || A->matrix)
        key = FAILURE;

    return key? SUCCESS: FAILURE;
}
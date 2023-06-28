#include "s21_additional_functions.h"

int s21_is_empty(matrix_t *A) {
    int key = 1;

    if (A->rows != 0 || A->columns != 0 || A->matrix != NULL)
        key = 0;

    return key? SUCCESS: FAILURE;
}
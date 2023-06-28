#include "s21_additional_functions.h"

int s21_is_correct(matrix_t *A) {
    return (A->rows > 0 && A->columns > 0 && A->matrix != NULL)? SUCCESS: FAILURE;
}
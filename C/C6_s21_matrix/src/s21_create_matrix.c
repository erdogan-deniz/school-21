#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {

    int status = OK;

    if (!s21_is_empty(result))
        status = CALCULATION_ERROR;
    
    if (!status)
        if (rows < 1 || columns < 1)
            status = INCORRECT_MATRIX;
    
    if (!status) {
            result->rows = rows;
            result->columns = columns;
            result->matrix = (double**)calloc(rows, sizeof(double*));
    }

    if (!status && result->matrix) {
        for (int i = 0; i < rows; ++i) {
            result->matrix[i] = (double*)calloc(columns, sizeof(double));

            if (!result->matrix[i]) {
                s21_remove_matrix(result);
                
                break;
            }
        }
    }

    return status;
}
#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int status = OK;
    
    if (!s21_is_correct(A) || !s21_is_empty(result))
        status = INCORRECT_MATRIX;
    
    if (!status)
        if (A->rows != A->columns)
            status = CALCULATION_ERROR;

    if (!status) {
        s21_create_matrix(A->rows, A->columns, result);
                
        for (int i = 0; i < A->rows; ++i)
            for (int j = 0; j < A->columns; ++j) {
                double determinant = 0.0;
                matrix_t downgrade_matrix = {0};
                    
                s21_create_matrix(A->rows - 1, A->columns - 1, &downgrade_matrix);
                s21_downgrade(i, j, A, &downgrade_matrix);
                s21_determinant(&downgrade_matrix, &determinant);

                result->matrix[i][j] = determinant * ((i + j) % 2? -1: 1);
                
                s21_remove_matrix(&downgrade_matrix);
        }
    }

    return status;
}
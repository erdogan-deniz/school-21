#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {

    int status = OK;

    if (!s21_is_correct(A) || !result) {
        status = INCORRECT_MATRIX;
    }
    else {
        if (A->rows != A->columns)
            status = CALCULATION_ERROR;
    }
    
    if (!status) {
        if (A->rows == 1)
            *result = A->matrix[0][0];
            
        if (A->rows == 2)
            *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
            
        if (A->rows > 2) {
            double determinant = 0.0;
            double major = 0.0;
            matrix_t minor = {0};
                
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

            for (int i = 0; i < A->columns; ++i) {
                s21_downgrade(0, i, A, &minor);
                s21_determinant(&minor, &determinant);
                major += A->matrix[0][i] * determinant;
            }

            s21_remove_matrix(&minor);
            *result = major;
        }
    }

    return status; 
}
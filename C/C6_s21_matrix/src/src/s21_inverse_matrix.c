#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    
    int status = OK;
    double res = 0.0;

    s21_determinant(A, &res);
    
    if (!s21_is_correct(A) || !s21_is_empty(result)) {
        status = INCORRECT_MATRIX;
    }
    else {
        if (A->rows != A->columns || !res)
            status = CALCULATION_ERROR;
    }
    
    if (!status) {
        s21_create_matrix(A->rows, A->columns, result);
            
        if (A->rows == 1) {
            result->matrix[0][0] = 1.0 / A->matrix[0][0];
        }
        else {
            matrix_t tmp_calc = {0};
            matrix_t tmp_trans = {0};
            
            s21_calc_complements(A, &tmp_calc);
            s21_transpose(&tmp_calc, &tmp_trans);
            s21_mult_number(&tmp_trans, 1 / res, result);
            s21_remove_matrix(&tmp_calc);
            s21_remove_matrix(&tmp_trans);
        }
    }
    
    return status;
}
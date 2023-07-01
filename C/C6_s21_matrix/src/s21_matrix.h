#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#define SUCCESS 1
#define FAILURE 0

#define EPS 10e-7

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum errors {
    OK,
    INCORRECT_MATRIX,
    CALCULATION_ERROR
};

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

// INITIALIZE
int s21_create_matrix(int rows, int columns, matrix_t *result);  // № 1
void s21_remove_matrix(matrix_t *A); // № 2

// COMPARISON
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // № 3

// ARITHMETICS
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // № 4
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // № 5
int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // № 6
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // № 7

// ANOTHER
int s21_transpose(matrix_t *A, matrix_t *result);  // № 8
int s21_calc_complements(matrix_t *A, matrix_t *result);  // № 9
int s21_determinant(matrix_t *A, double *result);  // № 10
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // № 11

// HELPERS
int s21_downgrade(int n, int m, matrix_t *A, matrix_t *result);
int s21_is_correct(matrix_t *A);
int s21_is_empty(matrix_t *A);
int s21_is_equal(double A, double B);

#endif  // SRC_S21_MATRIX_H_
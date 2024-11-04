#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum matrix_comparison_code { FAILURE = 0, SUCCESS = 1 };

enum matrix_operations_code {
  OK = 0,
  MATRIX_ERROR = 1,
  CALC_ERROR = 2,
  CALLOC_ERROR = 3
};

#define EPS 1e-6

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

bool s21_is_matrix_exists(matrix_t *A);
int s21_copy_matrix(matrix_t *A, matrix_t *B);
double s21_found_determinant(matrix_t matrix, int size);
void s21_fill_determinate_matrix(double **matrix_input, double **matrix_temp,
                                 int skip_row, int skip_column, int size);
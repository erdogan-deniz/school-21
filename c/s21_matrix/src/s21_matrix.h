/**
 * @file s21_matrix.h
 * @brief Numerical matrix library — addition, multiplication, transpose,
 *        determinant, algebraic complements, inverse.
 *
 * Matrices are heap-allocated `double **` with explicit `rows` / `columns`
 * dimensions, wrapped in `matrix_t`. Every operation returns an
 * @ref matrix_operations_code status; equality returns
 * @ref matrix_comparison_code.
 *
 * Memory ownership: the caller owns every `matrix_t` it instantiates and
 * is responsible for calling @ref s21_remove_matrix once the matrix is
 * no longer needed. Functions that produce a new matrix
 * (@ref s21_calc_complements, @ref s21_inverse_matrix, @ref s21_transpose,
 * @ref s21_sum_matrix, ...) allocate `result` themselves; the caller still
 * frees it.
 *
 * Accuracy contract: element-wise comparison is exact up to `EPS = 1e-6`.
 */

#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/** @brief Matrix payload — `rows × columns` doubles. */
typedef struct matrix_struct {
  double **matrix;  ///< Row-major `double[rows][columns]`.
  int rows;         ///< Number of rows; must be ≥ 1.
  int columns;      ///< Number of columns; must be ≥ 1.
} matrix_t;

/** @brief Result codes for @ref s21_eq_matrix. */
enum matrix_comparison_code { FAILURE = 0, SUCCESS = 1 };

/** @brief Result codes for every other operation. */
enum matrix_operations_code {
  OK = 0,            ///< Success.
  MATRIX_ERROR = 1,  ///< Input matrix is malformed (NULL or zero dims).
  CALC_ERROR = 2,    ///< Dimension mismatch or other math-domain error.
  CALLOC_ERROR = 3   ///< Out of memory.
};

/** Element-wise equality threshold for @ref s21_eq_matrix. */
#define EPS 1e-6

/** @brief Allocate an `rows × columns` matrix into `*result`. */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/** @brief Free a previously created matrix (safe on already-zeroed). */
void s21_remove_matrix(matrix_t *A);

/** @brief Element-wise equality within @ref EPS. */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/** @brief Element-wise sum: `*result = A + B`. Dimensions must match. */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/** @brief Element-wise difference: `*result = A - B`. Dimensions must match. */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/** @brief Scalar multiplication: `*result = A * number`. */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/** @brief Matrix multiplication: `*result = A * B`. `A.cols` must equal `B.rows`. */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/** @brief Transpose: `*result = A^T`. */
int s21_transpose(matrix_t *A, matrix_t *result);

/** @brief Algebraic complements: `*result(i,j) = (-1)^(i+j) * M(i,j)`. A must be square. */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/** @brief Determinant of `A` into `*result`. A must be square. */
int s21_determinant(matrix_t *A, double *result);

/** @brief Inverse matrix: `*result = A^(-1)`. A must be square with `det(A) != 0`. */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/** @name Internal helpers (exposed for testing)
 *  @{
 */

/** @brief Sanity check: A is non-NULL with positive dimensions and an allocated payload. */
bool s21_is_matrix_exists(matrix_t *A);

/** @brief Deep copy: allocates and populates B with the same content as A. */
int s21_copy_matrix(matrix_t *A, matrix_t *B);

/** @brief Recursive determinant via cofactor expansion. */
double s21_found_determinant(matrix_t matrix, int size);

/** @brief Build minor matrix by deleting `skip_row` / `skip_column`. */
void s21_fill_determinate_matrix(double **matrix_input, double **matrix_temp,
                                 int skip_row, int skip_column, int size);

/** @} */

/**
 * @file s21_matrix_oop.h
 * @brief Object-oriented matrix library — C++ rewrite of `c/s21_matrix`
 *        using the OOP paradigm.
 *
 * `S21Matrix` wraps a `double **` payload with explicit `rows_` / `cols_`
 * dimensions and provides matrix algebra both as member methods
 * (`SumMatrix`, `MulMatrix`, ...) and as overloaded operators
 * (`+`, `-`, `*`, `==`, `=`, `+=`, ...).
 *
 * Memory: RAII — constructors allocate, destructor frees, copy/move
 * constructors handle ownership transfer.
 *
 * Accuracy contract: element-wise comparison is exact up to
 * `PRECISION = 1e-7`.
 *
 * Exception semantics: domain errors (e.g. dimension mismatch, singular
 * matrix in `InverseMatrix`) throw `std::exception` derivatives;
 * out-of-bounds index access in `operator()` throws.
 */

#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include "cmath"
#include "iostream"

/** Element-wise equality threshold for @ref S21Matrix::EqMatrix. */
#define PRECISION 1e-7

/** Default matrix dimension used by the no-arg constructor. */
#define SIZE 2

/** Sentinel for "uninitialised" row / column counts. */
#define EMPTY 0

/**
 * @brief Numerical matrix (`rows × cols` doubles).
 *
 * RAII-owned `double **` payload; copyable and movable.
 */
class S21Matrix {
 public:
  /** @name Additional helpers
   *  Internal-but-public utilities exposed for fine-grained tests.
   *  @{
   */
  void CopyMatrix(const S21Matrix &matrix);              ///< Deep copy of `matrix` into `*this`.
  void DeleteMatrix();                                   ///< Free the payload; resets dims to `EMPTY`.
  void DownGrade(const int n, const int m, S21Matrix &matrix) const;  ///< Build minor by deleting row n, col m.
  void FillMatrix();                                     ///< Set every cell to `EMPTY`.
  bool IsCorrectMatrix() const;                          ///< `rows_ > 0 && cols_ > 0 && matrix_ != nullptr`.
  bool IsEqualValue(const double v1, const double v2) const;  ///< `|v1 - v2| < PRECISION`.
  void PrintMatrix() const;                              ///< Pretty-print to stdout.
  /** @} */

  /** @name Core methods
   *  Match the operations described in the original School 21 task.
   *  @{
   */
  bool EqMatrix(const S21Matrix &matrix) const;          ///< Element-wise `|a-b| < PRECISION`.
  void SumMatrix(const S21Matrix &matrix);               ///< `*this += matrix` (in-place).
  void SubMatrix(const S21Matrix &matrix);               ///< `*this -= matrix` (in-place).
  void MulNumber(const double number);                   ///< `*this *= number` (in-place).
  void MulMatrix(const S21Matrix &matrix);               ///< `*this = *this * matrix` (dim check).
  S21Matrix Transpose() const;                           ///< Returns transposed copy.
  S21Matrix CalcComplements() const;                     ///< Returns algebraic-complement matrix.
  double Determinant() const;                            ///< Returns determinant (square only).
  S21Matrix InverseMatrix() const;                       ///< Returns `*this^(-1)` (square, det != 0).
  /** @} */

  /** @name Overloaded operators
   *  Mirror the core methods + indexation.
   *  @{
   */
  S21Matrix operator+(const S21Matrix &matrix) const;
  S21Matrix operator-(const S21Matrix &matrix) const;
  S21Matrix operator*(const S21Matrix &matrix) const;
  S21Matrix operator*(const double number) const;
  bool operator==(const S21Matrix &matrix) const;
  void operator=(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double number);
  double &operator()(const int i, const int j);          ///< `m(i,j)` mutable access.
  double operator()(const int i, const int j) const;     ///< `m(i,j)` const access.
  /** @} */

  /** @name Accessors / mutators
   *  Dimension resize via `SetRows` / `SetColumns` pads with zeros on grow
   *  or truncates on shrink.
   *  @{
   */
  int GetRows() const;
  int GetColumns() const;
  double **GetMatrix() const;
  void SetRows(const int rows);
  void SetColumns(const int columns);
  void SetMatrix();                                      ///< Re-allocate `matrix_` for current dims.
  /** @} */

  /** @name Constructors / destructor
   *  @{
   */
  S21Matrix();                                           ///< Default — `SIZE × SIZE` zeroed.
  S21Matrix(const int rows, const int columns);          ///< Parameterised.
  S21Matrix(const S21Matrix &matrix);                    ///< Copy.
  S21Matrix(S21Matrix &&matrix);                         ///< Move.
  ~S21Matrix();
  /** @} */

 private:
  int rows_ = EMPTY, columns_ = EMPTY;
  double **matrix_ = nullptr;
};

#endif  // SRC_S21_MATRIX_OOP_H_

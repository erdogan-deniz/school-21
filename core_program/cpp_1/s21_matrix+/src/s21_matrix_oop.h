#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include "cmath"
#include "iostream"

#define PRECISION 1e-7

#define SIZE 2

#define EMPTY 0

class S21Matrix {
public:
  // ADDITIONAL:
  void CopyMatrix(const S21Matrix &matrix);
  void DeleteMatrix();
  void DownGrade(const int n, const int m, S21Matrix &matrix) const;
  void FillMatrix();
  bool IsCorrectMatrix() const;
  bool IsEqualValue(const double value_one, const double value_two) const;
  void PrintMatrix() const;

  // METHODS:
  bool EqMatrix(const S21Matrix &matrix) const;
  void SumMatrix(const S21Matrix &matrix);
  void SubMatrix(const S21Matrix &matrix);
  void MulNumber(const double number);
  void MulMatrix(const S21Matrix &matrix);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // OPERATIONS:
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
  double &operator()(const int i, const int j);
  double operator()(const int i, const int j) const;

  // PROPERTIES:
  int GetRows() const;
  int GetColumns() const;
  double **GetMatrix() const;
  void SetRows(const int rows);
  void SetColumns(const int columns);
  void SetMatrix();

  // CONSTRUCTORS:
  S21Matrix();
  S21Matrix(const int rows, const int columns);
  S21Matrix(const S21Matrix &matrix);
  S21Matrix(S21Matrix &&matrix);
  ~S21Matrix();

private:
  int rows_ = EMPTY, columns_ = EMPTY;
  double **matrix_ = nullptr;
};

#endif // SRC_S21_MATRIX_OOP_H_
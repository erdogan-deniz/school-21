#include "../s21_matrix_oop.h"

S21Matrix S21Matrix ::operator*(const S21Matrix &matrix) const {
  S21Matrix result(*this);

  result.MulMatrix(matrix);

  return result;
}

S21Matrix S21Matrix ::operator*(const double number) const {
  S21Matrix result(*this);

  result.MulNumber(number);

  return result;
}
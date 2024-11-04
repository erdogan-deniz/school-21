#include "../s21_matrix_oop.h"

S21Matrix S21Matrix ::operator-(const S21Matrix &matrix) const {
  S21Matrix result(*this);

  result.SubMatrix(matrix);

  return result;
}
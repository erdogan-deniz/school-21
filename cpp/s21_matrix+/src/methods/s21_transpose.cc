#include "../s21_matrix_oop.h"

S21Matrix S21Matrix ::Transpose() const {
  if (!IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else {
    S21Matrix matrix(GetColumns(), GetRows());

    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j)
        matrix(j, i) = (*this)(i, j);

    return matrix;
  }
}
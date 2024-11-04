#include "../s21_matrix_oop.h"

void S21Matrix ::SubMatrix(const S21Matrix &matrix) {
  if (!IsCorrectMatrix() || !matrix.IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetRows() != matrix.GetRows())
    throw std ::logic_error("NOT EQUAL ROWS MATRIX!");
  else if (GetColumns() != matrix.GetColumns())
    throw std ::logic_error("NOT EQUAL COLUMNS MATRIX!");
  else
    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j)
        (*this)(i, j) -= matrix(i, j);
}
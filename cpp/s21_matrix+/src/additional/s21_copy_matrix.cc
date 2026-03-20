#include "../s21_matrix_oop.h"

void S21Matrix ::CopyMatrix(const S21Matrix &matrix) {
  if (matrix.GetRows() <= EMPTY)
    throw std ::invalid_argument("INCORRECT MATRIX NUMBER OF ROWS!");
  else if (matrix.GetColumns() <= EMPTY)
    throw std ::invalid_argument("INCORRECT MATRIX NUMBER OF COLUMNS!");
  else if (matrix.GetMatrix() == nullptr)
    throw std ::invalid_argument("MATRIX IS EMPTY!");
  else if (GetMatrix() != nullptr)
    throw std ::invalid_argument("CURRENT MATRIX ISN'T EMPTY!");
  else {
    rows_ = matrix.GetRows();
    columns_ = matrix.GetColumns();
    SetMatrix();

    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j)
        (*this)(i, j) = matrix(i, j);
  }
}
#include "../s21_matrix_oop.h"

bool S21Matrix ::EqMatrix(const S21Matrix &matrix) const {
  bool status = true;

  if (!IsCorrectMatrix() || !matrix.IsCorrectMatrix() ||
      GetRows() != matrix.GetRows() || GetColumns() != matrix.GetColumns())
    status = false;
  else
    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j)
        if (!IsEqualValue((*this)(i, j), matrix(i, j)))
          status = false;

  return status;
}
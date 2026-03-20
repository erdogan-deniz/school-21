#include "../s21_matrix_oop.h"

void S21Matrix ::MulMatrix(const S21Matrix &matrix) {
  if (!IsCorrectMatrix() || !matrix.IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetColumns() != matrix.GetRows())
    throw std ::logic_error("COUNT OF FIRST MATRIX COLUMNS DOESN'T EQUAL "
                            "SECOND MATRIX COUNT ROWS!");
  else {
    S21Matrix matrix_two(GetRows(), matrix.GetColumns());

    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < matrix.GetColumns(); ++j)
        for (int k = 0; k < GetColumns(); ++k)
          matrix_two(i, j) += (*this)(i, k) * matrix(k, j);

    DeleteMatrix();
    CopyMatrix(matrix_two);
  }
}
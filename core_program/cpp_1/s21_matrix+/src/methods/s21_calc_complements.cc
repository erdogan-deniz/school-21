#include "../s21_matrix_oop.h"

S21Matrix S21Matrix ::CalcComplements() const {
  if (!IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetRows() != GetColumns())
    throw std ::logic_error("MATRIX ISN'T SQUARE!");
  else {
    S21Matrix matrix(GetRows(), GetColumns());

    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j) {
        double determinant = 0.0;
        S21Matrix down_grade_matrix(GetRows() - 1, GetColumns() - 1);

        DownGrade(i, j, down_grade_matrix);
        determinant = down_grade_matrix.Determinant();
        matrix(i, j) = determinant * ((i + j) % 2 ? -1 : 1);
      }

    return matrix;
  }
}
#include "../s21_matrix_oop.h"

double S21Matrix ::Determinant() const {
  if (!IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetRows() != GetColumns())
    throw std ::logic_error("IT'S NOT A SQUARE MATRIX!");
  else {
    double answer = EMPTY;

    if (GetRows() == 1)
      answer = (*this)(0, 0);
    else if (GetRows() == 2)
      answer = (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
    else if (GetRows() > 2) {
      double determinant = 0.0;
      double major = 0.0;
      S21Matrix minor(GetRows() - 1, GetColumns() - 1);

      for (int i = 0; i < GetColumns(); ++i) {
        DownGrade(0, i, minor);
        determinant = minor.Determinant();
        major += (*this)(0, i) * determinant * (i % 2 ? -1 : 1);
      }

      answer = major;
    }

    return answer;
  }
}
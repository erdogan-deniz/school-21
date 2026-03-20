#include "../s21_matrix_oop.h"

S21Matrix S21Matrix ::InverseMatrix() const {
  if (!IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetRows() != GetColumns())
    throw std ::logic_error("IT'S NOT A SQUARE MATRIX!");
  else {
    double determinant = Determinant();

    if (IsEqualValue(determinant, 0.0))
      throw std ::logic_error("DETERMINANT IS ZERO!");
    else {
      S21Matrix matrix_calc(CalcComplements());
      S21Matrix trans_matrix_calc(matrix_calc.Transpose());

      trans_matrix_calc.MulNumber(1 / determinant);

      return trans_matrix_calc;
    }
  }
}
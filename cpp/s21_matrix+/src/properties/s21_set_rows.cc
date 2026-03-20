#include "../s21_matrix_oop.h"

void S21Matrix ::SetRows(const int rows) {
  if (rows < EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF ROWS!");
  else if (rows != GetRows()) {
    if (rows == EMPTY) {
      DeleteMatrix();
    } else {
      S21Matrix matrix(*this);

      DeleteMatrix();
      rows_ = rows;
      columns_ = matrix.GetColumns();
      SetMatrix();

      for (int i = 0; (i < GetRows()) && (i < matrix.GetRows()); ++i)
        for (int j = 0; j < GetColumns(); ++j)
          (*this)(i, j) = matrix(i, j);
    }
  }
}
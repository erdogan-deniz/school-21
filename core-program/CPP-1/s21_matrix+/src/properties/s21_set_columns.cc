#include "../s21_matrix_oop.h"

void S21Matrix ::SetColumns(const int columns) {
  if (columns < EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF COLUMNS!");
  else if (columns != GetColumns()) {
    if (columns == EMPTY) {
      DeleteMatrix();
    } else {
      S21Matrix matrix(*this);

      DeleteMatrix();
      rows_ = matrix.GetRows();
      columns_ = columns;
      SetMatrix();

      for (int i = 0; i < GetRows(); ++i)
        for (int j = 0; (j < GetColumns()) && (j < matrix.GetColumns()); ++j)
          (*this)(i, j) = matrix(i, j);
    }
  }
}
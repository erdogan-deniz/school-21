#include "../s21_matrix_oop.h"

void S21Matrix ::DownGrade(const int n, const int m, S21Matrix &matrix) const {
  if (!IsCorrectMatrix())
    throw std ::invalid_argument("INCORRECT MATRIX!");
  else if (GetRows() != GetColumns())
    throw std ::invalid_argument("MATRIX ISN'T SQUARE!");
  else {
    int di = 0;
    int dj = 0;

    for (int i = 0; i < GetRows(); ++i) {
      if (i == n)
        continue;

      di = (i > n) ? 1 : 0;

      for (int j = 0; j < GetColumns(); ++j) {
        if (j == m)
          continue;

        dj = (j > m) ? 1 : 0;
        matrix(i - di, j - dj) = (*this)(i, j);
      }
    }
  }
}
#include "../s21_matrix_oop.h"

void S21Matrix ::PrintMatrix() const {
  for (int i = 0; i < GetRows(); ++i) {
    for (int j = 0; j < GetColumns(); ++j)
      std ::cout << (*this)(i, j) << " ";

    std ::cout << std ::endl;
  }
}
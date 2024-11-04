#include "../s21_matrix_oop.h"

void S21Matrix ::FillMatrix() {
  for (int i = 0; i < GetRows(); ++i) {
    for (int j = 0; j < GetColumns(); ++j) {
      (*this)(i, j) = i + j;
    }
  }
}
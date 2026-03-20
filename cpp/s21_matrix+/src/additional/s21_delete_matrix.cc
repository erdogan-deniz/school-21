#include "../s21_matrix_oop.h"

void S21Matrix ::DeleteMatrix() {
  if (GetMatrix() != nullptr) {
    for (int i = 0; i < GetRows(); ++i)
      delete[] matrix_[i];

    delete[] matrix_;
    matrix_ = nullptr;
  }

  rows_ = EMPTY;
  columns_ = EMPTY;
}
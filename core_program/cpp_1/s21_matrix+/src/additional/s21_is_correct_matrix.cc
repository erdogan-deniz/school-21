#include "../s21_matrix_oop.h"

bool S21Matrix ::IsCorrectMatrix() const {
  bool answer = true;

  if (GetRows() <= EMPTY || GetColumns() <= EMPTY || GetMatrix() == nullptr)
    answer = false;

  return answer;
}
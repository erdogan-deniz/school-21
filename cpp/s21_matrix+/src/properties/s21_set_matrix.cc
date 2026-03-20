#include "../s21_matrix_oop.h"

void S21Matrix ::SetMatrix() {
  if (GetRows() < EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF ROWS!");
  else if (GetColumns() < EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF COLUMNS!");
  else if (GetMatrix() != nullptr)
    throw std ::logic_error("MATRIX ISN'T EMPTY!");
  else {
    matrix_ = new double *[GetRows() * 8]();

    if (GetMatrix() == nullptr)
      throw std ::range_error("DON'T HAVE ENOUGH MEMORY!");

    for (int i = 0; i < GetRows(); ++i) {
      matrix_[i] = new double[GetColumns() * 8]();

      if (matrix_[i] == nullptr)
        throw std ::range_error("DON'T HAVE ENOUGH MEMORY!");
    }
  }
}
#include "../s21_matrix_oop.h"

bool S21Matrix ::operator==(const S21Matrix &matrix) const {
  return EqMatrix(matrix);
}
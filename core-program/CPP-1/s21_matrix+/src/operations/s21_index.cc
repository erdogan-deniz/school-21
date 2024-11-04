#include "../s21_matrix_oop.h"

double S21Matrix ::operator()(const int i, const int j) const {
  if (i > GetRows() || j > GetColumns())
    throw std ::out_of_range("INDEXES BIGGER THAN MATRIX SIZE!");
  else
    return matrix_[i][j];
}

double &S21Matrix ::operator()(const int i, const int j) {
  if (i > GetRows() || j > GetColumns())
    throw std ::out_of_range("INDEXES BIGGER THAN MATRIX SIZE!");
  else
    return matrix_[i][j];
}
#include "../s21_matrix_oop.h"

void S21Matrix ::operator*=(const S21Matrix &matrix) { MulMatrix(matrix); }

void S21Matrix ::operator*=(const double number) { MulNumber(number); }
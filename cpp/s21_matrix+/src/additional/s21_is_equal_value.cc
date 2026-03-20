#include "../s21_matrix_oop.h"

bool S21Matrix ::IsEqualValue(const double value_one,
                              const double value_two) const {
  return fabs(value_one - value_two) < PRECISION;
}

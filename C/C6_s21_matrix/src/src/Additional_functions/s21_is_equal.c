#include "s21_additional_functions.h"

int s21_is_equal(double A, double B) {
        return fabs(A - B) < 1e-07? SUCCESS: FAILURE;
}
#include "../s21_matrix.h"

int s21_is_equal(double A, double B) {
        return fabs(A - B) < EPS? SUCCESS: FAILURE;
}
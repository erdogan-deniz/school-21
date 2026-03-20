#include "s21_math.h"

int s21_abs(int x) {
  int y = 0;
  if (x < 0) {
    y = x * (-1.0);
  } else {
    y = x;
  }
  return y;
}
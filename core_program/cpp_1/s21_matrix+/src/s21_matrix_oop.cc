#include "s21_matrix_oop.h"

S21Matrix ::S21Matrix() {
  if (SIZE <= EMPTY)
    throw std ::invalid_argument("INCORRECT MATRIX SIZE!");
  else {
    rows_ = SIZE;
    columns_ = SIZE;
    SetMatrix();
  }
}

S21Matrix ::S21Matrix(const int rows, const int columns) {
  if (rows <= EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF ROWS!");
  else if (columns <= EMPTY)
    throw std ::invalid_argument("INCORRECT NUMBER OF COLUMNS!");
  else {
    rows_ = rows;
    columns_ = columns;
    SetMatrix();
  }
}

S21Matrix ::S21Matrix(const S21Matrix &matrix) {
  if (matrix.GetRows() <= EMPTY)
    throw std ::invalid_argument("INCORRECT MATRIX NUMBER OF ROWS!");
  else if (matrix.GetColumns() <= EMPTY)
    throw std ::invalid_argument("INCORRECT MATRIX NUMBER OF COLUMNS!");
  else if (matrix.GetMatrix() == nullptr)
    throw std ::invalid_argument("MATRIX IS EMPTY!");
  else {
    rows_ = matrix.GetRows();
    columns_ = matrix.GetColumns();
    SetMatrix();

    for (int i = 0; i < GetRows(); ++i)
      for (int j = 0; j < GetColumns(); ++j)
        (*this)(i, j) = matrix(i, j);
  }
}

S21Matrix ::S21Matrix(S21Matrix &&matrix) {
  if (GetRows() > EMPTY)
    throw std ::logic_error("YOU WILL LOSE COUNT OF ROWS!");
  else if (GetColumns() > EMPTY)
    throw std ::logic_error("YOU WILL LOSE COUNT OF COLUMNS!");
  else if (GetMatrix())
    throw std ::logic_error("YOU WILL LOSE MATRIX!");
  else if (matrix.GetRows() <= EMPTY)
    throw std ::logic_error("INCORRECT COUNT OF MATRIX ROWS!");
  else if (matrix.GetColumns() <= EMPTY)
    throw std ::logic_error("INCORRECT COUNT OF MATRIX COLUMNS!");
  else if (matrix.GetMatrix() == nullptr)
    throw std ::logic_error("MATRIX IS EMPTY!");
  else {
    rows_ = matrix.GetRows();
    columns_ = matrix.GetColumns();
    matrix_ = matrix.GetMatrix();
    matrix.rows_ = EMPTY;
    matrix.columns_ = EMPTY;
    matrix.matrix_ = nullptr;
  }
}

S21Matrix ::~S21Matrix() { DeleteMatrix(); }
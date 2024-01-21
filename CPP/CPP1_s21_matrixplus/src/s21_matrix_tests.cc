#include "s21_matrix_oop.h"
#include <gtest/gtest.h>

// --------------------ADDITIONAL-------------------- //

// DownGrade():
// TEST(S21MatrixAdditional, down_grade_incorrect_matrix) {  // Will be throw
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.DownGrade(0, 0, matrix);
// }

// TEST(S21MatrixAdditional, down_grade_not_square_matrix) {  // Will be throw
//   S21Matrix matrix(2, 3);

//   matrix.DownGrade(0, 0, matrix);
// }

TEST(S21MatrixAdditional, down_grade_test) {
  S21Matrix matrix(4, 4);

  matrix.DownGrade(1, 1, matrix);
  // matrix.PrintMatrix();
}

// CopyMatrix():
// TEST(S21MatrixAdditionals, copy_incorrect_rows) {  // Can't be
//   S21Matrix matrix(-5, SIZE);
//   S21Matrix matrix_copy;

//   matrix_copy.DeleteMatrix();
//   matrix_copy.CopyMatrix(matrix)
// }

// TEST(S21MatrixAdditionals, copy_incorrect_columns) {  // Can't be
//   S21Matrix matrix(SIZE, -5);
//   S21Matrix matrix_copy;

//   matrix_copy.DeleteMatrix();
//   matrix_copy.CopyMatrix(matrix)
// }

// TEST(S21MatrixAdditionals, copy_empty) {  // Can't be
//   S21Matrix matrix = {0};
//   S21Matrix matrix_copy;

//   matrix.DeleteMatrix();
//   matrix.CopyMatrix(matrix);
// }

// TEST(S21MatrixAdditionals, copy_matrix_in_matrix) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_copy;

//   matrix.CopyMatrix(matrix);
// }

TEST(S21MatrixAdditionals, copy_matrix_example) {
  S21Matrix matrix(5, 5);

  matrix.FillMatrix();

  S21Matrix matrix_copy;

  matrix_copy.DeleteMatrix();
  matrix_copy.CopyMatrix(matrix);
  // matrix.PrintMatrix();
  // matrix_copy.PrintMatrix();
  ASSERT_EQ(matrix.GetRows(), matrix_copy.GetRows());
  ASSERT_EQ(matrix.GetColumns(), matrix_copy.GetColumns());

  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetColumns(); ++j)
      ASSERT_EQ(true, matrix.IsEqualValue(matrix(i, j), matrix_copy(i, j)));
}

// DeleteMatrix():
// TEST(S21MatrixAdditional, delete_matrix_empty) {  // Can't be
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.DeleteMatrix();
//   // matrix.PrintMatrix();
//   ASSERT_EQ(EMPTY, matrix.GetRows());
//   ASSERT_EQ(EMPTY, matrix.GetColumns());
//   ASSERT_EQ(true, matrix.GetMatrix() == nullptr);
// }

TEST(S21MatrixAdditional, delete_matrix_nonempty) {
  S21Matrix matrix;

  matrix.DeleteMatrix();
  // matrix.PrintMatrix();
  ASSERT_EQ(0, matrix.GetRows());
  ASSERT_EQ(0, matrix.GetColumns());
  ASSERT_EQ(false, matrix.GetMatrix() != nullptr);
}

// IsCorrectMatrix():
TEST(S21MatrixAdditional, is_correct_matrix_correct) {
  S21Matrix matrix;

  ASSERT_EQ(true, matrix.IsCorrectMatrix());
}

TEST(S21MatrixAdditional, is_correct_matrix_empty) {
  S21Matrix matrix;

  matrix.DeleteMatrix();
  ASSERT_EQ(false, matrix.IsCorrectMatrix());
}

// TEST(S21MatrixAdditional, is_correct_matrix_incorrect_rows) {  // Can't be
//   S21Matrix matrix;

//   matrix.SetRows(-5);
//   ASSERT_EQ(false, matrix.IsCorrectMatrix(););
// }

// TEST(S21MatrixAdditional, is_correct_matrix_incorrect_columns) {  // Can't be
//   S21Matrix matrix;

//   matrix.SetColumns(-5);
//   ASSERT_EQ(false, matrix.IsCorrectMatrix(););
// }

// TEST(S21MatrixAdditional, is_correct_matrix_incorrect_matrix) {  // Can't be
//   S21Matrix matrix;

//   matrix.SetMatrix();
//   ASSERT_EQ(false, matrix.IsCorrectMatrix(););
// }

// IsEqualMatrix():
TEST(S21MatrixAdditional, is_equal_matrix_zero) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  ASSERT_EQ(true, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_negative) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = -10;
  matrix_two(0, 0) = -10;
  ASSERT_EQ(true, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_positive) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = 10;
  matrix_two(0, 0) = 10;
  ASSERT_EQ(true, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_positive_less_border) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = 10.0000001;
  matrix_two(0, 0) = 10.0000002;
  ASSERT_EQ(false, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_negative_less_border) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = -10.0000001;
  matrix_two(0, 0) = -10.0000002;
  ASSERT_EQ(false, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_positive_more_border) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = 10.00000001;
  matrix_two(0, 0) = 10.00000002;
  ASSERT_EQ(true, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

TEST(S21MatrixAdditional, is_equal_matrix_negative_more_border) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = -10.00000001;
  matrix_two(0, 0) = -10.00000002;
  ASSERT_EQ(true, matrix.IsEqualValue(matrix(0, 0), matrix_two(0, 0)));
}

// PrintMatrix():
// TEST(S21MatrixAdditional, print_matrix_nonempty) {
//   S21Matrix matrix;

//   matrix.PrintMatrix();
// }

// TEST(S21MatrixAdditional, print_matrix_filling) {
//   S21Matrix matrix;

//   matrix.FillMatrix();
//   matrix.PrintMatrix();
// }

// TEST(S21MatrixAdditional, print_matrix_empty) {
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.PrintMatrix();
// }

// --------------------METHODS-------------------- //

// CalcComplements():
// TEST(S21MatrixMethods, calc_complements_incorrect_matrix) {  // Will be throw
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.CalcComplements();
// }

// TEST(S21MatrixMethods, calc_complements_not_square_matrix) {  // Will be
// throw
//   S21Matrix matrix(2, 3);

//   matrix.CalcComplements();
// }

TEST(S21MatrixMethods, calc_complements_test) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;

  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;

  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  S21Matrix result(3, 3);

  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;

  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;

  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;

  S21Matrix matrix_two(matrix.CalcComplements());

  // matrix_two.PrintMatrix();
  ASSERT_EQ(true, matrix_two.EqMatrix(result));
}

// EqMatrix():
TEST(S21MatrixMethods, eq_matrix_equal_default) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  ASSERT_EQ(true, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_nonequal_elements) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix(0, 0) = -1;
  ASSERT_EQ(false, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_nonequal_rows_first) {
  S21Matrix matrix(10, 5);
  S21Matrix matrix_two(5, 5);

  ASSERT_EQ(false, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_nonequal_rows_second) {
  S21Matrix matrix(5, 5);
  S21Matrix matrix_two(10, 5);

  ASSERT_EQ(false, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_nonequal_columns_first) {
  S21Matrix matrix(5, 10);
  S21Matrix matrix_two(5, 5);

  ASSERT_EQ(false, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_nonequal_columns_second) {
  S21Matrix matrix(5, 5);
  S21Matrix matrix_two(5, 10);

  ASSERT_EQ(false, matrix.EqMatrix(matrix_two));
}

TEST(S21MatrixMethods, eq_matrix_equal_nondefault) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();
  ASSERT_EQ(true, matrix.EqMatrix(matrix_two));
}

// MulMatrix():
// TEST(S21MatrixMethods, mul_matrix_incorrect_first_matrix) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix.DeleteMatrix();
//   matrix.MulMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, mul_matrix_incorrect_second_matrix) {  // Will be
// throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix_two.DeleteMatrix();
//   matrix.MulMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, mul_matrix_nonequal_rows_and_columns) {  // Will be
// throw
//   S21Matrix matrix;
//   S21Matrix matrix_two(SIZE + 1, SIZE + 1);

//   matrix.MulMatrix(matrix_two);
// }

TEST(S21MatrixMethods, mul_matrix_test) {
  S21Matrix matrix(3, 2);
  S21Matrix matrix_two(2, 3);
  S21Matrix result(3, 3);

  result(0, 0) = 9;
  result(0, 1) = 11;
  result(0, 2) = 17;

  result(1, 0) = 12;
  result(1, 1) = 13;
  result(1, 2) = 22;

  result(2, 0) = 15;
  result(2, 1) = 15;
  result(2, 2) = 27;

  matrix(0, 0) = 1;
  matrix(0, 1) = 4;

  matrix(1, 0) = 2;
  matrix(1, 1) = 5;

  matrix(2, 0) = 3;
  matrix(2, 1) = 6;

  matrix_two(0, 0) = 1;
  matrix_two(0, 1) = -1;
  matrix_two(0, 2) = 1;

  matrix_two(1, 0) = 2;
  matrix_two(1, 1) = 3;
  matrix_two(1, 2) = 4;

  matrix.MulMatrix(matrix_two);
  ASSERT_EQ(true, matrix.EqMatrix(result));
  // matrix.PrintMatrix();
}

// MulNumber():
TEST(S21MatrixMethods, mul_number_nonempty) {
  S21Matrix matrix;

  matrix.FillMatrix();

  S21Matrix matrix_copy(matrix);

  // matrix.PrintMatrix();
  matrix.MulNumber(-2.5);
  // matrix.PrintMatrix();

  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetColumns(); ++j)
      ASSERT_EQ(true,
                matrix.IsEqualValue(matrix_copy(i, j) * (-2.5), matrix(i, j)));
}

TEST(S21MatrixMethods, mul_number_empty) {
  S21Matrix matrix;

  matrix.DeleteMatrix();
  matrix.MulNumber(5);
  // matrix.PrintMatrix();
}

// SubMatrix():
// TEST(S21MatrixMethods, sub_matrix_incorrect_first) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix.DeleteMatrix();
//   matrix.SubMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, sub_matrix_incorrect_second) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix_two.DeleteMatrix();
//   matrix.SubMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, sub_matrix_nonequal_rows) {  // Will be throw
//   S21Matrix matrix(5, SIZE);
//   S21Matrix matrix_two;

//   matrix.SubMatrix(matrix_two);
// }

TEST(S21MatrixMethods, sub_matrix_nonempty) {
  S21Matrix matrix;

  matrix.FillMatrix();

  S21Matrix matrix_two;
  S21Matrix matrix_copy(matrix);

  // matrix.PrintMatrix();
  matrix_two(0, 0) = 1;
  matrix_two(0, 1) = 1;
  matrix_two(1, 0) = 1;
  matrix_two(1, 1) = 1;
  matrix.SumMatrix(matrix_two);
  // matrix.PrintMatrix();

  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetColumns(); ++j)
      ASSERT_EQ(true, matrix.IsEqualValue(matrix_copy(i, j) + matrix_two(i, j),
                                          matrix(i, j)));
}

// SumMatrix():
// TEST(S21MatrixMethods, sum_matrix_incorrect_first) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix.DeleteMatrix();
//   matrix.SumMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, sum_matrix_incorrect_second) {  // Will be throw
//   S21Matrix matrix;
//   S21Matrix matrix_two;

//   matrix_two.DeleteMatrix();
//   matrix.SumMatrix(matrix_two);
// }

// TEST(S21MatrixMethods, sum_matrix_nonequal_rows) {  // Will be throw
//   S21Matrix matrix(5, SIZE);
//   S21Matrix matrix_two;

//   matrix.SumMatrix(matrix_two);
// }

TEST(S21MatrixMethods, sum_matrix_nonempty) {
  S21Matrix matrix;

  matrix.FillMatrix();

  S21Matrix matrix_two;
  S21Matrix matrix_copy(matrix);

  // matrix.PrintMatrix();
  matrix_two(0, 0) = 1;
  matrix_two(0, 1) = 1;
  matrix_two(1, 0) = 1;
  matrix_two(1, 1) = 1;
  matrix.SumMatrix(matrix_two);
  // matrix.PrintMatrix();

  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetColumns(); ++j)
      ASSERT_EQ(true, matrix.IsEqualValue(matrix_copy(i, j) + matrix_two(i, j),
                                          matrix(i, j)));
}

// Transpose():
// TEST(S21MatrixMethods, transpose_incorrect_matrix) {  // Will be throw
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.Transpose();
// }

TEST(S21MatrixMethods, transpose_example) {
  S21Matrix matrix(3, 2);

  matrix(0, 0) = 1;
  matrix(0, 1) = 4;

  matrix(1, 0) = 2;
  matrix(1, 1) = 5;

  matrix(2, 0) = 3;
  matrix(2, 1) = 6;

  S21Matrix result(2, 3);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(0, 2) = 3;

  result(1, 0) = 4;
  result(1, 1) = 5;
  result(1, 2) = 6;

  S21Matrix matrix_two(matrix.Transpose());

  ASSERT_EQ(true, matrix_two.EqMatrix(result));
}

// Determinant():
// TEST(S21MatrixMethods, determinant_incorrect_matrix) {  // Will be throw
//   S21Matrix matrix;

//   matirx.DeleteMatrix();
//   matrix.Determinant();
// }

// TEST(S21MatrixMethods, determinant_not_square_matrix) {  // Will be throw
//   S21Matrix matrix(2, 3);

//   matrix.Determinant();
// }

TEST(S21MatrixMethods, determinant_test_big) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 6;

  matrix(1, 0) = 4;
  matrix(1, 1) = 3;
  matrix(1, 2) = -1;

  matrix(2, 0) = 2;
  matrix(2, 1) = -2;
  matrix(2, 2) = 5;

  ASSERT_EQ(-115, matrix.Determinant());
}

TEST(S21MatrixMethods, determinant_test_small) {
  S21Matrix matrix(1, 1);

  matrix(0, 0) = 1;
  ASSERT_EQ(1, matrix.Determinant());
}

TEST(S21MatrixMethods, determinant_test_medium) {
  S21Matrix matrix;

  matrix(0, 0) = 2;
  matrix(0, 1) = -3;

  matrix(1, 0) = 5;
  matrix(1, 1) = 6;
  ASSERT_EQ(27, matrix.Determinant());
}

// InverseMatrix():
// TEST(S21MatrixMethods, inverse_matrix_incorrect_matrix) {  // Will be throw
//   S21Matrix matrix;

//   matrix.DeleteMatrix();
//   matrix.InverseMatrix();
// }

// TEST(S21MatrixMethods, inverse_matrix_not_square_matrix) {  // Will be throw
//   S21Matrix matrix(2, 3);

//   matrix.InverseMatrix();
// }

TEST(S21MatrixMethods, inverse_matrix_test) {

  S21Matrix result(3, 3);

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;

  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;

  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  S21Matrix matrix(3, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;

  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;

  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  S21Matrix matrix_two(matrix.InverseMatrix());

  // matrix_two.PrintMatrix();
  ASSERT_EQ(true, matrix_two.EqMatrix(result));
}

// --------------------OPERATIONS-------------------- //

// +:
TEST(S21MatrixOperations, plus) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();
  // matrix.PrintMatrix();

  S21Matrix matrix_three(matrix + matrix_two);

  // matrix_three.PrintMatrix();
  matrix.SumMatrix(matrix_two);
  ASSERT_EQ(true, (matrix_three == matrix));
}

// -:
TEST(S21MatrixOperations, minus) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();
  // matrix.PrintMatrix();

  S21Matrix matrix_three(matrix - matrix_two);

  // matrix_three.PrintMatrix();
  matrix.SubMatrix(matrix_two);
  ASSERT_EQ(true, matrix_three == matrix);
}

// *:
TEST(S21MatrixOperations, mult_number) {
  S21Matrix matrix;

  matrix.FillMatrix();
  // matrix.PrintMatrix();

  S21Matrix matrix_two(matrix * 2.5);

  // matrix_two.PrintMatrix();
  matrix.MulNumber(2.5);
  ASSERT_EQ(true, (matrix_two == matrix));
}

TEST(S21MatrixOperations, mult_matrix) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();
  // matrix.PrintMatrix();
  // matrix_two.PrintMatrix();

  S21Matrix matrix_three(matrix * matrix_two);

  // matrix_three.PrintMatrix();
  matrix.MulMatrix(matrix_two);
  ASSERT_EQ(true, matrix_three.EqMatrix(matrix));
}

// ==:
TEST(S21MatrixOperations, equal) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  ASSERT_EQ(true, (matrix == matrix_two));
}

// =:
TEST(S21MatrixOperations, assigne) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two = matrix;
  // matrix_two.PrintMatrix();
  ASSERT_EQ(true, (matrix == matrix_two));
}

// +=:
TEST(S21MatrixOperations, plus_equal) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two += matrix;
  // matrix_two.PrintMatrix();
  ASSERT_EQ(true, (matrix == matrix_two));
}

// -=:
TEST(S21MatrixOperations, minus_equal) {
  S21Matrix matrix;
  S21Matrix matrix_two;
  S21Matrix matrix_copy(matrix);

  matrix.FillMatrix();

  matrix_two -= matrix;
  // matrix_two.PrintMatrix();
  matrix_copy.SubMatrix(matrix);
  ASSERT_EQ(true, (matrix_two == matrix_copy));
}

// *=:
TEST(S21MatrixOperations, mult_equal_number) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();
  matrix *= 2;
  matrix_two.MulNumber(2);
  // matrix_two.PrintMatrix();

  ASSERT_EQ(true, (matrix == matrix_two));
}

TEST(S21MatrixOperations, mult_equal_matrix) {
  S21Matrix matrix;
  S21Matrix matrix_two;

  matrix.FillMatrix();
  matrix_two.FillMatrix();

  S21Matrix matrix_copy(matrix);

  matrix *= matrix_two;
  // matrix_two.PrintMatrix();
  matrix_copy.MulMatrix(matrix_two);
  ASSERT_EQ(true, (matrix == matrix_copy));
}

// ():
// TEST(S21MatrixOperations, index_error) {  // Will be throw
//   S21Matrix matrix;

//   matrix(SIZE + 1, SIZE);
// }

// --------------------PROPERTIES-------------------- //

// GetRows():
TEST(S21MatrixAdditional, get_rows_default) {
  S21Matrix matrix;

  ASSERT_EQ(SIZE, matrix.GetRows());
}

TEST(S21MatrixAdditional, get_rows_nondefault) {
  S21Matrix matrix(10, 100);

  ASSERT_EQ(10, matrix.GetRows());
}

// GetColumns():
TEST(S21MatrixAdditional, get_columns_default) {
  S21Matrix matrix;

  ASSERT_EQ(SIZE, matrix.GetColumns());
}

TEST(S21MatrixAdditional, get_columns_nondefault) {
  S21Matrix matrix(10, 100);

  ASSERT_EQ(100, matrix.GetColumns());
}

// GetMatrix():
TEST(S21MatrixAdditional, get_matrix_default) {
  S21Matrix matrix;

  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

TEST(S21MatrixAdditional, get_columns_nondefaults) {
  S21Matrix matrix(10, 100);

  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// SetRows():
// TEST(S21MatrixAdditional, set_rows_negative) {  // Throw will work
//   S21Matrix matrix;

//   matrix.SetRows(-5);
// }

TEST(S21MatrixAdditional, set_rows_zero) {
  S21Matrix matrix;

  matrix.SetRows(0);
  ASSERT_EQ(EMPTY, matrix.GetRows());
  ASSERT_EQ(EMPTY, matrix.GetColumns());
  ASSERT_EQ(nullptr, matrix.GetMatrix());
}

TEST(S21MatrixAdditional, set_rows_bigger) {
  S21Matrix matrix;

  matrix.SetRows(10);
  // matrix.PrintMatrix();
  ASSERT_EQ(10, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

TEST(S21MatrixAdditional, set_rows_less) {
  S21Matrix matrix;

  matrix.SetRows(1);
  // matrix.PrintMatrix();
  ASSERT_EQ(1, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

TEST(S21MatrixAdditional, set_rows_equal) {
  S21Matrix matrix;

  matrix.SetRows(SIZE);
  // matrix.PrintMatrix();
  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// SetColumns():
// TEST(S21MatrixAdditional, set_columns_negative) {  // Throw will work
//   S21Matrix matrix;

//   matrix.SetColumns(-5);
// }

TEST(S21MatrixAdditional, set_columns_zero) {
  S21Matrix matrix;

  matrix.SetColumns(0);
  ASSERT_EQ(EMPTY, matrix.GetRows());
  ASSERT_EQ(EMPTY, matrix.GetColumns());
  ASSERT_EQ(nullptr, matrix.GetMatrix());
}

TEST(S21MatrixAdditional, set_columns_bigger) {
  S21Matrix matrix;

  matrix.SetColumns(10);
  // matrix.PrintMatrix();
  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(10, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

TEST(S21MatrixAdditional, set_columns_less) {
  S21Matrix matrix;

  matrix.SetColumns(1);
  // matrix.PrintMatrix();
  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(1, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

TEST(S21MatrixAdditional, set_columns_equal) {
  S21Matrix matrix;

  matrix.SetColumns(SIZE);
  // matrix.PrintMatrix();
  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// SetMatrix():
// TEST(S21MatrixAdditional, set_matrix_negativ_rows) {  // Can't be real
//   S21Matrix matrix;

//   matrix.SetRows(-5);
// }

// TEST(S21MatrixAdditional, set_matrix_negativ_columns) {  // Can't be real
//   S21Matrix matrix;

//   matrix.SetColumns(-5);
// }

// TEST(S21MatrixAdditional, set_matrix_nonempty) {  // Throw will work
//   S21Matrix matrix;

//   matrix.SetMatrix();
// }

TEST(S21MatrixAdditional, set_matrix_normal) {
  S21Matrix matrix;

  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// --------------------CONSTRUCTORS-------------------- //

// S21Matrix():
// TEST(S21MatrixConstructors, s21_matrix_negative) {  // Throw will work
//   #define SIZE -5

//   S21Matrix matrix;
// }

TEST(S21MatrixConstructors, s21_matrix_default) {
  S21Matrix matrix;

  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// S21Matrix(rows, columns):
// TEST(S21MatrixConstructors, s21_matrix_parameters_incorrect_rows) {  // Throw
// will be
//   S21Matrix matrix(-5, SIZE);
// }

// TEST(S21MatrixConstructors, s21_matrix_parameters_incorrect_columns) {  //
// Throw will be
//   S21Matrix matrix(SIZE, -5);
// }

// TEST(S21MatrixConstructors, s21_matrix_parameters_incorrect_rows_and_columns)
// {  // Throw will be
//   S21Matrix matrix(SIZE, 0);
// }

TEST(S21MatrixConstructors, s21_matrix_parameters_default) {
  S21Matrix matrix(15, 10);

  // matrix.PrintMatrix();
  ASSERT_EQ(15, matrix.GetRows());
  ASSERT_EQ(10, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

// S21Matrix(matrix):
// TEST(S21MatrixConstructors, s21_matrix_copy_incorrect_rows) {  // Can't be
//   S21Matrix matrix(-5, SIZE);
//   S21Matrix matrix_copy(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_copy_incorrect_columns) {  // Can't be
//   S21Matrix matrix(SIZE, -5);
//   S21Matrix matrix_copy(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_copy_empty) {  // Can't be
//   S21Matrix matrix = {0};
//   S21Matrix matrix_copy(matrix);
// }

TEST(S21MatrixConstructors, s21_matrix_copy_empty) {
  S21Matrix matrix(5, 5);

  // matrix.FillMatrix();

  S21Matrix matrix_copy(matrix);

  // matrix.PrintMatrix();
  // matrix_copy.PrintMatrix();
  ASSERT_EQ(matrix.GetRows(), matrix_copy.GetRows());
  ASSERT_EQ(matrix.GetColumns(), matrix_copy.GetColumns());

  for (int i = 0; i < matrix.GetRows(); ++i)
    for (int j = 0; j < matrix.GetColumns(); ++j)
      ASSERT_EQ(true, matrix.IsEqualValue(matrix(i, j), matrix_copy(i, j)));
}

// S21Matrix(move(matrix)):
// TEST(S21MatrixConstructors, s21_matrix_move_incorrect_matrix_rows) {  // Will
// be throw
//   S21Matrix matrix;
//   matrix.DeleteMatrix();
//   S21Matrix matrix_move(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_move_incorrect_matrix_columns) {  //
// Can't be
//   S21Matrix matrix;
//   matrix.DeleteMatrix();
//   S21Matrix matrix_move(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_move_incorrect_matrix) {  // Can't be
//   S21Matrix matrix;
//   matrix.DeleteMatrix();
//   S21Matrix matrix_move(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_move_nonempty_rows) {  // Can't be
//   S21Matrix matrix;
//   S21Matrix matrix_move(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_move_nonempty_columns) {  // Can't be
//   S21Matrix matrix;
//   S21Matrix matrix_move(matrix);
// }

// TEST(S21MatrixConstructors, s21_matrix_move_nonempty_matrix) {  // Can't be
//   S21Matrix matrix;
//   S21Matrix matrix_move(matrix);
// }

TEST(S21MatrixConstructors, s21_matrix_move_default) {
  S21Matrix matrix(5, 10);
  matrix.FillMatrix();
  S21Matrix matrix_move(std ::move(matrix));

  // matrix_move.PrintMatrix();
  // matrix.PrintMatrix();
  ASSERT_EQ(5, matrix_move.GetRows());
  ASSERT_EQ(10, matrix_move.GetColumns());
  ASSERT_EQ(true, matrix_move.GetMatrix() != nullptr);
  ASSERT_EQ(EMPTY, matrix.GetRows());
  ASSERT_EQ(EMPTY, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() == nullptr);
}

// ~S21Matrix():
TEST(S21MatrixConstructors, s21_matrix_destructor_empty) {
  S21Matrix matrix;

  matrix.DeleteMatrix();
  // matrix.PrintMatrix();
  ASSERT_EQ(EMPTY, matrix.GetRows());
  ASSERT_EQ(EMPTY, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() == nullptr);
}

TEST(S21MatrixConstructors, s21_matrix_destructor_nonempty) {
  S21Matrix matrix;

  // matrix.PrintMatrix();
  ASSERT_EQ(SIZE, matrix.GetRows());
  ASSERT_EQ(SIZE, matrix.GetColumns());
  ASSERT_EQ(true, matrix.GetMatrix() != nullptr);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
#include "../s21_matrix.h"
#include "test_main.h"

// Тест на матрицу 1х1
START_TEST(test_determinant_1x1) {
  matrix_t A;
  double result;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 5.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест на матрицу 2х2
START_TEST(test_determinant_2x2) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 3.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 10.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест на матрицу 3х3
START_TEST(test_determinant_3x3) {
  matrix_t A;
  double result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 5.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 6.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 22.0);

  s21_remove_matrix(&A);
}
END_TEST

// Тест на некорректную матрицу
START_TEST(test_determinant_non_square_matrix) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_determinant(&A, &result), ERROR_COR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_zero_value) {
  matrix_t A;
  double result;

  // Создание и инициализация матрицы 2x2 с нулевым определителем
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 0.0);  // Определитель равен 0

  // Освобождение памяти
  s21_remove_matrix(&A);
}
END_TEST

Suite *matrix_det_suite(void) {
  Suite *s;
  TCase *tc_determinant;

  s = suite_create("MatrixDeterminant");

  tc_determinant = tcase_create("Determinant");
  tcase_add_test(tc_determinant, test_determinant_1x1);
  tcase_add_test(tc_determinant, test_determinant_2x2);
  tcase_add_test(tc_determinant, test_determinant_3x3);
  tcase_add_test(tc_determinant, test_determinant_non_square_matrix);
  tcase_add_test(tc_determinant, test_determinant_zero_value);
  suite_add_tcase(s, tc_determinant);

  return s;
}
#include "../s21_matrix.h"
#include "test_main.h"

// Тест на матрицу 2х2
START_TEST(test_inverse_matrix_2x2) {
  matrix_t A;
  matrix_t result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 7.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 6.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на матрицу 3х3
START_TEST(test_inverse_matrix_3x3) {
  matrix_t A;
  matrix_t result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][0], -24.0);
  ck_assert_double_eq(result.matrix[0][1], 18.0);
  ck_assert_double_eq(result.matrix[0][2], 5.0);
  ck_assert_double_eq(result.matrix[1][0], 20.0);
  ck_assert_double_eq(result.matrix[1][1], -15.0);
  ck_assert_double_eq(result.matrix[1][2], -4.0);
  ck_assert_double_eq(result.matrix[2][0], -5.0);
  ck_assert_double_eq(result.matrix[2][1], 4.0);
  ck_assert_double_eq(result.matrix[2][2], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на некорректную матрицу
START_TEST(test_inverse_matrix_non_square) {
  matrix_t A;
  matrix_t result;

  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_CALC);

  s21_remove_matrix(&A);
}
END_TEST

// Тест на матрицу с нулевыми определителями
START_TEST(test_inverse_matrix_singular) {
  matrix_t A;
  matrix_t result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_CALC);

  s21_remove_matrix(&A);
}
END_TEST

// Тест на нулевую матрицу
START_TEST(test_inverse_matrix_zero_matrix) {
  matrix_t A;
  matrix_t result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_CALC);

  s21_remove_matrix(&A);
}
END_TEST

Suite *matrix_inv_suite(void) {
  Suite *s;
  TCase *tc_inverse;

  s = suite_create("MatrixInverse");

  tc_inverse = tcase_create("Inverse");
  tcase_add_test(tc_inverse, test_inverse_matrix_2x2);
  tcase_add_test(tc_inverse, test_inverse_matrix_3x3);
  tcase_add_test(tc_inverse, test_inverse_matrix_non_square);
  tcase_add_test(tc_inverse, test_inverse_matrix_singular);
  tcase_add_test(tc_inverse, test_inverse_matrix_zero_matrix);
  suite_add_tcase(s, tc_inverse);

  return s;
}
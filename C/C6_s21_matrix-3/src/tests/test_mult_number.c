#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное умножение
START_TEST(test_mult_matrix_by_number_normal_case) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  expected.matrix[0][0] = 2.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 6.0;
  expected.matrix[1][1] = 8.0;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на умножение на ноль
START_TEST(test_mult_matrix_by_zero) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  expected.matrix[0][0] = 0.0;
  expected.matrix[0][1] = 0.0;
  expected.matrix[1][0] = 0.0;
  expected.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_mult_number(&A, 0.0, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на умножение на отрицательное
START_TEST(test_mult_matrix_by_negative_number) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = 4.0;

  expected.matrix[0][0] = -2.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 6.0;
  expected.matrix[1][1] = -8.0;

  ck_assert_int_eq(s21_mult_number(&A, -2.0, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на умножение на нецелое
START_TEST(test_mult_matrix_by_fractional_number) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 8.0;

  expected.matrix[0][0] = 1.0;
  expected.matrix[0][1] = 2.0;
  expected.matrix[1][0] = 3.0;
  expected.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_mult_number(&A, 0.5, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на неинициализированную матрицу
START_TEST(test_mult_matrix_by_invalid_matrix) {
  matrix_t result;

  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &result), ERROR_COR);
}
END_TEST

Suite *matrix_multn_suite(void) {
  Suite *s;
  TCase *tc_mult;

  s = suite_create("MatrixMultiplicationNumber");

  tc_mult = tcase_create("MultNumber");
  tcase_add_test(tc_mult, test_mult_matrix_by_number_normal_case);
  tcase_add_test(tc_mult, test_mult_matrix_by_zero);
  tcase_add_test(tc_mult, test_mult_matrix_by_negative_number);
  tcase_add_test(tc_mult, test_mult_matrix_by_fractional_number);
  tcase_add_test(tc_mult, test_mult_matrix_by_invalid_matrix);
  suite_add_tcase(s, tc_mult);

  return s;
}
#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное сложение
START_TEST(test_sum_valid_matrices) {
  matrix_t A, B, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  expected.matrix[0][0] = 6;
  expected.matrix[0][1] = 8;
  expected.matrix[1][0] = 10;
  expected.matrix[1][1] = 12;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на сложение матриц разного размера
START_TEST(test_sum_incorrect_dimensions) {
  matrix_t A, B, result;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на сложение нулевых матриц
START_TEST(test_matrix_addition_zero_matrix) {
  matrix_t A, B, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  expected.matrix[0][0] = 0.0;
  expected.matrix[0][1] = 0.0;
  expected.matrix[1][0] = 0.0;
  expected.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *matrix_sum_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MatrixSummarize");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sum_valid_matrices);
  tcase_add_test(tc_core, test_sum_incorrect_dimensions);
  tcase_add_test(tc_core, test_matrix_addition_zero_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}
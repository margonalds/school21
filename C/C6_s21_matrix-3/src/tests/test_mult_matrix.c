#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное умножение
START_TEST(test_mult_matrix_normal_case) {
  matrix_t A, B, result, expected;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 8.0;
  B.matrix[1][0] = 9.0;
  B.matrix[1][1] = 10.0;
  B.matrix[2][0] = 11.0;
  B.matrix[2][1] = 12.0;

  expected.matrix[0][0] = 58.0;
  expected.matrix[0][1] = 64.0;
  expected.matrix[1][0] = 139.0;
  expected.matrix[1][1] = 154.0;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на умножение несовместимых размеров
START_TEST(test_mult_matrix_incompatible_dimensions) {
  matrix_t A, B, result;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(4, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 8.0;
  B.matrix[1][0] = 9.0;
  B.matrix[1][1] = 10.0;
  B.matrix[2][0] = 11.0;
  B.matrix[2][1] = 12.0;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на перемножение идентичных матриц
START_TEST(test_mult_matrix_by_identity_matrix) {
  matrix_t A, B, result;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &A), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на умножение на нулевую матрицу
START_TEST(test_mult_matrix_by_zero_matrix) {
  matrix_t A, B, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 0.0;

  expected.matrix[0][0] = 0.0;
  expected.matrix[0][1] = 0.0;
  expected.matrix[1][0] = 0.0;
  expected.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на неинициализированные матрицы
START_TEST(test_mult_matrix_invalid_matrices) {
  matrix_t result;

  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, &result), ERROR_COR);
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, NULL), ERROR_COR);
}
END_TEST

Suite *matrix_multm_suite(void) {
  Suite *s;
  TCase *tc_mult;

  s = suite_create("MatrixMultiplicationMatrix");

  tc_mult = tcase_create("MultMatrix");
  tcase_add_test(tc_mult, test_mult_matrix_normal_case);
  tcase_add_test(tc_mult, test_mult_matrix_incompatible_dimensions);
  tcase_add_test(tc_mult, test_mult_matrix_by_identity_matrix);
  tcase_add_test(tc_mult, test_mult_matrix_by_zero_matrix);
  tcase_add_test(tc_mult, test_mult_matrix_invalid_matrices);
  suite_add_tcase(s, tc_mult);

  return s;
}
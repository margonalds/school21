#include "../s21_matrix.h"
#include "test_main.h"

// Teст на корректную матрицу
START_TEST(test_transpose_normal_case) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  expected.matrix[0][0] = 1.0;
  expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 2.0;
  expected.matrix[1][1] = 5.0;
  expected.matrix[2][0] = 3.0;
  expected.matrix[2][1] = 6.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на неинициализированную матрицу
START_TEST(test_transpose_invalid_matrix) {
  matrix_t result = {0};

  ck_assert_int_eq(s21_transpose(NULL, &result), ERROR_COR);
  ck_assert_int_eq(s21_transpose(&result, NULL), ERROR_COR);
}
END_TEST

Suite *matrix_trans_suite(void) {
  Suite *s;
  TCase *tc_transpose;

  s = suite_create("MatrixTranspose");

  tc_transpose = tcase_create("TransposeMatrix");
  tcase_add_test(tc_transpose, test_transpose_normal_case);
  tcase_add_test(tc_transpose, test_transpose_invalid_matrix);
  suite_add_tcase(s, tc_transpose);

  return s;
}
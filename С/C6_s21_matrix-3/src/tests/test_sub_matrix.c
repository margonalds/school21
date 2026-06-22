#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное вычитание
START_TEST(test_sub_valid_matrices) {
  matrix_t A, B, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 6;
  A.matrix[0][1] = 8;
  A.matrix[1][0] = 10;
  A.matrix[1][1] = 12;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  expected.matrix[0][0] = 5;
  expected.matrix[0][1] = 6;
  expected.matrix[1][0] = 7;
  expected.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на вычитание матриц разного размера
START_TEST(test_sub_incorrect_dimensions) {
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

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на некорректную матрицу
START_TEST(test_sub_null_matrices) {
  matrix_t result;

  ck_assert_int_eq(s21_sub_matrix(NULL, NULL, &result), ERROR_COR);
  ck_assert_int_eq(s21_sub_matrix(NULL, NULL, NULL), ERROR_COR);
}
END_TEST

Suite *matrix_sub_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MatrixSubstraction");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sub_valid_matrices);
  tcase_add_test(tc_core, test_sub_incorrect_dimensions);
  tcase_add_test(tc_core, test_sub_null_matrices);
  suite_add_tcase(s, tc_core);

  return s;
}
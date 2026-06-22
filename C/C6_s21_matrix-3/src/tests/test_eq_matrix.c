#include "../s21_matrix.h"
#include "test_main.h"

// Тест на сравнение двух одинаковых матриц
START_TEST(test_eq_matrix_equal_matrices) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на сравнение двух разных матриц
START_TEST(test_eq_matrix_unequal_matrices) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 5.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на  сравнение матриц разных размеров
START_TEST(test_eq_matrix_different_sizes) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 5.0;
  B.matrix[1][2] = 6.0;
  B.matrix[2][0] = 7.0;
  B.matrix[2][1] = 8.0;
  B.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на сравнение матриц с погрешностью
START_TEST(test_eq_matrix_with_eps) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.00000001;
  A.matrix[0][1] = 2.00000001;
  A.matrix[1][0] = 3.00000001;
  A.matrix[1][1] = 4.00000001;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест на сравнение матрицы с NULL
START_TEST(test_eq_matrix_null_matrix) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

Suite *matrix_eq_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MatrixEquality");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_eq_matrix_equal_matrices);
  tcase_add_test(tc_core, test_eq_matrix_unequal_matrices);
  tcase_add_test(tc_core, test_eq_matrix_different_sizes);
  tcase_add_test(tc_core, test_eq_matrix_with_eps);
  tcase_add_test(tc_core, test_eq_matrix_null_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}
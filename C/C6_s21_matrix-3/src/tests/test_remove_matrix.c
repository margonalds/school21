#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное освобождение памяти матрицы
START_TEST(test_remove_matrix_valid) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);

  ck_assert_ptr_nonnull(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 3);
  ck_assert_int_eq(matrix.columns, 3);

  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест на удаление уже пустой матрицы
START_TEST(test_remove_matrix_null_matrix) {
  matrix_t matrix;
  matrix.matrix = NULL;
  matrix.rows = 0;
  matrix.columns = 0;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест на корректное удаление после нескольких вызовов
START_TEST(test_remove_matrix_double_call) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);

  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Добавляем все тесты в тестовый набор
Suite *matrix_rm_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MatrixRemoval");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_remove_matrix_valid);
  tcase_add_test(tc_core, test_remove_matrix_null_matrix);
  tcase_add_test(tc_core, test_remove_matrix_double_call);
  suite_add_tcase(s, tc_core);

  return s;
}
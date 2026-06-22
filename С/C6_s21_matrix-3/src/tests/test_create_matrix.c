#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректное создание матрицы
START_TEST(test_create_matrix_valid) {
  matrix_t result;
  int error = s21_create_matrix(3, 3, &result);
  ck_assert_int_eq(error, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(result.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&result);
}
END_TEST

// Тест на строки < 0
START_TEST(test_create_matrix_invalid_rows) {
  matrix_t result;
  int error = s21_create_matrix(-3, 3, &result);
  ck_assert_int_eq(error, ERROR_COR);
}
END_TEST

// Тест на столбцы < 0
START_TEST(test_create_matrix_invalid_columns) {
  matrix_t result;
  int error = s21_create_matrix(3, -3, &result);
  ck_assert_int_eq(error, ERROR_COR);
}
END_TEST

// Тест на 0 строк
START_TEST(test_create_matrix_zero_rows) {
  matrix_t result;
  int error = s21_create_matrix(0, 3, &result);
  ck_assert_int_eq(error, ERROR_COR);
}
END_TEST

// Тест на 0 столбцов
START_TEST(test_create_matrix_zero_columns) {
  matrix_t result;
  int error = s21_create_matrix(3, 0, &result);
  ck_assert_int_eq(error, ERROR_COR);
}
END_TEST

Suite *matrix_create_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MatrixCreation");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_matrix_valid);
  tcase_add_test(tc_core, test_create_matrix_invalid_rows);
  tcase_add_test(tc_core, test_create_matrix_invalid_columns);
  tcase_add_test(tc_core, test_create_matrix_zero_rows);
  tcase_add_test(tc_core, test_create_matrix_zero_columns);
  suite_add_tcase(s, tc_core);

  return s;
}
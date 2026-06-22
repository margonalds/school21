#include "../s21_matrix.h"
#include "test_main.h"

// Тест на корректную матрицу
START_TEST(test_calc_complements_normal_case) {
  matrix_t A, result, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  expected.matrix[0][0] = 4.0;
  expected.matrix[0][1] = -3.0;
  expected.matrix[1][0] = -2.0;
  expected.matrix[1][1] = 1.0;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на некорректную матрицу
START_TEST(test_calc_complements_non_square_matrix) {
  matrix_t A, result;

  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &result), ERROR_COR);

  s21_remove_matrix(&A);
}
END_TEST

Suite *matrix_comp_suite(void) {
  Suite *s;
  TCase *tc_complements;

  s = suite_create("MatrixOperations");

  tc_complements = tcase_create("CalcComplements");
  tcase_add_test(tc_complements, test_calc_complements_normal_case);
  tcase_add_test(tc_complements, test_calc_complements_non_square_matrix);
  suite_add_tcase(s, tc_complements);

  return s;
}
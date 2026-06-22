#include "test_main.h"

#include "../s21_matrix.h"

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, matrix_comp_suite());
  srunner_add_suite(sr, matrix_create_suite());
  srunner_add_suite(sr, matrix_det_suite());
  srunner_add_suite(sr, matrix_eq_suite());
  srunner_add_suite(sr, matrix_inv_suite());
  srunner_add_suite(sr, matrix_multm_suite());
  srunner_add_suite(sr, matrix_multn_suite());
  srunner_add_suite(sr, matrix_rm_suite());
  srunner_add_suite(sr, matrix_sub_suite());
  srunner_add_suite(sr, matrix_sum_suite());
  srunner_add_suite(sr, matrix_trans_suite());

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

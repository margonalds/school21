#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <check.h>

Suite *matrix_comp_suite(void);
Suite *matrix_create_suite(void);
Suite *matrix_det_suite(void);
Suite *matrix_eq_suite(void);
Suite *matrix_inv_suite(void);
Suite *matrix_multm_suite(void);
Suite *matrix_multn_suite(void);
Suite *matrix_rm_suite(void);
Suite *matrix_sub_suite(void);
Suite *matrix_sum_suite(void);
Suite *matrix_trans_suite(void);

#endif  // TEST_MAIN_H

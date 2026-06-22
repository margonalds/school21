#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

void test_s21_strerror(int errnum) {
  char *expected = strerror(errnum);
  char *result = s21_strerror(errnum);

  ck_assert_str_eq(result, expected);
}

START_TEST(test_s21_strerror_basic) {
  for (int i = 0; i <= 34; i++) {
    test_s21_strerror(i);
  }
}
END_TEST

START_TEST(test_s21_strerror_out_of_range) { test_s21_strerror(1000); }
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strerror");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strerror_basic);
  tcase_add_test(tc_core, test_s21_strerror_out_of_range);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_strerror_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
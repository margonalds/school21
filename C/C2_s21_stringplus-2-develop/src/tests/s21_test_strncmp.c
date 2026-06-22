#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strncmp_equal) {
  char *str1 = "Hello, World!";
  char *str2 = "Hello, World!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_s21_strncmp_not_equal) {
  char *str1 = "Hello, World!";
  char *str2 = "Hello, there!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));
}
END_TEST

START_TEST(test_s21_strncmp_zero_n) {
  char *str1 = "Hello, World!";
  char *str2 = "Hello, there!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_s21_strncmp_partial_match) {
  char *str1 = "Hello, World!";
  char *str2 = "Hello, Universe!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncmp");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncmp_equal);
  tcase_add_test(tc_core, test_s21_strncmp_not_equal);
  tcase_add_test(tc_core, test_s21_strncmp_zero_n);
  tcase_add_test(tc_core, test_s21_strncmp_partial_match);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_strncmp_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
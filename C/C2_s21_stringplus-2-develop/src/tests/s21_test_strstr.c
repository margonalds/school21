#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strstr_basic) {
  char haystack[] = "Hello, world!";
  char needle[] = "world";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  char haystack[] = "Hello, world!";
  char needle[] = "planet";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), NULL);
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  char haystack[] = "Hello, world!";
  char needle[] = "";
  ck_assert_str_eq(s21_strstr(haystack, needle), haystack);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strstr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strstr_basic);
  tcase_add_test(tc_core, test_s21_strstr_not_found);
  tcase_add_test(tc_core, test_s21_strstr_empty_needle);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *suite = s21_strstr_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
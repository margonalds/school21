#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strcspn_basic) {
  char str[] = "Hello, world!";
  char reject[] = "world";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_no_reject) {
  char str[] = "Hello, world!";
  char reject[] = "xyz";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_empty_reject) {
  char str[] = "Hello, world!";
  char reject[] = "";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strcspn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strcspn_basic);
  tcase_add_test(tc_core, test_s21_strcspn_no_reject);
  tcase_add_test(tc_core, test_s21_strcspn_empty_reject);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *suite = s21_strcspn_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
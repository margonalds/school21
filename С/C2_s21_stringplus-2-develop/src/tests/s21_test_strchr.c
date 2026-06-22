#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strchr_found) {
  char str[] = "Hello, world!";
  char ch = 'o';
  ck_assert_ptr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
  char str[] = "Hello, world!";
  char ch = 'x';
  ck_assert_ptr_eq(s21_strchr(str, ch), NULL);
}
END_TEST

START_TEST(test_s21_strchr_first_char) {
  char str[] = "Hello, world!";
  char ch = 'H';
  ck_assert_ptr_eq(s21_strchr(str, ch), str);
}
END_TEST

START_TEST(test_s21_strchr_last_char) {
  char str[] = "Hello, world!";
  char ch = '!';
  ck_assert_ptr_eq(s21_strchr(str, ch), str + strlen(str) - 1);
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strchr_found);
  tcase_add_test(tc_core, test_s21_strchr_not_found);
  tcase_add_test(tc_core, test_s21_strchr_first_char);
  tcase_add_test(tc_core, test_s21_strchr_last_char);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *suite = s21_strchr_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
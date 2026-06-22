#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strrchr_basic) {
  char str[] = "Hello, World!";
  int ch = 'o';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  char str[] = "Hello, World!";
  int ch = 'x';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(test_s21_strrchr_end_of_string) {
  char str[] = "Hello, World!";
  int ch = '!';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(test_s21_strrchr_null_terminator) {
  char str[] = "Hello, World!";
  int ch = '\0';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

START_TEST(test_s21_strrchr_first_character) {
  char str[] = "Hello, World!";
  int ch = 'H';
  ck_assert_ptr_eq(s21_strrchr(str, ch), strrchr(str, ch));
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strrchr");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strrchr_basic);
  tcase_add_test(tc_core, test_s21_strrchr_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_end_of_string);
  tcase_add_test(tc_core, test_s21_strrchr_null_terminator);
  tcase_add_test(tc_core, test_s21_strrchr_first_character);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_strrchr_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
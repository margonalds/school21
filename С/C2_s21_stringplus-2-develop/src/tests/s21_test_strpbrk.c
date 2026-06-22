#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strpbrk_found) {
  char str[] = "Hello, world!";
  char accept[] = "aeiou";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_not_found) {
  char str[] = "Hello, world!";
  char accept[] = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), NULL);
}
END_TEST

START_TEST(test_s21_strpbrk_first_char) {
  char str[] = "Hello, world!";
  char accept[] = "H";
  ck_assert_ptr_eq(s21_strpbrk(str, accept), str);
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strpbrk");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strpbrk_found);
  tcase_add_test(tc_core, test_s21_strpbrk_not_found);
  tcase_add_test(tc_core, test_s21_strpbrk_first_char);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *suite = s21_strpbrk_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
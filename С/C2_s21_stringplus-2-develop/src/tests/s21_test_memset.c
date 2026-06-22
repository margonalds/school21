#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memset_basic) {
  char str1[20] = "Hello, World!";
  char str2[20] = "Hello, World!";
  ck_assert_str_eq(s21_memset(str1, 'A', 5), memset(str2, 'A', 5));
}
END_TEST

START_TEST(test_s21_memset_full) {
  char str1[20] = "Hello, World!";
  char str2[20] = "Hello, World!";
  ck_assert_str_eq(s21_memset(str1, 'A', 13), memset(str2, 'A', 13));
}
END_TEST

START_TEST(test_s21_memset_partial) {
  char str1[20] = "Hello, World!";
  char str2[20] = "Hello, World!";
  ck_assert_str_eq(s21_memset(str1, 'A', 7), memset(str2, 'A', 7));
}
END_TEST

START_TEST(memset_4) {
  char str1[] = "";
  char str2[] = "";
  int ch = '\0';
  s21_size_t n = 0;
  ck_assert_str_eq(memset(str1, ch, n), s21_memset(str2, ch, n));
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memset");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memset_basic);
  tcase_add_test(tc_core, test_s21_memset_full);
  tcase_add_test(tc_core, test_s21_memset_partial);
  tcase_add_test(tc_core, memset_4);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_memset_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strncpy_basic) {
  char src[] = "Hello, World!";
  char dest[20];
  char expected[20];

  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_full_copy) {
  char src[] = "Hello";
  char dest[20];
  char expected[20];

  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_beyond_src_length) {
  char src[] = "Hello";
  char dest[20] = "1234567890123456789";
  char expected[20] = "1234567890123456789";

  strncpy(expected, src, 10);
  s21_strncpy(dest, src, 10);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncpy_with_null_bytes) {
  char src[] = "Hello\0World";
  char dest[20];
  char expected[20];

  strncpy(expected, src, 11);
  s21_strncpy(dest, src, 11);
  ck_assert_mem_eq(dest, expected, 11);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncpy");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncpy_basic);
  tcase_add_test(tc_core, test_s21_strncpy_full_copy);
  tcase_add_test(tc_core, test_s21_strncpy_beyond_src_length);
  tcase_add_test(tc_core, test_s21_strncpy_with_null_bytes);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_strncpy_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
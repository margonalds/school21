#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memcmp_equal_strings) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, World!";
  s21_size_t n = 13;

  int result_s21 = s21_memcmp(str1, str2, n);
  int result_standard = memcmp(str1, str2, n);

  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_memcmp_different_strings) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, Moon!";
  s21_size_t n = 13;

  int result_s21 = s21_memcmp(str1, str2, n);
  int result_standard = memcmp(str1, str2, n);

  ck_assert_int_eq(result_s21, result_standard);
}
END_TEST

START_TEST(test_s21_memcmp_partial_compare) {
  const char *str1 = "Hello, World!";
  const char *str2 = "Hello, Moon!";
  s21_size_t n = 6;

  int result_s21 = s21_memcmp(str1, str2, n);
  int result_standard = memcmp(str1, str2, n);

  ck_assert_int_eq(result_s21, result_standard);
}

Suite *memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memcmp_equal_strings);
  tcase_add_test(tc_core, test_s21_memcmp_different_strings);
  tcase_add_test(tc_core, test_s21_memcmp_partial_compare);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main(void) {
  Suite *suite = memcmp_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
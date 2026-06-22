#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memcpy_basic) {
  char src[] = "Hello, world!";
  char dest[50];
  ck_assert_mem_eq(s21_memcpy(dest, src, strlen(src) + 1),
                   memcpy(dest, src, strlen(src) + 1), strlen(src) + 1);
}
END_TEST

START_TEST(test_s21_memcpy_overlap) {
  char src[] = "Hello, world!";
  ck_assert_mem_eq(s21_memcpy(src + 1, src, strlen(src) - 1),
                   memcpy(src + 1, src, strlen(src) - 1), strlen(src) - 1);
}
END_TEST

START_TEST(test_s21_memcpy_empty) {
  char src[] = "";
  char dest[50];
  ck_assert_mem_eq(s21_memcpy(dest, src, strlen(src) + 1),
                   memcpy(dest, src, strlen(src) + 1), strlen(src) + 1);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memcpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memcpy_basic);
  tcase_add_test(tc_core, test_s21_memcpy_overlap);
  tcase_add_test(tc_core, test_s21_memcpy_empty);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *suite = s21_memcpy_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
#include <check.h>
#include <stdlib.h>

#include "../string_functions/s21_strncat.c"

START_TEST(test_s21_strncat_basic) {
  char dest[50] = "Hello, ";
  const char *src = "world!";
  char expected[50] = "Hello, world!";

  s21_strncat(dest, src, 6);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest[50] = "Hello, ";
  const char *src = "world!";
  char expected[50] = "Hello, wor";

  s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  char dest[50] = "Hello, ";
  const char *src = "";
  char expected[50] = "Hello, ";

  s21_strncat(dest, src, 5);
  ck_assert_str_eq(dest, expected);
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char dest[50] = "";
  const char *src = "Hello!";
  char expected[50] = "Hello!";

  s21_strncat(dest, src, 6);
  ck_assert_str_eq(dest, expected);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *suite = suite_create("s21_strncat");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncat_basic);
  tcase_add_test(tc_core, test_s21_strncat_partial);
  tcase_add_test(tc_core, test_s21_strncat_empty_src);
  tcase_add_test(tc_core, test_s21_strncat_empty_dest);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_strncat_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
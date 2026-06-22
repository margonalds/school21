#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memchr_found) {
  char str[] = "Hello, world!";
  int ch = 'o';
  size_t n = 12;
  ck_assert_ptr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_s21_memchr_not_found) {
  char str[] = "Hello, world!";
  int ch = 'x';
  size_t n = 12;
  ck_assert_ptr_eq(s21_memchr(str, ch, n), NULL);
}
END_TEST

START_TEST(test_s21_memchr_first_char) {
  char str[] = "Hello, world!";
  int ch = 'H';
  size_t n = 12;
  ck_assert_ptr_eq(s21_memchr(str, ch, n), str);
}
END_TEST

START_TEST(test_s21_memchr_last_char) {
  const char *str = "Hello, World!";
  int ch = '!';
  s21_size_t n = strlen(str);

  ck_assert_ptr_eq(s21_memchr(str, ch, n), str + strlen(str) - 1);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_memchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memchr_found);
  tcase_add_test(tc_core, test_s21_memchr_not_found);
  tcase_add_test(tc_core, test_s21_memchr_first_char);
  tcase_add_test(tc_core, test_s21_memchr_last_char);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  // Создаем набор тестов для функции s21_memchr
  Suite *suite = s21_memchr_suite();

  // Создаем запускатель тестов
  SRunner *runner = srunner_create(suite);

  // Запускаем все тесты в наборе
  srunner_run_all(runner, CK_NORMAL);

  // Получаем количество неудачных тестов
  int number_failed = srunner_ntests_failed(runner);

  // Освобождаем ресурсы, связанные с запускателем тестов
  srunner_free(runner);

  // Возвращаем 0, если все тесты прошли успешно, иначе 1
  return (number_failed == 0) ? 0 : 1;
}
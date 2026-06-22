#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  s21_size_t size1 = s21_strlen(src);
  s21_size_t size2 = s21_strlen(str);
  res = (char *)calloc(size1 + size2, sizeof(char));
  if (res != S21_NULL) {
    for (s21_size_t i = 0; i < start_index; i++) {
      res[i] = src[i];
    }
    for (s21_size_t i = start_index; i < size2 + start_index; i++) {
      res[i] = str[i - start_index];
    }
    for (s21_size_t i = size2 + start_index; i < size2 + size1; i++) {
      res[i] = src[i - size2];
    }
  }
  return (void *)res;
}
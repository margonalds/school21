#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *last_occurrence = S21_NULL;
  while (*str) {
    if (*str == (char)c) {
      last_occurrence = (char *)str;
    }
    str++;
  }
  if (c == '\0') {
    last_occurrence = (char *)str;
  }
  return last_occurrence;
}
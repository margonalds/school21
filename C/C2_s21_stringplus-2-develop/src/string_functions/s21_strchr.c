#include "../s21_string.h"

//Ищет первое вхождение символа, код которого указан в аргументе c
char* s21_strchr(const char* str, int c) {
  while (*str != '\0') {
    if (*str == (char)c) {
      return (char*)str;
    }
    str++;
  }

  if (c == '\0') {
    return (char*)str;
  }

  return S21_NULL;  // Если символ не найден, возвращаем NULL
}

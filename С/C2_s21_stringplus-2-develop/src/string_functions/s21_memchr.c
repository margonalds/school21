#include "../s21_string.h"

//Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
//байтах строки, на которую указывает аргумент str.
void* s21_memchr(const void* str, int c, s21_size_t n) {
  const unsigned char* p = str;
  unsigned char ch = (unsigned char)c;
  while (n--) {
    if (*p == ch) {
      return (void*)p;
    }
    p++;
  }
  return S21_NULL;
}

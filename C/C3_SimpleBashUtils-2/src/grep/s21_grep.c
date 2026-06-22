#include "s21_grep.h"

int main(int argc, char** argv) {
  arguments arg = argument_parser(argc, argv);
  output(arg, argc, argv);
  free(arg.pattern);
  return 0;
}

arguments argument_parser(int argc, char** argv) {
  arguments arg = {0};  // изначально заполняем нулями структуру
  int opt;  // результат парсинга
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch_func(opt, &arg, argv);
  }
  if (arg.len_pattern ==
      0) {  // в случае отсутствия e, берем ее из следующего аргумента
    if (optind < argc) {
      pattern_add(&arg, argv[optind]);
      optind++;
    }
  }
  if ((argc - optind) == 1) {
    arg.h = 1;  // реализация флага h
  }
  return arg;
}

void switch_func(int opt, arguments* arg, char** argv) {
  switch (opt) {  // сравниваем с численным значением char
    case 'e':
      arg->e = 1;
      pattern_add(arg, optarg);
      break;
    case 'i':
      arg->i = REG_ICASE;  // учет регистра независимого поиска
      break;
    case 'v':
      arg->v = 1;
      break;
    case 'c':
      arg->c = 1;
      break;
    case 'l':
      arg->c = 1;
      arg->l = 1;
      break;
    case 'n':
      arg->n = 1;
      break;
    case 'h':
      arg->h = 1;
      break;
    case 's':
      arg->s = 1;
      break;
    case 'f':
      arg->f = 1;
      add_reg_from_file(arg, optarg);
      break;
    case 'o':
      arg->o = 1;
      break;
    default:
      break;
  }
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error =
      regcomp(&re, arg.pattern,
              REG_EXTENDED | arg.i);  // если флаг не указан все будет в 0
  if (error) {
    perror("Error");
    return;
  }
  int multiple_files = (argc - optind) > 1;
  for (int i = optind; i < argc; i++) {
    process_file(arg, argv[i], &re, multiple_files);
  }
  regfree(&re);
}

void process_file(arguments arg, char* path, regex_t* re, int multiple_files) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {             //проверка открытия файла
    if (!arg.s) perror(path);  //реализация флага ы
    return;
  }
  char* line = NULL;   // хранение строки
  size_t memline = 0;  // хранение размера памяти выделенной под строку
  ssize_t read;
  int line_count = 1;  // счетчик строк в файле
  int c = 0;           // счетчик совпадений
  while ((read = getline(&line, &memline, f)) != -1) {
    if (should_print_line(arg, re, line)) {
      print_line(arg, line, re, path, line_count, multiple_files);
      c++;
    }
    line_count++;
  }
  //Если установлен флаг с и не установлен l  выводим количество совпадений
  if (arg.c && !arg.l) {
    if (multiple_files && !arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  //если устанлвлен флаг l и есть совпадения, выводим имя файла
  if (arg.l && c > 0) {
    printf("%s\n", path);
  }

  free(line);
  fclose(f);
}

int should_print_line(arguments arg, regex_t* re, char* line) {
  int result = regexec(re, line, 0, NULL, 0);
  return (result == 0 && !arg.v) || (result != 0 && arg.v);
}

void print_line(arguments arg, char* line, regex_t* re, char* path,
                int line_count, int multiple_files) {
  if (!arg.c && !arg.l) {
    if (arg.o) {
      print_match(arg, line, re, multiple_files, path);
    } else {  //печать имени файла и номера строки
      if (multiple_files && !arg.h) {
        printf("%s:", path);
      }
      if (arg.n) {
        printf("%d:", line_count);
      }
      output_line(line, strlen(line), NULL, multiple_files);
    }
  }
}

void print_match(arguments arg, char* line, regex_t* re, int multiple_files,
                 char* path) {  // реализация флага o
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    if (multiple_files && !arg.h) printf("%s:", path);  // вывод имени файла
    for (int i = offset + match.rm_so; i < offset + match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void pattern_add(arguments* arg, char* pattern) {
  int n = strlen(pattern);
  if (arg->len_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    if (arg->pattern == NULL) {  // обработка ошибки выделения памяти
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    arg->pattern[0] = '\0';  // Инициализация строки
    arg->mem_pattern = 1024;
  }
  while (arg->mem_pattern <
         (arg->len_pattern + n + 3)) {  // +3 для "()" и возможно "|"
    arg->mem_pattern *= 2;
    char* new_pattern = realloc(arg->pattern, arg->mem_pattern);
    if (new_pattern == NULL) {  // Обработка ошибки выделения памяти
      perror("realloc");
      free(arg->pattern);
      exit(EXIT_FAILURE);
    }
    arg->pattern = new_pattern;
  }
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern +=
      sprintf(arg->pattern + arg->len_pattern, "(%s)",
              pattern);  // записывает в строку и возвращает количество символов
}

void add_reg_from_file(arguments* arg, char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {  // проверка, указан ли путь до файла корректно
    if (!arg->s)
      perror(filepath);  // если не флаг s, то ошибка (флаг s подавляет ошибки)
    exit(1);
  }
  char* line = NULL;   // хранение строки
  size_t memline = 0;  // хранение размера памяти выделенной под строку
  ssize_t read;

  while ((read = getline(&line, &memline, f)) !=
         -1) {  // -1 возврат getline в конце файла
    if (line[read - 1] == '\n') line[read - 1] = '\0';  // реализация флага f
    pattern_add(arg, line);
  }
  free(line);
  fclose(f);
}

void output_line(char* line, int n, char* filename, int multiple_files) {
  if (multiple_files && filename) {
    printf("%s:", filename);
  }
  fwrite(line, sizeof(char), n, stdout);
  if (line[n - 1] != '\n') putchar('\n');
}
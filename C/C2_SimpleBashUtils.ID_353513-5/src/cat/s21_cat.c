#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, n, s, E, T, v;
} arguments;  // задаем структуру с нужными флагами

arguments argument_parser(int argc, char **argv);
void switch_func(int opt, arguments *arg);
void output(arguments *arg, char **argv);
void outline(arguments *arg, char *line, int n);
char v_output(char ch);

int main(int argc, char *argv[]) {
  arguments arg = argument_parser(
      argc, argv);  // получение значений из функции сразу в структуру
  output(&arg, argv);

  return 0;
}

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};  // изначально заполняем нулями структуру
  struct option long_options[] = {
      {"number", no_argument, NULL, 'n'},
      {"number-nonblank", no_argument, NULL, 'b'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}  // конец массива
  };
  int opt;  // результат парсинга
  while ((opt = getopt_long(argc, argv, "bneEtTsv", long_options, 0)) != -1) {
    switch_func(opt, &arg);
  }
  return arg;
}

void switch_func(int opt, arguments *arg) {
  switch (opt) {  // сравниваем с численным значением char
    case 'b':
      arg->b = 1;
      break;
    case 'n':
      arg->n = 1;
      break;
    case 's':
      arg->s = 1;
      break;
    case 'e':
      arg->E = 1;
      arg->v = 1;
      break;
    case 'E':
      arg->E = 1;
      break;
    case 't':
      arg->T = 1;
      arg->v = 1;
      break;
    case 'T':
      arg->T = 1;
      break;
    case 'v':
      arg->v = 1;
      break;
    case '?':
      perror("ERROR");
      exit(1);
      break;
    default:
      break;
  }
}

void output(arguments *arg, char **argv) {
  FILE *f = fopen(argv[optind], "r");  // открытие файла и его чтение
  char *line = NULL;                   // хранение строки
  size_t memline = 0;  // хранение размра памяти выделенной под строку
  int read = 0;        // хранения количества символов
  int empty_count = 0;  // Хранение значения ЧЕГО
  int line_count = 1;
  read = getline(&line, &memline, f);  // указатель на строку, числовое значение
                                       // выделенной памяти, ссылка на файл
  while (read != -1) {  //-1 возврат getline в конце файла
    if (line[0] == '\n') {
      empty_count++;
    } else {
      empty_count = 0;
    }
    if (arg->s && empty_count > 1) {
      // пропускаем вывод лишних строк
    } else {
      if (arg->n || arg->b) {
        if (arg->b) {
          if (line[0] != '\n') {  // реализация флага b
            printf("%6d\t", line_count);
            line_count++;
          } else if (arg->E) {
            printf("      	");
          }
        } else if (arg->n) {  // реализация флага n
          printf("%6d\t", line_count);
          line_count++;
        }
      }
      outline(arg, line, read);  // вывод на экран строки
    }
    read = getline(&line, &memline, f);
  }
  free(line);
  fclose(f);
}

void outline(arguments *arg, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t') {
      printf("^I");
    } else {
      if (arg->E && line[i] == '\n') {
        putchar('$');  // реализация флага Е
      }
      if (arg->v) {
        line[i] = v_output(line[i]);  // вызов флага V
      }
      putchar(line[i]);
    }
  }
}

char v_output(char ch) {           // реализация флага v
  if (ch == '\n' || ch == '\t') {  // исключение возврата для \n \t
    return ch;
  }
  if (ch < 0) {  // обработка отрицательных символов
    printf("M-");
    ch = ch & 0x7F;  // сделать его положительным (отбросив старший бит)
  }
  if (ch <= 31) {  // обработка управляющих символов
    putchar('^');
    ch += 64;  // добавляем 64 для отображения на экране
  } else if (ch == 127) {  // обработка DEL
    putchar('^');
    ch = '?';
  }
  return ch;
}
#ifndef S21_GREP_H
#define S21_GREP_H
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char* pattern;
  int len_pattern;
  int mem_pattern;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} arguments;

arguments argument_parser(int argc, char** argv);
void switch_func(int opt, arguments* arg, char** argv);
void output(arguments arg, int argc, char** argv);
void process_file(arguments arg, char* path, regex_t* re, int multiple_files);
int should_print_line(arguments arg, regex_t* re, char* line);
void print_line(arguments arg, char* line, regex_t* re, char* path,
                int line_count, int multiple_files);
void print_match(arguments arg, char* line, regex_t* re, int multiple_files,
                 char* path);
void pattern_add(arguments* arg, char* pattern);
void add_reg_from_file(arguments* arg, char* filepath);
void output_line(char* line, int n, char* filename, int multiple_files);

#endif
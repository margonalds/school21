#ifndef S21MATRIX
#define S21MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR_COR 1
#define ERROR_CALC 2
#define SUCCESS 1
#define FAILURE 0
#define EPS 0.0000001

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// s21_matrix
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// s21_utils
int valid_matrix(matrix_t *A);
void matrix_multiplication(matrix_t *A, matrix_t *B, matrix_t *result);
int get_dec_mat(matrix_t *A, matrix_t *result, int row, int column);
int calc_single_complement(matrix_t *A, matrix_t *result, int i, int j);

#endif  // MATRIX_H
#include "s21_matrix.h"

int valid_matrix(matrix_t *A) {
  return (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) ? 1
                                                                           : 0;
}

void matrix_multiplication(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

int get_dec_mat(matrix_t *A, matrix_t *result, int row, int column) {
  int res = OK;

  if (!valid_matrix(A) || A->rows < 2 || A->columns < 2 ||
      A->rows != A->columns) {
    return ERROR_COR;
  }

  res = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (res != OK) {
    return ERROR_CALC;
  }
  for (int i = 0, ir = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0, jr = 0; j < A->columns; j++) {
        if (j != column) {
          result->matrix[ir][jr] = A->matrix[i][j];
          jr++;
        }
      }
      ir++;
    }
  }

  return res;
}

int calc_single_complement(matrix_t *A, matrix_t *result, int i, int j) {
  int error = OK;
  double temp_err = 0;
  matrix_t temp_mat;

  error = get_dec_mat(A, &temp_mat, i, j);
  if (error == OK) {
    error = s21_determinant(&temp_mat, &temp_err);
    if (error == OK) {
      result->matrix[i][j] = ((i + j) % 2 == 0) ? temp_err : -temp_err;
    }
    s21_remove_matrix(&temp_mat);
  }
  return error;
}

#include "s21_matrix.h"

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = ERROR_COR;

  if (rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!result->matrix) {
      return ERROR_CALC;
    }

    result->columns = columns;
    result->rows = rows;

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        for (int q = 0; q < i; q++) {
          free(result->matrix[q]);
        }
        free(result->matrix);
        result->matrix = NULL;
        result->rows = 0;
        result->columns = 0;
        return ERROR_CALC;
      }
    }
    error = OK;
  }

  return error;
}

// Очистка матриц
void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->rows != B->rows ||
      A->columns != B->columns) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
        return FAILURE;
      }
    }
  }

  return SUCCESS;
}

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || !valid_matrix(B) || result == NULL) {
    error = ERROR_COR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = ERROR_CALC;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = ERROR_CALC;
  }

  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || !valid_matrix(B) || result == NULL) {
    error = ERROR_COR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = ERROR_CALC;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    error = ERROR_CALC;
  }

  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return error;
}

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || result == NULL) {
    return ERROR_COR;
  }

  error = s21_create_matrix(A->rows, A->columns, result);
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

// Перемножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || !valid_matrix(B) || result == NULL) {
    error = ERROR_COR;
  } else if (A->columns != B->rows) {
    error = ERROR_CALC;
  } else {
    error = s21_create_matrix(A->rows, B->columns, result);
    if (error == OK) {
      matrix_multiplication(A, B, result);  // Вызов функции умножения
    }
  }

  return error;
}

// Транспониирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || result == NULL) {
    return ERROR_COR;
  }
  error = s21_create_matrix(A->columns, A->rows, result);
  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (!valid_matrix(A) || A->rows != A->columns) {
    return ERROR_COR;
  }

  error = s21_create_matrix(A->rows, A->columns, result);
  if (error == OK) {
    for (int i = 0; i < A->rows && error == OK; i++) {
      for (int j = 0; j < A->columns && error == OK; j++) {
        error = calc_single_complement(A, result, i, j);
      }
    }
  }
  return error;
}

// Определитель марицы
int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  double temp_err = 0;

  if (!valid_matrix(A) || A->rows != A->columns || result == NULL) {
    return ERROR_COR;
  }

  *result = 0;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (A->rows > 2) {
    for (int i = 0; i < A->rows; i++) {
      matrix_t dMatr;
      error = get_dec_mat(A, &dMatr, 0, i);
      if (error != OK) {
        return ERROR_CALC;
      }

      error = s21_determinant(&dMatr, &temp_err);
      if (error != OK) {
        s21_remove_matrix(&dMatr);
        return ERROR_CALC;
      }

      *result += A->matrix[0][i] * pow(-1, i) * temp_err;
      s21_remove_matrix(&dMatr);
      temp_err = 0;
    }
  }

  return error;
}

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!valid_matrix(A)) {
    error = ERROR_COR;
  } else if (A->rows != A->columns) {
    error = ERROR_CALC;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0) {
      error = ERROR_CALC;
    } else {
      matrix_t alg_add;
      matrix_t trans;
      s21_calc_complements(A, &alg_add);
      s21_transpose(&alg_add, &trans);
      s21_mult_number(&trans, 1 / det, result);
      s21_remove_matrix(&alg_add);
      s21_remove_matrix(&trans);
    }
  }
  return error;
}
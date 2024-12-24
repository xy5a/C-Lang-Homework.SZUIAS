#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

#include "hw06.h"

#define CLASS1_SIZE 5
#define CLASS2_SIZE 6

void scores_input(int *scores, int size) {
  for (int i = 0; i < size; i++) {
    printf("Enter score for student %d: ", i + 1);
    scanf("%d", &scores[i]);
  }
}

void scores_print(const int *scores, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", scores[i]);
  }
  printf("\n");
}

int _score_cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

void scores_sort(int *scores, int size) {
  qsort(scores, size, sizeof(int), _score_cmp);
}

double scores_average(const int *scores, int size) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += scores[i];
  }
  return sum / size;
}

double scores_variance(const int *scores, int size) {
  double average = scores_average(scores, size);
  double variance = 0;
  for (int i = 0; i < size; i++) {
    variance += (scores[i] - average) * (scores[i] - average);
  }
  return variance / size;
}

int score_main(void) {
  int class1_scores[CLASS1_SIZE];
  int class2_scores[CLASS2_SIZE];

  printf("Enter scores for class 1:\n");
  scores_input(class1_scores, CLASS1_SIZE);

  printf("Enter scores for class 2:\n");
  scores_input(class2_scores, CLASS2_SIZE);

  scores_sort(class1_scores, CLASS1_SIZE);
  printf("Sorted scores for class 1: ");
  scores_print(class1_scores, CLASS1_SIZE);

  scores_sort(class2_scores, CLASS2_SIZE);
  printf("Sorted scores for class 2: ");
  scores_print(class2_scores, CLASS2_SIZE);

  double average1 = scores_average(class1_scores, CLASS1_SIZE);
  double variance1 = scores_variance(class1_scores, CLASS1_SIZE);
  printf("Class 1 - Average: %.2f, Variance: %.2f\n", average1, variance1);

  double average2 = scores_average(class2_scores, CLASS2_SIZE);
  double variance2 = scores_variance(class2_scores, CLASS2_SIZE);
  printf("Class 2 - Average: %.2f, Variance: %.2f\n", average2, variance2);

  return 0;
}

typedef double dtype;

enum Matrix_Error {
  MATRIX_OK,
  MATRIX_ERROR_MEMORY_ALLOCATION,
  MATRIX_ERROR_INVALID_ARGUMENT,
  MATRIX_ERROR_INVALID_DIMENSION,
};

typedef struct {
  int size[2];
  dtype *data;
} Matrix;

Matrix *matrix_new(int rows, int cols) {
  Matrix *matrix = malloc(sizeof(Matrix));
  matrix->size[0] = rows;
  matrix->size[1] = cols;
  matrix->data = malloc(sizeof(dtype) * rows * cols);
  return matrix;
}

Matrix *matrix_from_array(dtype *data, int rows, int cols) {
  Matrix *matrix = matrix_new(rows, cols);
  memcpy(matrix->data, data, sizeof(dtype) * rows * cols);
  return matrix;
}

Matrix *matrix_from_array_2d(dtype **data, int rows, int cols) {
  Matrix *matrix = matrix_new(rows, cols);
  for (int i = 0; i < rows; i++) {
    memcpy(matrix->data + i * cols, data[i], sizeof(dtype) * cols);
  }
  return matrix;
}

void matrix_free(Matrix *matrix) {
  free(matrix->data);
  free(matrix);
}

enum Matrix_Error matrix_resize(Matrix *matrix, int rows, int cols) {
  if (matrix == NULL) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  matrix->size[0] = rows;
  matrix->size[1] = cols;
  free(matrix->data);
  matrix->data = malloc(sizeof(dtype) * rows * cols);
  return MATRIX_OK;
}

enum Matrix_Error matrix_set(Matrix *matrix, int row, int col, dtype value) {
  if (matrix == NULL || row >= matrix->size[0] || col >= matrix->size[1]) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  matrix->data[row * matrix->size[1] + col] = value;
  return MATRIX_OK;
}

enum Matrix_Error matrix_get(Matrix *matrix, int row, int col, dtype *value) {
  if (matrix == NULL || row >= matrix->size[0] || col >= matrix->size[1]) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  *value = matrix->data[row * matrix->size[1] + col];
  return MATRIX_OK;
}

enum Matrix_Error matrix_mul(Matrix *matrix1, Matrix *matrix2, Matrix *result) {
  if (matrix1 == NULL || matrix2 == NULL || result == NULL) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  } else if (matrix1->size[1] != matrix2->size[0]) {
    return MATRIX_ERROR_INVALID_DIMENSION;
  } else if (matrix1->size[0] != result->size[0] ||
             matrix2->size[1] != result->size[1]) {
    result->size[0] = matrix1->size[0];
    result->size[1] = matrix2->size[1];
    free(result->data);
    result->data = malloc(sizeof(dtype) * result->size[0] * result->size[1]);
  }

  for (int i = 0; i < matrix1->size[0]; i++) {
    for (int j = 0; j < matrix2->size[1]; j++) {
      dtype sum = 0;
      for (int k = 0; k < matrix1->size[1]; k++) {
        dtype value1, value2;
        matrix_get(matrix1, i, k, &value1);
        matrix_get(matrix2, k, j, &value2);
        sum += value1 * value2;
      }
      matrix_set(result, i, j, sum);
    }
  }
  return MATRIX_OK;
}

enum Matrix_Error matrix_add(Matrix *matrix1, Matrix *matrix2, Matrix *result) {
  // will cast to the bigger matrix
  if (matrix1 == NULL || matrix2 == NULL || result == NULL) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  int rows =
      matrix1->size[0] > matrix2->size[0] ? matrix1->size[0] : matrix2->size[0];
  int cols =
      matrix1->size[1] > matrix2->size[1] ? matrix1->size[1] : matrix2->size[1];
  matrix_resize(result, rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      dtype value1 = 0, value2 = 0;
      matrix_get(matrix1, i, j, &value1);
      matrix_get(matrix2, i, j, &value2);
      matrix_set(result, i, j, value1 + value2);
    }
  }
  return MATRIX_OK;
}

enum Matrix_Error matrix_trn(Matrix *matrix, Matrix *result) {
  if (matrix == NULL || result == NULL) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  matrix_resize(result, matrix->size[1], matrix->size[0]);
  for (int i = 0; i < matrix->size[0]; i++) {
    for (int j = 0; j < matrix->size[1]; j++) {
      dtype value;
      matrix_get(matrix, i, j, &value);
      matrix_set(result, j, i, value);
    }
  }
  return MATRIX_OK;
}

bool matrix_is_symmetric(Matrix *matrix) {
  if (matrix == NULL) {
    return false;
  } else if (matrix->size[0] != matrix->size[1]) {
    return false;
  }
  for (int i = 0; i < matrix->size[0]; i++) {
    for (int j = 0; j < matrix->size[1]; j++) {
      dtype value1, value2;
      matrix_get(matrix, i, j, &value1);
      matrix_get(matrix, j, i, &value2);
      if (value1 != value2) {
        return false;
      }
    }
  }
  return true;
}

enum Matrix_Error matrix_print(Matrix *matrix) {
  if (matrix == NULL) {
    return MATRIX_ERROR_INVALID_ARGUMENT;
  }
  for (int i = 0; i < matrix->size[0]; i++) {
    for (int j = 0; j < matrix->size[1]; j++) {
      dtype value;
      matrix_get(matrix, i, j, &value);
      printf("%4.2f\t", value);
    }
    puts("");
  }
  return MATRIX_OK;
}

int matrix_test(void) {
  Matrix *matrix1, *matrix2, *result;
  double imm[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  matrix1 = matrix_from_array(imm, 3, 4);
  matrix2 = matrix_from_array(imm, 4, 3);
  result = matrix_new(3, 3);

  puts("Matrix 1");
  matrix_print(matrix1);
  puts("Matrix 2");
  matrix_print(matrix2);

  matrix_mul(matrix1, matrix2, result);
  puts("Matrix 1 * Matrix 2");
  matrix_print(result);

  matrix_add(matrix1, matrix2, result);
  puts("Matrix 1 + Matrix 2");
  matrix_print(result);
  printf("is symmetric: %s\n", matrix_is_symmetric(result) ? "true" : "false");

  matrix_trn(matrix1, result);
  puts("Matrix 1 transpose");
  matrix_print(result);

  matrix_free(matrix1);
  matrix_free(matrix2);
  matrix_free(result);

  return 0;
}

int gcd_iterative(int a, int b) {
  int gcd = 1, term = a > b ? a : b;
  for (int i = 1; i <= term; i++) {
    if (a % i == 0 && b % i == 0) {
      gcd = i;
    }
  }
  return gcd;
}

int gcd_remain(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd_remain(b, a % b);
  }
}

int gcd_recursive(int a, int b) {
  return (a == b ? a
                 : (a && b ? (a > b ? gcd_recursive(a - b, b)
                                    : gcd_recursive(a, b - a))
                           : a | b));
}

void gcd_test(void) {
  printf("gcd_iterative(12, 18) = %d\n", gcd_iterative(12, 18));
  printf("gcd_remain(12, 18) = %d\n", gcd_remain(12, 18));
  printf("gcd_recursive(12, 18) = %d\n", gcd_recursive(12, 18));
}

#ifndef MF
int main(void) {
  score_main();
  matrix_test();
  gcd_test();
  return 0;
}
#else

void hw06(int argc, char *argv[]) {
  if (argc != 1) {
    printf("Usage: %s\n", argv[0]);
    return;
  }
  score_main();
  matrix_test();
  gcd_test();
}

#endif

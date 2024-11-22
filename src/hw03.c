#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "vec.h"
#include <string.h>

int _cmp_int(void *a, void *b) { return *(int *)a - *(int *)b; }
void _print_int(void *a) { printf("%d ", *(int *)a); }

void sort_int(int argc, char **argv) {
  Vec *v = vec_new(argc);
  int desc = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--desc") == 0) {
      desc = 1;
    } else {
      int *val = malloc(sizeof(int));
      *val = atoi(argv[i]);
      vec_push(v, val);
    }
  }
  printf("unsorted list: ");
  vec_print(v, _print_int);
  v = vec_sort(v, _cmp_int);
  printf("\nsorted list: ");
  if (desc) {
    vec_print(v, _print_int);
  } else {
    vec_print(vec_reverse(v), _print_int);
  }
  printf("\n");
  vec_free(v);
}

typedef int grade_t[4];

Vec *grade = NULL;

void grade_insert(int argc, char **argv) {
  if (grade == NULL) {
    grade = vec_new(argc);
  }
  grade_t *g = malloc(sizeof(grade_t));
  for (int i = 1; i < argc && i < 5; i++) {
    (*g)[i - 1] = atoi(argv[i]);
  }
  if (argc < 5) {
    printf("info: unassigned grade are set to 0\n");
    for (int i = argc - 1; i < 4; i++) {
      (*g)[i] = 0;
    }
  }

  vec_push(grade, g);
}

void grade_print(int argc, char **argv) {
  printf("grade list: \n");
  for (size_t i = 0; i < grade->len; i++) {
    grade_t *g = vec_get(grade, i);
    printf("\t %d\t %d\t %d\t %d \n", (*g)[0], (*g)[1], (*g)[2], (*g)[3]);
  }
}

void grade_average(int argc, char **argv) {
  printf("average grade: \n");
  double sum[4] = {0};
  for (size_t i = 0; i < grade->len; i++) {
    grade_t *g = vec_get(grade, i);
    for (int j = 0; j < 4; j++) {
      sum[j] += (*g)[j];
    }
  }
  for (int i = 0; i < 4; i++) {
    printf("\t %f", sum[i] / grade->len);
  }
  printf("\n");
}

void grade_maximum(int argc, char **argv) {
  printf("maximum grade: \n");
  grade_t max = {0};
  int idx[4] = {0};
  for (size_t i = 0; i < grade->len; i++) {
    grade_t *g = vec_get(grade, i);
    for (int j = 0; j < 4; j++) {
      if (max[j] < (*g)[j]) {
        max[j] = (*g)[j];
        idx[j] = i;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    printf("course #%d:\t %d from student #%d\n", i + 1, max[i], idx[i] + 1);
  }
}

void grade_minimum(int argc, char **argv) {

  printf("minimum grade: \n");
  grade_t min = {0};
  int idx[4] = {0};
  for (size_t i = 0; i < grade->len; i++) {
    grade_t *g = vec_get(grade, i);
    for (int j = 0; j < 4; j++) {
      if (min[j] > (*g)[j]) {
        min[j] = (*g)[j];
        idx[j] = i;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    printf("course #%d:\t %d from student #%d\n", i + 1, min[i], idx[i] + 1);
  }
}

void grade_average_student(int argc, char **argv) {
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      int idx = atoi(argv[i]) - 1;
      if (idx >= 0 && idx < grade->len) {
        grade_t *g = vec_get(grade, idx);
        double sum = 0;
        for (int j = 0; j < 4; j++) {
          sum += (*g)[j];
        }
        printf("average grade of student #%d: %f\n", idx + 1, sum / 4);
      }
    }
  } else {
    for (int i = 0; i < grade->len; i++) {
      grade_t *g = vec_get(grade, i);
      double sum = 0;
      for (int j = 0; j < 4; j++) {
        sum += (*g)[j];
      }
      printf("average grade of student #%d: %f\n", i + 1, sum / 4);
    }
  }
}

void dice(int argc, char **argv) {
  srand(time(NULL));

  int dice[6] = {0};
  int count = 6000;
  for (int i = 0; i < count; i++) {
    dice[rand() % 6]++;
  }
  for (int i = 0; i < 6; i++) {
    printf("%d:\t %d, %d%%\n", i + 1, dice[i], dice[i] * 100 / count);
  }
}

void factorial(int argc, char **argv) {
  int i = 40;
  if (argc >= 2) {
    i = atoi(argv[1]);
  }

  BigInt *b = bigint_new(50);
  bigint_addi(b, 1);

  for (int j = 1; j < i; j++) {
    BigInt_muli(b, j);
  }

  printf("fatorial of %d: ", i);
  bigint_print(b);
  puts("");
}

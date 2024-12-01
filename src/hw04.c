#include "my_string.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "vec.h"
void str_compare(int argc, char *argv[]) {
  if (argc != 3) {
    return;
  }
  printf("%s vs %s\n", argv[1], argv[2]);
  printf("libc strcmp: %d\n", strcmp(argv[1], argv[2]));
  printf("my strcmp: %d\n", my_strcmp(argv[1], argv[2]));
}

int NUMBER_OF_JUDGE = 4;
Vec *scores;

void config(int argc, char *argv[]) {

  if (scores == NULL) {
    scores = vec_new(4);
  }

  if (argc != 2) {
    return;
  }
  NUMBER_OF_JUDGE = atoi(argv[1]);
  vec_clear(scores);
}

void add_score(int argc, char *argv[]) {
  if (argc != 1 + NUMBER_OF_JUDGE) {
    return;
  }
  int *score = malloc(sizeof(int) * NUMBER_OF_JUDGE + 1);
  int max = 0, min = 1000000, sum = 0;
  for (int i = 1; i < argc; i++) {
    score[i] = atoi(argv[i]);
    if (score[i] > max) {
      max = score[i];
    }
    if (score[i] < min) {
      min = score[i];
    }
    sum += score[i];
  }
  sum -= max + min;
  score[0] = sum / (NUMBER_OF_JUDGE - 2);
  vec_push(scores, score);
}

int _cmp_score(void *a, void *b) { return ((int *)a)[0] - ((int *)b)[0]; }
void _print_score(void *a) {
  int *score = (int *)a;
  printf("%d\t%d\t%d\t%d\t%d\n", score[0], score[1], score[2], score[3],
         score[4]);
}

void print_score(int argc, char *argv[]) {
  scores = vec_sort(scores, &_cmp_score);
  printf("sum\t");
  for (int i = 0; i < NUMBER_OF_JUDGE; i++) {
    printf("judge%d\t", i + 1);
  }
  puts("");
  vec_print(scores, _print_score);
}

void print_judge(int argc, char *argv[]) {
  int *sum_of_sqd = malloc(sizeof(int) * NUMBER_OF_JUDGE);
  for (size_t i = 0; i < scores->len; i++) {
    for (int j = 0; j < NUMBER_OF_JUDGE + 1; j++) {
      sum_of_sqd[j] +=
          (((int *)scores->data[i])[0] - ((int *)scores->data[i])[j + 1]) *
          (((int *)scores->data[i])[0] - ((int *)scores->data[i])[j + 1]);
    }
  }
  printf("judge: ");
  for (int i = 0; i < NUMBER_OF_JUDGE; i++) {
    printf("%d\t", i + 1);
  }
  printf("\n\t");
  for (int i = 0; i < NUMBER_OF_JUDGE; i++) {
    printf("%4.2f\t", sum_of_sqd[i] / (double)scores->len);
  }
  puts("");
}

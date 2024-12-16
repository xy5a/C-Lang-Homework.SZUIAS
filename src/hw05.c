#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hw05.h"

int isprime(int n) {
  if (n < 2)
    return 0;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0)
      return 0;
  return 1;
}

int isperfect(int n) {
  int sum = 1;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  return sum == n;
}

uint64_t factorial(int n) { return n == 0 ? 1 : n * factorial(n - 1); }

int gcd(int a, int b) {
  return (a == b ? a
                 : (a && b ? (a > b ? gcd(a - b, b) : gcd(a, b - a)) : a | b));
}

int lcm(int a, int b) { return a * b / gcd(a, b); }

bool check_answer(int n) {
  int input;
  printf("Enter answer: ");
  scanf(" %d ", &input);

  return input == n;
}

int setup_question(int upper_bound, char *_qstr) {
  int a = rand() % upper_bound + 1;
  int b = rand() % upper_bound + 1;
  int op = rand() % 4;
  char *ops = "+-*/";

  int answer = 0;
  switch (op) {
  case 0:
    answer = a + b;
    break;
  case 1:
    if (a < b) {
      a ^= b;
      b ^= a;
      a ^= b;
      // interesting...
    }
    answer = a - b;
    break;
  case 2:
    answer = a * b;
    break;
  case 3:

    answer = a * b;
    a ^= answer;
    answer ^= a;
    a ^= answer;
    // more interesting...
    break;
  }

  sprintf(_qstr, "%d %c %d", a, ops[op], b);

  return answer;
}

void question_simple(int _, char **argv) {
  srand(time(NULL));
  for (int i = 0; i < 10; i++) {
    char question[100];
    int answer = setup_question(10, question);
    printf("What is %s?\n", question);

    while (!check_answer(answer)) {
      printf("Incorrect! Try again.\n");
    }
    printf("Right!\n");
  }
}

void question_hard(int _, char **argv) {
  int score = 0;
  for (int i = 0; i < 10; i++) {
    char question[100];
    int answer = setup_question(10, question);
    printf("What is %s?\n", question);
    if (check_answer(answer)) {
      score++;
    }
  }
  printf("your score is %d\n", score);
}

#ifndef MF
int main(void) {

  int i, j;
  scanf("%d", &i);
#else
void num1(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <num>\n", argv[0]);
    return;
  }
  int i = atoi(argv[1]);
#endif
  printf("isprime(%d) = %s\n", i, isprime(i) ? "true" : "false");
  printf("isperfect(%d) = %s\n", i, isperfect(i) ? "true" : "false");
  printf("fatorial(%d) = %d\n", i, factorial(i));
#ifndef MF
  scanf("%d", &j);
#else
}
void num2(int argc, char **argv) {
  if (argc <= 3) {
    printf("Usage: %s <num1> <num2>\n", argv[0]);
    return;
  }
  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
#endif
  printf("lcm(%d, %d) = %d\n", i, j, lcm(i, j));
  printf("gcd(%d, %d) = %d\n", i, j, gcd(i, j));
#ifndef MF
  question_simple(NULL, NULL);
  question_hard(NULL, NULL);
#endif
}

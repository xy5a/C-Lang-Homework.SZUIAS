#include "hw02.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *encrypt(char *in) {
  int len = strlen(in);

  char *out = strdup(in);

  for (int i = 0; i < len; i++) {
    if (out[i] >= 'A' && out[i] <= 'Z') {

      out[i] = ((out[i] + 4 - 'A' + 26) % 26) + 'A';
    } else if (out[i] >= 'a' && out[i] <= 'z') {

      out[i] = ((out[i] + 4 - 'a' + 26) % 26) + 'a';
    }
  }

  return out;
}

char *decrypt(char *in) {
  int len = strlen(in);

  char *out = strdup(in);

  for (int i = 0; i < len; i++) {
    if (out[i] >= 'A' && out[i] <= 'Z') {

      out[i] = ((out[i] - 4 - 'A' + 26) % 26) + 'A';
    } else if (out[i] >= 'a' && out[i] <= 'z') {

      out[i] = ((out[i] - 4 - 'a' + 26) % 26) + 'a';
    }
  }

  return out;
}

int *calc_prime_under(int i) {
  _Bool *num = malloc(sizeof(_Bool) * i);

  int size = 1;
  for (int p = 2; p < (i + 1) / 2; p++) {
    if (num[p] == 1) {
      continue;
    } else {
      for (int n = p; n < i; n += p) {
        num[n] = 1;
      }
      size += 1;
    }
  }

  int *primes = malloc(sizeof(int) * size);

  primes[0] = size;
  for (int p = 2, n = 1; p < i; p++) {
    if (num[p] == 0) {
      primes[n] = p;
      n += 1;
    }
  }

  return primes;
}

void guess_number_game(void) {
  srand(time(NULL));
  int targit = rand() % 100;

  int h = 10;
  int guess;
game:

  printf("guess number: ");
  scanf(" %d", &guess);

  if (guess == targit) {
    goto success;
  } else if (guess > targit) {
    printf("%d is bigger than the targit\n", guess);
  } else {
    printf("%d is smaller than the targit\n", guess);
  }

  h--;
  if (h)
    goto game;

  printf("you failed\n");
  goto end;

success:
  printf("you successed\n");
end:
  printf("targit is %d\n", targit);
}

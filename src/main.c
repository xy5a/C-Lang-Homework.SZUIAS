#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "hw03.h"

#include "hw04.h"
#include "hw05.h"
#include "hw06.h"
void usage(void) { puts("operations: F Y P d f t 0 1 u g q"); }

void quit(int _, char **_v) {

  puts(_v[0]);
  exit(0);
}

#ifdef WIN32 // strndup is not available on Windows
char *strndup(const char *s, size_t n) {
  size_t len = strlen(s);
  if (len > n) {
    len = n;
  }
  char *result = (char *)malloc(len + 1);
  if (!result) {
    return NULL;
  }
  strncpy(result, s, len);
  result[len] = '\0';
  return result;
}
#endif

int main(void) {

  while (1) {
    printf("> ");
    int argc = 0;
    char *argv[100];
    char cache[100];
    fgets(cache, 100, stdin);
    for (size_t head = 0, tail = 0; tail < strlen(cache); tail++) {
      if (cache[tail] == ' ' || cache[tail] == '\n') {
        if (head < tail) {
          argv[argc] = strndup(cache + head, tail - head);
          argv[argc][tail - head] = '\0';
          argc++;
        }
        head = tail + 1;
      }
    }

    char *subcmd = argv[0];

    struct Cmd_s {
      char *name;
      void (*func)(int argc, char *argv[]);
    } cmds[] = {
        {"sort", sort_int},
        {"quit", quit},
        {"igrade", grade_insert},
        {"pgrade", grade_print},
        {"avgrade", grade_average},
        {"maxgrade", grade_maximum},
        {"mingrade", grade_minimum},
        {"avgsgrade", grade_average_student},
        {"dice", dice},
        {"fact", big_factorial},
        {"strcmp", str_compare},
        {"config", config},
        {"add_score", add_score},
        {"print_score", print_score},
        {"print_judge", print_judge},
        {"p1num", num1},
        {"p2num", num2},
        {"q.ez", question_simple},
        {"q.hard", question_hard},
        {"last", hw06},
    };

    for (size_t i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
      if (strcmp(subcmd, cmds[i].name) == 0) {
        cmds[i].func(argc, argv);
        break;
      }
    }
  }
}

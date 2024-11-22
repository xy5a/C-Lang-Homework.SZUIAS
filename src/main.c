#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "hw03.h"

void usage(void) { puts("operations: F Y P d f t 0 1 u g q"); }

void quit(int _, char **_v) {

  puts(_v[0]);
  exit(0);
}

int main(void) {

  while (1) {
    printf("> ");
    int argc = 0;
    char *argv[100];
    char cache[100];
    fgets(cache, 100, stdin);
    for (uint head = 0, tail = 0; tail < strlen(cache); tail++) {
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
    } cmds[] = {{"sort", sort_int},
                {"quit", quit},
                {"igrade", grade_insert},
                {"pgrade", grade_print},
                {"avgrade", grade_average},
                {"maxgrade", grade_maximum},
                {"mingrade", grade_minimum},
                {"avgsgrade", grade_average_student},
                {"dice", dice},
                {"fact", factorial}};

    for (size_t i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
      if (strcmp(subcmd, cmds[i].name) == 0) {
        cmds[i].func(argc, argv);
        break;
      }
    }
  }
}

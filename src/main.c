#include <editline/readline.h>
#include <stdio.h>

#include "read.h"
#include "types.h"

MalVar *EVAL(MalVar *expr) { return expr; }

void PRINT(MalVar *expr) { printf("%s\n", expr); }

int main(int argc, char **argv) {

  for (char *input = readline(">"); input; input = readline(">")) {

    MalVar *expr = READ(input);
    char *result = EVAL(expr);
    PRINT(result);
  }

  return 0;
}

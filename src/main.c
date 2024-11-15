#include <editline/readline.h>
#include <stdio.h>

#include "read.h"
#include "types.h"

MalVar *EVAL(MalVar *expr) { return expr; }

void PRINT(MalVar *expr) { reader_print((Reader *)(expr)); }

int main(int argc, char **argv) {

  for (char input[1000]; *input; fgets(input, sizeof(input), stdin)) {

    MalVar *expr = READ(input);
    MalVar *result = EVAL(expr);
    PRINT(result);
  }

  return 0;
}

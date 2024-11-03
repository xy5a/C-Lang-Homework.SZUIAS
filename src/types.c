#include "types.h"
#include <stdlib.h>
#include <string.h>

MalVar *mal_new_var(void) { return malloc(sizeof(MalVar)); }

MalVar *mal_new_symbol(const char *name) {
  MalVar *var = mal_new_var();
  var->type = MAL_SYM;
  char *name_str = strdup(name);
  var->var.sym = name_str;
  return var;
}
MalVar *mal_new_string(const char *str) {
  MalVar *var = mal_new_var();
  var->type = MAL_STR;
  char *_str = strdup(str);
  var->var.sym = _str;
  return var;
}

MalVar *mal_new_cons(MalVar *a, MalVar *b) {
  MalVar *var = mal_new_var();
  var->type = MAL_CONS;
  var->var.cons[0] = a;
  var->var.cons[1] = b;
  return var;
}

void mal_free(MalVar *var) {
  switch (var->type) {
  case MAL_SYM:
    free(var->var.sym);
    break;
  case MAL_STR:
    free(var->var.str);
    break;
  case MAL_CONS:
    mal_free(var->var.cons[0]);
    mal_free(var->var.cons[1]);
    break;

  case MAL_NIL:
    // early return. do nothing on nil
    return;

  default:
    break;
  }
  free(var);
}

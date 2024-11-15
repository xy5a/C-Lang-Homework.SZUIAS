#include "types.h"
#include <stdlib.h>
#include <string.h>

MalVar *mal_new_var(void) { return malloc(sizeof(MalVar)); }

static MalVar _NIL = {MAL_NIL, {0}};

MalVar *mal_nil(void) { return &_NIL; }
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

MalVar *mal_new_num(double num) {
  MalVar *var = mal_new_var();
  var->type = MAL_NUM;
  var->var.num = num;
  return var;
}

MalVar *mal_new_cons(MalVar *car, MalVar *cdr) {
  MalVar *var = mal_new_var();
  var->type = MAL_CONS;
  var->var.cons.car = car;
  var->var.cons.cdr = cdr;
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
    mal_free(var->var.cons.car);
    mal_free(var->var.cons.cdr);
    break;

  case MAL_NIL:
    // early return. do nothing on nil
    return;

  default:
    break;
  }
  free(var);
}

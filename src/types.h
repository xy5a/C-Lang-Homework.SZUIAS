#ifndef MAL_TYPES_H
#define MAL_TYPES_H
typedef enum {
  MAL_NIL = 0,
  MAL_NUM,
  MAL_STR = 0x10,
  MAL_SYM,
  MAL_CONS,
  MAL_FN,
} MalTypes;

typedef struct MalVar {
  MalTypes type;
  union {
    double num;
    char *str;
    struct MalVar *cons[2];
    struct MalVar *(*fn)(struct MalVar *);
    char *sym;
  } var;
} MalVar;

static MalVar _NIL = {MAL_NIL, {0}};

// will copy name
MalVar *mal_new_symbol(const char *);

// will copy str
MalVar *mal_new_string(const char *);

// will NOT copy a and b
MalVar *mal_new_cons(MalVar *a, MalVar *b);

MalVar *mal_new_num(double num);

void mal_free(MalVar *var);

#endif // !MAL_TYPES_H

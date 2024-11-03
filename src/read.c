#include "read.h"
#include "types.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include "pcre2.h"

MalVar read_atom(char *in) {
  char read_cache[50];
  // read string
  if (*in == '"') {
  }
}

PCRE2_SPTR8 _re_raw =
    (const unsigned char *)"([\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\.|[^\\\\\"])*"
                           "\"?|;.*|[^\\s\\[\\]{}('\"`,;)]*)";

MalVar *read_from2(const char *in) {
  MalVar *ast;
  MalVar *read_stack[50];
  read_stack[0] = &_NIL;
  ast = read_stack[0];
  int read_stack_head = 0;

  regex_t *re_code;
  regcomp(re_code, _re_raw, REG_EXTENDED);

  regmatch_t match_data[2];

  for (char *head = in; regexec(re_code, head, 2, match_data, 0) == 0;
       head += match_data[0].rm_eo) {

    char *toks = head + match_data[1].rm_so;
    int tokl = match_data[1].rm_so - match_data[1].rm_eo;

    switch (*toks) {
    // start a list
    case '(': {
      MalVar *new_cons = mal_new_cons(&_NIL, &_NIL);
      read_stack[read_stack_head] = new_cons;
      read_stack[++read_stack_head] = new_cons->var.cons[0];
    } break;

    // end a list
    case ')':
      read_stack_head--;
      break;

    // read string
    case '"':
      if (toks[tokl - 1] == '"') {
        toks[tokl - 1] = '\0';
        MalVar *new_str = mal_new_string(toks + 1);
        read_stack[read_stack_head] = new_str;

      } else {
        printf("error: unterminated string\n");
        exit(1);
      }
      break;

    default: {
      if (*toks >= '0' && *toks <= '9') {
        toks[tokl] = '\0';
        MalVar *new_num = mal_new_num(atof(toks));
        read_stack[read_stack_head] = new_num;
      }
    }

    break;
    }
  }

  return ast;
}

MalVar *read_from(const char *in) {
  MalVar *ast;
  MalVar *read_stack[50];
  read_stack[0] = &_NIL;
  ast = read_stack[0];
  int read_stack_head = 0;

  int pcre2_error_code;

  size_t pcre2_error_offset;

  pcre2_code *re_code =
      pcre2_compile(_re_raw, PCRE2_ZERO_TERMINATED, PCRE2_UTF,
                    &pcre2_error_code, &pcre2_error_offset, NULL);

  pcre2_match_data *match_data =
      pcre2_match_data_create_from_pattern(re_code, NULL);

  int head = 0, tail = strlen(in);

  while (head < tail) {
    PCRE2_UCHAR **list;
    PCRE2_SIZE *length;

    pcre2_match(re_code, in, tail, head, 0, match_data, NULL);
    pcre2_substring_list_get(match_data, &list, &length);

    PCRE2_UCHAR *token = list[1];

    switch (*token) {
    // start a list
    case '(': {
      MalVar *new_cons = mal_new_cons(&_NIL, &_NIL);
      read_stack[read_stack_head]->var.cons[0] = new_cons;
      read_stack[++read_stack_head] = new_cons;
    } break;

    // end a list
    case ')':
      break;

    // read string
    case '"':
      break;
    }

    head += length[0];
  }

  return ast;
}

MalVar *read_file(FILE *in) {
  MalVar *ast;
  MalVar *read_stack[50];
  int read_stack_head = 0;
  char read_cache[100];

  while (!feof(in)) {
    if (fscanf(in, " \"%s\" ", read_cache)) {
      // read string
      MalVar *new_str = mal_new_string(read_cache);
    }
  }
}

MalVar *READ(char *in) {}

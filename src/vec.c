#include "vec.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

Vec *vec_new(size_t cap) {
  Vec *vec = malloc(sizeof(Vec));
  vec->cap = cap;
  vec->len = 0;
  vec->data = malloc(cap * sizeof(void *));
  return vec;
}

void vec_free(Vec *vec) {
  for (size_t i = 0; i < vec->len; i++) {
    free(vec->data[i]);
  }
  free(vec->data);
  free(vec);
}

void vec_push(Vec *vec, void *item) {
  if (vec->len == vec->cap) {
    vec->cap *= 2;
    vec->data = realloc(vec->data, vec->cap * sizeof(void *));
  }
  vec->data[vec->len++] = item;
}

Vec *vec_concat(Vec *v1, Vec *v2) {
  if (v1->len + v2->len > v1->cap) {
    v1->cap = v1->len + v2->len;
    v1->data = realloc(v1->data, v1->cap * sizeof(void *));
  }
  memcpy(v1->data + v1->len, v2->data, v2->len * sizeof(void *));
  v1->len = v1->len + v2->len;
  return v1;
}

void *vec_pop(Vec *v) {
  if (v->len > 0) {
    v->len--;
    return v->data[v->len];
  } else {
    return NULL;
  }
}

void *vec_get(Vec *v, size_t i) {
  if (i < v->len) {
    return v->data[i];
  } else {
    return NULL;
  }
}

void vec_set(Vec *v, size_t i, void *item) {
  if (i < v->len) {
    v->data[i] = item;
  }
}

void vec_resize(Vec *v, size_t new_size) {
  if (v->len > new_size) {
    v->cap = v->len;
  } else {
    v->cap = new_size;
  }
  v->data = realloc(v->data, v->cap * sizeof(void *));
}

void vec_clear(Vec *v) { v->len = 0; }

Vec *vec_reverse(Vec *v) {
  Vec *new = vec_new(v->cap);
  for (size_t i = 0; i < v->len; i++) {
    vec_push(new, v->data[v->len - i - 1]);
  }
  return new;
}

void vec_print(Vec *v, void (*print)(void *)) {
  for (size_t i = 0; i < v->len; i++) {
    print(v->data[i]);
  }
}

Vec *vec_map(Vec *v, void *(*map)(void *, void *), void *arg) {
  Vec *new = vec_new(v->cap);
  for (size_t i = 0; i < v->len; i++) {
    vec_push(new, map(v->data[i], arg));
  }
  return new;
}

Vec *vec_filter(Vec *v, int (*filter)(void *, void *), void *arg) {
  Vec *new = vec_new(v->cap);
  for (size_t i = 0; i < v->len; i++) {
    if (filter(v->data[i], arg)) {
      vec_push(new, v->data[i]);
    }
  }
  return new;
}
struct _vec_sort_arg {
  int (*cmp)(void *, void *);
  void *b;
};
int _vec_sort_le(void *a, void *arg) {
  struct _vec_sort_arg *arg_ = (struct _vec_sort_arg *)arg;
  return arg_->cmp(a, arg_->b) >= 0;
}

int _vec_sort_gt(void *a, void *arg) {
  struct _vec_sort_arg *arg_ = (struct _vec_sort_arg *)arg;
  return arg_->cmp(a, arg_->b) < 0;
}

Vec *vec_sort(Vec *v, int(cmp)(void *, void *)) {
  // TODO: Change into inplace quicksort
  //
  if (v->len <= 1) {
    return v;
  }

  void *mid = vec_pop(v);
  struct _vec_sort_arg arg = {cmp, mid};

  Vec *v_le = vec_filter(v, _vec_sort_le, &arg);
  Vec *v_gt = vec_filter(v, _vec_sort_gt, &arg);

  v_le = vec_sort(v_le, cmp);
  v_gt = vec_sort(v_gt, cmp);
  vec_push(v_le, mid);

  return vec_concat(v_le, v_gt);
}

BigInt *bigint_new(size_t size) {
  BigInt *bi = malloc(sizeof(BigInt));
  bi->cap = size;
  bi->len = 1;
  bi->data = malloc(size * sizeof(uint32_t));
  bi->data[0] = 0;

  return bi;
}

void bigint_free(BigInt *bi) {
  free(bi->data);
  free(bi);
}

void bigint_print(BigInt *bi) {
  for (int i = bi->len - 1; i >= 0; i--) {
    printf("%u", bi->data[i]);
  }
}

BigInt *bigint_add(BigInt *a, BigInt *b) {
  BigInt *c = bigint_new(a->cap + b->cap);
  int carry = 0;
  for (size_t i = 0; i < a->len || i < b->len || carry; i++) {
    int64_t sum = carry;
    carry = 0;
    if (i < a->len) {
      sum += a->data[i];
    }
    if (i < b->len) {
      sum += b->data[i];
    }
    if (sum >= BIGINT_NODE_MAX) {
      sum -= BIGINT_NODE_MAX;
      carry = 1;
    }
    c->data[i] = sum;
  }
}

void bigint_addi(BigInt *v, int imm) {
  int64_t sum = 0;
  int carry = imm;
  for (size_t i = 0; i < v->len || carry; i++) {
    sum = carry;
    carry = 0;
    if (i < v->len) {
      sum += v->data[i];
    }
    if (sum >= BIGINT_NODE_MAX) {
      carry = sum / (BIGINT_NODE_MAX);
      sum = sum % (BIGINT_NODE_MAX);
    }
    if (i >= v->len) {
      v->len = i + 1;
    }
    v->data[i] = sum;
  }
}

void BigInt_muli(BigInt *v, int imm) {
  uint64_t prod = 0;
  int carry = 0;
  for (size_t i = 0; i < v->len || carry; i++) {
    prod = carry;
    carry = 0;
    if (i < v->len) {
      prod += v->data[i] * imm;
    } else {
      v->len = i + 1;
    }
    if (prod >= BIGINT_NODE_MAX) {
      carry = prod / (BIGINT_NODE_MAX);
      prod = prod % (BIGINT_NODE_MAX);
    }
    v->data[i] = prod;
  }
}
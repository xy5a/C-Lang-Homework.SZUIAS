#ifndef _VEC_H
#define _VEC_H

#include <stdint.h>
#include <stdio.h>
typedef struct {
  void **data;
  size_t len;
  size_t cap;
} Vec;

Vec *vec_new(size_t size);
void vec_free(Vec *v);
void vec_push(Vec *v, void *elem);
Vec *vec_concat(Vec *v1, Vec *v2);
void *vec_pop(Vec *v);
void *vec_get(Vec *v, size_t i);
void vec_set(Vec *v, size_t i, void *elem);
void vec_resize(Vec *v, size_t new_size);
void vec_clear(Vec *v);
Vec *vec_reverse(Vec *v);
void vec_print(Vec *v, void (*print)(void *));
Vec *vec_map(Vec *v, void *(*f)(void *, void *), void *arg);
Vec *vec_filter(Vec *v, int(f)(void *, void *), void *arg);
Vec *vec_sort(Vec *v, int(cmp)(void *, void *));

typedef struct {
  int32_t *data;
  size_t len;
  size_t cap;
} BigInt;

BigInt *bigint_new(size_t size);
void bigint_free(BigInt *v);
void bigint_addi(BigInt *v, int i);
void bigint_print(BigInt *v);
void BigInt_muli(BigInt *v, int i);
void BigInt_add(BigInt *v1, BigInt *v2);

#endif // _VEC_H

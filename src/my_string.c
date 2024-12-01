#include "my_string.h"
#include "stdlib.h"

size_t my_strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

char *my_strcpy(char *dest, const char *src) {
  size_t i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
  size_t i = 0;
  while (src[i] != '\0' && i < n) {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *my_strcat(char *dest, const char *src) {
  size_t i = 0;
  while (dest[i] != '\0') {
    i++;
  }
  my_strcpy(dest + i, src);
  return dest;
}

char *my_strncat(char *dest, const char *src, size_t n) {
  size_t i = 0;
  while (dest[i] != '\0') {
    i++;
  }
  my_strncpy(dest + i, src, n);
  return dest;
}

int my_strcmp(const char *str1, const char *str2) {
  size_t i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
    i++;
  }
  return str1[i] - str2[i];
}

int my_strncmp(const char *str1, const char *str2, size_t n) {
  size_t i = 0;
  while (str1[i] != '\0' && str2[i] != '\0' && i < n) {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
    i++;
  }
  return str1[i] - str2[i];
}

char *my_strlwr(char *str) {

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32;
    }
  }

  return str;
}

char *my_strupr(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;
    }
  }
  return str;
}

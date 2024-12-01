#ifndef _MY_STRING_H_
#define _MY_STRING_H_
#include <stdlib.h>

size_t my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t n);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strlwr(char *str);
char *my_strupr(char *str);

#ifdef REPLACE_STRING_H
#define strlen my_strlen
#define strcpy my_strcpy
#define strncpy my_strncpy
#define strcat my_strcat
#define strncat my_strncat
#define strcmp my_strcmp
#define strncmp my_strncmp
#define strlwr my_strlwr
#define strupr my_strupr

#endif

#endif /* _MY_STRING_H_ */

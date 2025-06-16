/* Write versions of the library functions strncpy, strncat, and strcncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. */
#include <stdio.h>

void strcpy_(char *s, char *t) {
  while (*s)
    s++;
  while (*s++ = *t++)
    ;
}

void strncat_(char *s, char *t, size_t n) {
  while (*s)
    s++;
  for (size_t i = 0; i < n && *t; i++)
    *s++ = *t++;
  *s = '\0';
}

int main(void) {
  char s[50] = "Can";
  char t[] = " Kocak";
  strncat_(s, t, 3);
  printf("My full name is %s\n", s);

  return 0;
}

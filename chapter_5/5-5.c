/* Write versions of the library functions strncpy, strncat, and strcncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. */
#include <stdio.h>

void strncat_(char *s, char *t, size_t n) {
  while (*s)
    s++;
  for (size_t i = 0; i < n && *t; i++)
    *s++ = *t++;
  *s = '\0';
}

void strncpy_(char *s, char *t, size_t n) {
  size_t i;

  for (i = 0; i < n && *t; i++)
    *s++ = *t++;

  for (; i < n; i++) /* t < n */
    *s++ = '\0';     /* pad the rest of s with null */
}

int strncmp_(char *s, char *t, size_t n) {
  size_t i;

  for (i = 0; i < n && (*s || *t); i++, s++, t++) {
    if (*s != *t)
      return *s - *t;
    if (*s == '\0')
      return 0;
  }

  return (i == n) ? 0 : (*s - *t);
}

int main(void) {
  char s[50] = "Can";
  char t[] = " Kocak";
  char u[50];
  char v[] = "Knight Artorias, the Abysswalker";
  char x[] = "Can", y[] = "Can";
  strncat_(s, t, 3);
  strncpy_(u, v, 55);
  printf("My full name is %s\n", s);
  printf("My favourite boss in Dark Souls is %s\n", u);

  if (!strncmp_(x, y, 10))
    printf("they are the same string\n");

  return 0;
}

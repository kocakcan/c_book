/* Write versions of the library functions strncpy, strncat, and strcncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. */
#include <assert.h>
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
  for (size_t i = 0; i < n; i++, s++, t++) {
    if (*s != *t)
      return (unsigned char)*s - (unsigned char)*t;
    if (*s == '\0')
      return 0;
  }

  return 0;
}

int main(void) {
  char s[50] = "Can";
  char t[] = " Kocak";
  char u[50];
  char v[] = "Knight Artorias, the Abysswalker";
  strncat_(s, t, 3);
  strncpy_(u, v, 55);
  printf("My full name is %s\n", s);
  printf("My favourite boss in Dark Souls is %s\n", u);

  // Exact match, n equals string length
  assert(strncmp_("hello", "hello", 5) == 0);

  // Exact match, n less than string length
  assert(strncmp_("hello", "hello", 3) == 0);

  // First string is less than second (alphabetically)
  assert(strncmp_("abc", "abd", 3) < 0);

  // First string is greater than second (alphabetically)
  assert(strncmp_("abe", "abd", 3) > 0);

  // n greater than strings, first string is shorter
  assert(strncmp_("abc", "abcde", 5) < 0);

  // n greater than strings, second string is shorter
  assert(strncmp_("abcde", "abc", 5) > 0);

  // Compare with n=0, should always return 0
  assert(strncmp_("abc", "xyz", 0) == 0);

  // First difference after n chars, so should return 0
  assert(strncmp_("abcdef", "abcxyz", 3) == 0);

  // One string empty
  assert(strncmp_("", "", 1) == 0);
  assert(strncmp_("", "a", 1) < 0);
  assert(strncmp_("a", "", 1) > 0);

  printf("All strncmp_ test cases passed!\n");

  return 0;
}

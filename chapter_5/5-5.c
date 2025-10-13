/* Write versions of the library functions strncpy, strncat, and strcncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. */
#include <assert.h>
#include <stdio.h>
#include <string.h>

char *strncat_(char *dest, const char *src, size_t count) {
  char *tmp = dest;

  while (*dest)
    dest++;
  while (count-- && *src)
    *dest++ = *src++;
  *dest = '\0';

  // if (count) {
  //   while (*dest)
  //     dest++;
  //   while ((*dest++ = *src++) != 0) {
  //     if (--count == 0) {
  //       *dest = '\0';
  //       break;
  //     }
  //   }
  // }

  return tmp;
}

char *strncpy_(char *dest, const char *src, size_t count) {
  char *tmp = dest;

  while (count--) {
    if ((*tmp = *src) != 0)
      src++;
    tmp++;
    // count--;
  }

  return dest;
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

/* best implementation imo 👌 */
int strncmp__(const char *s, const char *t, size_t n) {
  while (n--) {
    if (*s != *t)
      return (unsigned char)*s - (unsigned char)*t;
    if (*s == '\0')
      return 0;
    s++, t++;
  }

  return 0;
}

int main(void) {
  char buf[50] = "";
  const char *name = "can kocak";
  strncat_(buf, name, strlen(name));
  char u[50];
  const char v[] = "Knight Artorias, the Abysswalker";
  strncpy_(u, v, 55);
  printf("My full name is %s\n", buf);
  printf("My favourite boss in Dark Souls is %s\n", u);

  // Exact match, n equals string length
  assert(strncmp__("hello", "hello", 5) == 0);

  // Exact match, n less than string length
  assert(strncmp__("hello", "hello", 3) == 0);

  // First string is less than second (alphabetically)
  assert(strncmp__("abc", "abd", 3) < 0);

  // First string is greater than second (alphabetically)
  assert(strncmp__("abe", "abd", 3) > 0);

  // n greater than strings, first string is shorter
  assert(strncmp__("abc", "abcde", 5) < 0);

  // n greater than strings, second string is shorter
  assert(strncmp__("abcde", "abc", 5) > 0);

  // Compare with n=0, should always return 0
  assert(strncmp__("abc", "xyz", 0) == 0);

  // First difference after n chars, so should return 0
  assert(strncmp__("abcdef", "abcxyz", 3) == 0);

  // One string empty
  assert(strncmp__("", "", 1) == 0);
  assert(strncmp__("", "a", 1) < 0);
  assert(strncmp__("a", "", 1) > 0);

  printf("All strncmp__ test cases passed!\n");

  char dest[100];
  const char *temp = "Knight Artorias, the Abysswalker";

  strncpy_(dest, temp, 5);
  printf("%s\n", dest);

  return 0;
}

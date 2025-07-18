/* Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include getline, atoi,
 * itoa, and their variants, reverse, strindex and getop */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100

/* strindex: return index of t in s, -1 if none; pointer version */
int strindex_(char *s, char *t) {
  char *ps, *pt;
  int i;

  if (!*t)
    return 0;

  for (i = 0; *s; s++, i++) {
    for (ps = s, pt = t; *pt && *ps == *pt; ps++, pt++)
      ;
    if (pt > t && *pt == '\0')
      return i;
  }

  return -1;
}

/* getline__; pointer version 1 */
int getline__(char *s, int lim) {
  int i, c;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    *s++ = c;

  if (c == '\n')
    *s++ = c;

  *s = '\0';
  return i;
}

/* getline___; pointer version 2 */
int getline___(char *s, int lim) {
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
    i++;
  }
  if (c == '\n') {
    *s++ = c;
    i++;
  }
  *s = '\0';
  return i;
}

/* reverse: reverse the string s in place; pointer version */
void reverse(char *s) {
  char *left = s;
  char *right = s + strlen(s) - 1;

  char temp;
  while (left < right) {
    temp = *left, *left = *right, *right = temp;
    left++;
    right--;
  }
}

/* itoa: convert n to characters in s */
void itoa(int n, char *s) {
  int sign;
  unsigned long num;
  char *t = s;

  if ((sign = n) < 0)
    num = (unsigned int)(~n + 1); /* make it unsigned to avoid UB edge case */
  else
    num = n;

  do { /* generate digits in reverse order */
    *t++ = num % 10 + '0';
  } while ((num /= 10) > 0); /* delete it */

  if (sign < 0) {
    *t++ = '-';
  }

  *t = '\0';
  reverse(s);
}

/* atoi: convert s to integer */
int atoi_(char s[]) {
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    n = n * 10 + (s[i] - '0');

  return n;
}

/* atoi__: convert s to integer; pointer version */
int atoi__(char *s) {
  int n = 0;
  int sign;

  for (; isspace(*s); s++)
    ;

  sign = (*s == '-') ? -1 : 1;

  if (*s == '-' || *s == '+')
    s++;

  for (; *s >= '0' && *s <= '9'; s++)
    n = n * 10 + (*s - '0');

  return n * sign;
}

int main(void) {
  char *s = "Can Kocak";
  char *t = "Kocak";
  char u[] = "Prince of Persia: Warrior Within";
  int n = 1997;
  char buf[20];
  char *x = "   -1997";
  printf("I was born in %d\n", atoi__(x));

  itoa(n, buf);
  printf("buf is %s\n", buf);

  reverse(u);

  char buffer[SIZE];
  getline___(buffer, SIZE);

  printf("buffer: %s\n", buffer);
  printf("%s is at index %d in %s\n", t, strindex_(s, t), s);
  printf("%s is one of my favourite games in reverse\n", u);

  // Test 1: Substring present in the middle
  assert(strindex_("Hello, World!", "World") == 7);

  // Test 2: Substring present at the start
  assert(strindex_("Hello, World!", "Hello") == 0);

  // Test 3: Substring present at the end
  assert(strindex_("Hello, World!", "ld!") == 10);

  // Test 4: Substring not present
  assert(strindex_("Hello, World!", "cat") == -1);

  // Test 5: Empty substring (should match at index 0)
  assert(strindex_("Hello", "") == 0);

  // Test 6: Substring longer than source
  assert(strindex_("Hi", "Hello") == -1);

  // Test 7: Both strings empty (should match at index 0)
  assert(strindex_("", "") == 0);

  // Test 8: Substring is the whole string
  assert(strindex_("abc", "abc") == 0);

  // Test 9: Substring is single character present
  assert(strindex_("abcdef", "e") == 4);

  // Test 10: Substring is single character not present
  assert(strindex_("abcdef", "x") == -1);

  printf("All tests passed for strindex_!\n");

  return 0;
}

/* Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include getline, atoi,
 * itoa, and their variants, reverse, strindex and getop */
#include <assert.h>
#include <stdio.h>

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

int main(void) {
  char *s = "Can Kocak";
  char *t = "Kocak";
  printf("%s is at index %d in %s\n", t, strindex_(s, t), s);

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

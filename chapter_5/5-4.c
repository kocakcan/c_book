/* Write the function strend(s, t), which returns 1 if the string t occurs at
 * the end of the string s, and zero otherwise. */
#include <assert.h>
#include <stdio.h>

/* strend: return 1 if string t occurs at the end of string s, and 0 otherwise
 */
int strend(char *s, char *t) {
  int i = 0, j = 0;

  // Find the lengths of s and t
  while (*s) {
    s++;
    j++;
  }
  while (*t) {
    t++;
    i++;
  }

  if (j < i)
    return 0;

  // Set s and t to the start of the suffix and start of t, respectively
  s = s - i;
  t = t - i;

  while (i--) {
    if (*s++ != *t++)
      return 0;
  }
  return 1;
}

int main(void) {
  char *s = "Knight Artorias";
  char *t = "Artorias";

  if (strend(s, t))
    printf("%s appears at the end of %s\n", t, s);
  // Test 1: t is at the end of s
  assert(strend("hello world", "world") == 1);

  // Test 2: t is not at the end of s
  assert(strend("hello world", "hello") == 0);

  // Test 3: t is empty (should be considered at the end of s)
  assert(strend("hello", "") == 1);

  // Test 4: t is longer than s
  assert(strend("short", "longerstring") == 0);

  // Test 5: s and t are exactly the same
  assert(strend("same", "same") == 1);

  // Test 6: t is one character, matches last character of s
  assert(strend("test", "t") == 1);

  // Test 7: t is one character, does not match last character of s
  assert(strend("test", "e") == 0);

  // Test 8: both s and t are empty
  assert(strend("", "") == 1);

  // Test 9: s is empty, t is not
  assert(strend("", "not") == 0);

  printf("All tests passed!\n");
  return 0;
}

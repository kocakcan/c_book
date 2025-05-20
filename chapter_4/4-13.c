/* Write a recursive version of the function reverse(s), which reverses the
 * string s in place. */
#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
  int i, j, c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
}

int main(void) {
  char s[] = "Knight Artorias, the Abysswalker";
  reverse(s);
  printf("%s\n", s);

  return 0;
}

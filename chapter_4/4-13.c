/* Write a recursive version of the function reverse(s), which reverses the
 * string s in place. */
#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
  int i, j, c;
  void swap(char s[], char i, char j);

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    swap(s, i, j);
  // c = s[i], s[i] = s[j], s[j] = c;
}

void swap(char s[], char i, char j) {
  int temp;

  temp = s[i], s[i] = s[j], s[j] = temp;
}

int main(void) {
  char s[] = "Knight Artorias, the Abysswalker";
  reverse(s);
  printf("%s\n", s);

  return 0;
}

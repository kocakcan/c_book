/* Write a recursive version of the function reverse(s), which reverses the
 * string s in place. */
#include <stdio.h>
#include <string.h>

void swap(char s[], char i, char j) {
  if (i >= j)
	  return;

  int temp;

  temp = s[i], s[i] = s[j], s[j] = temp;
  swap(s, ++i, --j);
}

void reverse(char s[]) {
	swap(s, 0, strlen(s) - 1);
}

int main(void) {
  char s[] = "Knight Artorias, the Abysswalker";
  reverse(s);
  printf("%s\n", s);

  return 0;
}

/*** Write a version of itoa that accepts three arguments instead of two. The
 * third argument is a minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough. */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int j);
void reverse(char s[]);

int main() {
  int n = 155;
  char s[100];
  int j = 10;

  itoa(n, s, j);
  printf("%s\n", s);

  return 0;
}

void itoa(int n, char s[], int j) {
  int sign, i;

  if ((sign = n) < 0)
    n = -n;

  i = 0;

  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';

  while (j > i)
    s[i++] = ' ';

  s[i] = '\0';
  reverse(s);
}

void reverse(char s[]) {
  int i, j, c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

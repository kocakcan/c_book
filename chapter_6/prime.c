#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 100

int getline_(char *, int lim);

/*
 * input: n, a positive number
 * if n is a multiple of 2:
 *   if n is prime:
 *     announce: "n is 2"
 *   else:
 *     announce: "n is greater than 3"
 */

int main(void) {
  int len, input;
  char buf[MAX_INPUT];

  if ((len = getline_(buf, MAX_INPUT)) > 0) {
    if (input = atoi(buf))
      printf("Input: %d\n", input);
  }
  return 0;
}

int getline_(char *s, int lim) {
  int c, i = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    *s++ = c, i++;
  if (*s == '\n')
    *s++ = c, i++;
  *s = '\0';
  return i;
}

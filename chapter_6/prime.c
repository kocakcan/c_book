#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 100

int getline_(char *, int lim);
int isprime(int);

/*
 * input: n, a positive number
 * if n is a multiple of 2:
 *   if n is prime:
 *     announce: "n is 2"
 *   else:
 *     announce: "n is greater than 3"
 */

int main(void) {
  int len, n;
  char buf[MAX_INPUT];

  if ((len = getline_(buf, MAX_INPUT)) > 0) {
    if ((n = atoi(buf)) % 2 == 0) {
      if (isprime(n))
        printf("n is indeed 2\n");
      else
        printf("n is greater than 3\n");
    }
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

int isprime(int n) {
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;

  for (int i = 3; i * i <= n; i += 2)
    if (n % i == 0)
      return 0;
  return 1;
}

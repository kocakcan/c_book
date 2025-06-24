// The while and for loops test the termination condition at the top. By
// contrast, the third loop in C, the do-while, tests at the bottom after
// making each pass through the loop body, the body is always executed at least
// once.

/***
 *   The syntax of the do is
 *   do
 *     statement
 *   while (expression);
 *
 * - The statement is executed, then expression is evaluated, If it is true,
 *   statement is evaluated again, and so on. When the expression becomes false,
 *   the loop terminates. Except for the sense of the test, do-while is
 *   equivalent to Pascal repeat-until statement.
 *
 * - Experience shows that do-while is much less used than while and for.
 *   Nonetheless, from time to time it is valuable, as in the following
 *   function itoa, which converts a number to a character string (the inverse
 *   of atoi).
 */
#include <limits.h>
#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
  int i, j, c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
  int i, sign;
  unsigned long num;

  if ((sign = n) < 0)             /* record sign */
    num = (unsigned int)(~n + 1); /* make it unsigned to avoid UB edge case */

  i = 0;

  do {                       /* generate digits in reverse order */
    s[i++] = num % 10 + '0'; /* get next digit */
  } while ((num /= 10) > 0); /* delete it */

  if (sign < 0) {
    s[i++] = '-';
  }

  s[i] = '\0';
  reverse(s);
}

int main() {
  int n = INT_MIN;
  char s[100];

  itoa(n, s);

  printf("%s\n", s);

  return 0;
}

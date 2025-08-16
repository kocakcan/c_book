/* Write the program tail, which prints the last n lines of its input. By
 * default, n is set to 10, let us say, but it can be changed by an optional
 * argument so that
 *
 *   tail -n
 * prints the last n lines. The program should behave rationally no matter
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program, not in a two-dimensional array of fixed size.
 */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_NUMBER 10

int getline_(char *s, int lim) {
  int c, i = 0;

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

void writelines(char **input, size_t nlines) {
  while (nlines--)
    printf("%s\n", *input++);
}

char *input[10];
char **ip = input;

int main(int argc, char *argv[]) {
  int n = DEFAULT_NUMBER;

  char *s = "can kocak";
  char *t = "seyfi kocak";
  char *u = "dilan kocak";
  char *v = "leyli kocak";
  char *z = "medet kocak";

  *ip++ = s;
  *ip++ = t;
  *ip++ = u;
  *ip++ = v;
  *ip++ = z;

  if (--argc > 0 && (*++argv)[0] == '-')
    n = atoi(*(argv) + 1);

writelines(input, n);

  return 0;
}

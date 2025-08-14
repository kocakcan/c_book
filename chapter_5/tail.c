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

int main(int argc, char *argv[]) {
  printf("2nd arg string: %s\n", *++argv);

  return 0;
}

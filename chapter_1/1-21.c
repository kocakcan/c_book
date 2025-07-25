#include <stdio.h>
#define TABSTOP 8

int main(void) {
  int c;           /* current char read */
  int pos = 1;     /* initial pos */
  int nspaces = 0; /* accumulated spaces */

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++nspaces;
      if ((pos % TABSTOP) == 0) {
        putchar('\t'); /* replace the spaces accumulated with a tab */
        nspaces = 0;
      }
      ++pos;
    } else {
      while (nspaces > 0) {
        putchar(' ');
        --nspaces;
      }

      putchar(c); /* print the current char */

      if (c == '\n') {
        pos = 1;
        nspaces = 0;
      } else if (c == '\t') {
        pos +=
            (TABSTOP - ((pos - 1) % TABSTOP)); /* move to the next tab stop */
      } else {
        ++pos;
      }
    }
  }

  while (nspaces > 0) {
    putchar(' ');
    --nspaces;
  }

  return 0;
}

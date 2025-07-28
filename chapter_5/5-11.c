/* Modify the program entab and detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#define TABSTOP 8

int main(int argc, char *argv[]) {
  int c, nspaces = 0, pos = 1;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++nspaces;
      if (pos % TABSTOP == 0) {
        putchar('\t');
        nspaces = 0;
      }
      ++pos;
    } else {
      while (nspaces > 0) {
        putchar(' ');
        nspaces--;
      }

      putchar(c);

      if (c == '\n') {
        pos = 1;
        nspaces = 0;
      } else if (c == '\t') {
        pos += (TABSTOP - ((pos - 1) % TABSTOP));
      } else
        pos++;
    }
  }

  while (nspaces--)
    putchar(' ');
}

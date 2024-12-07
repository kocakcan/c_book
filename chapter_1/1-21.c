#include <stdio.h>
#define TABSTOP 8

int main(void) {
  int c;
  int pos = 1;
  int nspaces = 0, ntabs = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (pos % TABSTOP != 0) {
        ++nspaces;
      } else {
        nspaces = 0;
        ++ntabs;
      }
    } else {
      for (int i = 0; i < ntabs; ++i)
        putchar('\t');
      ntabs = 0;

      if (c == '\t') {
        nspaces = 0;
        pos += (TABSTOP - (pos - 1) % TABSTOP) - 1;
      }

      for (int i = 0; i < nspaces; ++i)
        putchar(' ');
      nspaces = 0;

      putchar(c);

      if (c == '\n') {
        pos = 0;
      }
    }
    ++pos;
  }
}

/* Modify the program entab and detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TABSTOP 8
#define MAX_TABS 100

int main(int argc, char *argv[]) {
  int c, nspaces = 0, pos = 1;
  int tabstops[MAX_TABS];
  int *tp = tabstops;
  int current_tabstop;

  if (argc > 1) {
    while (--argc > 0 && tp - tabstops < MAX_TABS)
      *tp++ = atoi(*++argv);
  } else
    *tp++ = DEFAULT_TABSTOP;

  while ((c = getchar()) != EOF) {
    current_tabstop = (tp == tabstops) ? DEFAULT_TABSTOP : *(tp - 1);
    if (c == ' ') {
      ++nspaces;
      for (int *t = tabstops; t < tp; ++t) {
        if (pos == *t) {
          putchar('\t');
          nspaces = 0;
          break;
        }
      }
      ++pos;
    } else {
      while (nspaces > 0) {
        putchar(' ');
        nspaces--;
      }

      putchar(c);

      if (c == '\n')
        pos = 1;
      else
        pos++;
    }
  }

  while (nspaces--)
    putchar(' ');

  return 0;
}

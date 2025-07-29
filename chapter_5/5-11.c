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
      // tabstops[ntabs++] = atoi(*++argv);
      *tp++ = atoi(*++argv);
  } else
    *tp++ = DEFAULT_TABSTOP;

  int *copy = tp;

  while ((c = getchar()) != EOF) {
    // current_tabstop = tabstops[ntabs - 1];
    current_tabstop = *--tp;
    if (c == ' ') {
      ++nspaces;
      // for (int i = 0; i < ntabs; ++i) {
      for (int i = 0; i < copy - tabstops; ++i) {
        if (pos == tabstops[i]) {
          printf("[TAB]");
          nspaces = 0;
          break;
        }
      }
      ++pos;
    } else {
      while (nspaces > 0) {
        // putchar(' ');
        printf("[SPACE]");
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
    // putchar(' ');
    printf("[SPACE]");

  return 0;
}

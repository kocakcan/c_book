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
  int *index = tabstops;
  int current_tabstop = *index;

  if (argc > 1) {
    while (--argc > 0 && tp - tabstops < MAX_TABS)
      *tp++ = atoi(*++argv);
  } else
    *tp++ = DEFAULT_TABSTOP;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++nspaces;
      if (pos == current_tabstop) {
        // putchar('\t');
        printf("[TAB]");
        nspaces = 0;
        index++;
        current_tabstop = (index - tabstops < MAX_TABS)
                              ? *index
                              : current_tabstop + DEFAULT_TABSTOP;
      }
      ++pos;
    } else {
      while (nspaces > 0) {
        // putchar(' ');
        printf("[SPACE]");
        nspaces--;
      }

      putchar(c);

      if (c == '\n') {
        pos = 1;
        index = tabstops;
        current_tabstop = *index;
      } else
        pos++;
    }
  }

  while (nspaces--)
    putchar(' ');

  return 0;
}

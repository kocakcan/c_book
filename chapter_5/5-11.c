/* Modify the program entab and detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TABSTOP 8
#define MAX_TABS 100

int main(int argc, char *argv[]) {
  int c, nspaces = 0, pos = 1;
  int ntabs = 0;
  int tabstops[MAX_TABS];
  int current_tabstop;

  if (argc > 1) {
    while (--argc > 0 && ntabs < MAX_TABS)
      tabstops[ntabs++] = atoi(*++argv);
  } else
    tabstops[ntabs++] = DEFAULT_TABSTOP;

  while ((c = getchar()) != EOF) {
    current_tabstop = tabstops[ntabs - 1];
    if (c == ' ') {
      ++nspaces;
      for (int i = 0; i < ntabs; ++i) {
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

/* Modify the program detab to accept a list of tab stops as arguments. Use the
 * default tab settings if there are no arguments.
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_TABS 100
#define DEFAULT_TABSTOP 8

int main(int argc, char *argv[]) {
  int c, pos = 1;
  int tabstops[MAX_TABS];
  int *tp = tabstops;
  int current_tabstop;

  if (argc > 1)
    while (--argc > 0 && tp - tabstops < MAX_TABS)
      *tp++ = atoi(*++argv);
  else
    *tp++ = DEFAULT_TABSTOP;

  while ((c = getchar()) != EOF) {
    current_tabstop = (tp == tabstops) ? DEFAULT_TABSTOP : *(tp - 1);
    if (c == '\t') {
      for (int *t = tabstops; t < tp; ++t) {
        if (pos == *t) {
          printf("[TAB]");
          break;
        }
      }
      ++pos;
    } else {
      putchar(c);

      if (c == '\n')
        pos = 1;
      else
        pos++;
    }
  }

  return 0;
}

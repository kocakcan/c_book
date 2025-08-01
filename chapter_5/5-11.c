/* Modify the program entab and detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TABSTOP 8
#define MAX_TABS 100

/* next_tab: returns next tabstop after (or at) current position */
int next_tab(int pos, int *tabstops, int ntabs) {
  for (int i = 0; i < ntabs; i++)
    if (pos < tabstops[i])
      return tabstops[i];
  // beyond specified tabs, use default intervals
  int last = ntabs > 0 ? tabstops[ntabs - 1] : DEFAULT_TABSTOP;
  int offset = (pos - last) % DEFAULT_TABSTOP;
  return pos + (DEFAULT_TABSTOP - offset);
}

int main(int argc, char *argv[]) {
  int tabstops[MAX_TABS];
  int ntabs = 0;

  if (argc > 1) {
    for (int i = 1; i < argc && ntabs < MAX_TABS; ++i)
      tabstops[ntabs++] = atoi(argv[i]);
  } else {
    tabstops[0] = DEFAULT_TABSTOP;
    ntabs = 1;
  }

  int pos = 1, nspaces = 0, c;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++nspaces;
    else {
      while (nspaces > 0) {
        int next = next_tab(pos, tabstops, ntabs);
        if (pos + nspaces >= next) {
          // putchar('\t');
          printf("[TAB]");
          nspaces -= (next - pos);
          pos = next;
        } else {
          // putchar(' ');
          printf("[SPACE]");
          --nspaces;
          ++pos;
        }
      }

      putchar(c);
      if (c == '\n')
        pos = 1;
      else
        ++pos;
    }
  }

  // on EOF
  while (nspaces > 0) {
    int next = next_tab(pos, tabstops, ntabs);
    if (pos + nspaces >= next) {
      // putchar('\t');
      printf("[TAB]");
      nspaces -= (next - pos);
      pos = next;
    } else {
      // putchar(' ');
      printf("[SPACE]");
      --nspaces;
      ++pos;
    }
  }

  return 0;
}

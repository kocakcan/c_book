/* Modify the program entab and detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TABSTOP 8
#define MAX_TABS 100

int tabstops[MAX_TABS];
int *tp = tabstops;

/* next_tab: returns next tabstop after (or at) current position */
int next_tab(int pos, int *tabstops) {
  for (int *temp = tabstops; temp < tp; ++temp)
    if (pos < *temp)
      return *temp;
  int last = (tp - tabstops > 0) ? *(tp - 1) : DEFAULT_TABSTOP;
  int offset = (pos - last) % DEFAULT_TABSTOP;
  return pos + (DEFAULT_TABSTOP - offset);
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    while (--argc > 0 && tp - tabstops < MAX_TABS)
      *tp++ = atoi(*++argv);
  } else {
    *tp++ = DEFAULT_TABSTOP;
  }

  int pos = 1, c;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int next = next_tab(pos, tabstops);
      for (; pos < next; ++pos)
        printf("[SPACE]");
    } else {

      putchar(c);
      if (c == '\n')
        pos = 1;
      else
        ++pos;
    }
  }

  return 0;
}

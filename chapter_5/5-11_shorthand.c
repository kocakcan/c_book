/* Extend entab and detab to accept the shorthand
 *
 *   entab -m +n
 *  to mean tab stops every n columns, starting at column m. Choose convenient
 *  (for the user) default behaviour. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_EVERY_COL 8
#define DEFAULT_INIT_POS 1

int next_tab(int pos, int init_pos, int every_col) {
  int tab_width = (pos < init_pos) ? DEFAULT_EVERY_COL : every_col;
  int distance = tab_width - (pos - 1) % tab_width;

  return (distance > 0) ? distance : tab_width;
}

int main(int argc, char *argv[]) {
  int c, init_pos = DEFAULT_INIT_POS, every_col = DEFAULT_EVERY_COL;
  int nspaces = 0, pos = 1;

  while (--argc > 0) {
    char *arg = *++argv;
    if (*arg == '-' && *(arg + 1) != '\0') {
      int val = atoi(arg + 1);
      if (val > 0)
        init_pos = val;
    } else if (*arg == '+' && *(arg + 1) != '\0') {
      int val = atoi(arg + 1);
      if (val > 0)
        every_col = val;
    } else {
      printf("error: unknown argument %c\n", *arg);
      return 1;
    }
  }

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++nspaces;
    else {
      while (nspaces > 0) {
        int next = next_tab(pos, init_pos, every_col);
        if (nspaces >= next) {
          printf("[TAB]");
          nspaces -= next;
          pos += next;
        } else {
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

  while (nspaces--)
    printf("[SPACE]");

  return 0;
}

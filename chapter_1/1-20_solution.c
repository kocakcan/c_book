/*
 *   Write a program detab that replaces tabs in the input with the proper
 *   number of blanks to space to the next tab stop. Assume a fixed set of tab
 *   stops, say every n columns. Should n be a variable or a symbolic parameter?
 */
#include <stdio.h>
#define TABSTOP 8

int main(void) {
  int c, nspaces;
  int pos = 1;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      nspaces = TABSTOP - (pos - 1) % TABSTOP;
      while (nspaces--) {
        printf("[SPACE]");
        ++pos;
      }
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

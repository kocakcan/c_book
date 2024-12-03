/*
 *   Write a program detab that replaces tabs in the input with the proper
 *   number of blanks to space to the next tab stop. Assume a fixed set of tab
 *   stops, say every n columns. Should n be a variable or a symbolic parameter?
 */
#include <stdio.h>
#define TABSTOP 4

int main(void) {
  int c, nblanks;
  int position = 1;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      nblanks = TABSTOP - (position - 1) % TABSTOP;
      for (int i = 0; i < nblanks; ++i) {
        putchar(' ');
        ++position;
      }
    } else if (c == '\n') {
      putchar(c);
      position = 1;
    } else {
      putchar(c);
      ++position;
    }
  }
}

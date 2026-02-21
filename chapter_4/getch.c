#include <stdio.h>
#define BUFSIZE 100

// External variables
static char buf[BUFSIZE];
static char *bufp = buf;

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (c == EOF)
    return;
  if (bufp - buf >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}

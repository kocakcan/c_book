#include "calc.h"
#include <ctype.h>

// TODO: Write a pointer version of getop
int getop(char *s) {
  int c;
  static int last_ch = 0;

  c = (last_ch) ? last_ch : getch();
  last_ch = 0;

  while (c == ' ' || c == '\t')
    c = getch();

  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  if (c == '-') {
    last_ch = getch();
    if (!isdigit(last_ch) && last_ch != '.')
      return '-';
    *s++ = '-';
    c = last_ch;
    last_ch = 0;
  }

  *s++ = c;

  if (isdigit(c)) {
    while (isdigit(*s++ = c = getch()))
      ;
  }

  if (c == '.') {
    while (isdigit(*s++ = c = getch()))
      ;
  }

  *s = '\0';
  return NUMBER;
}

#include "calc.h"
#include <ctype.h>

int getop(char s[]) {
  int i = 0;
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
    s[i++] = '-';
    c = last_ch;
    last_ch = 0;
  }

  s[i++] = c;

  if (isdigit(c)) {
    while (isdigit(s[i++] = c = getch()))
      ;
  }

  if (c == '.') {
    while (isdigit(s[i++] = c = getch()))
      ;
  }

  s[i] = '\0';
  return NUMBER;
}

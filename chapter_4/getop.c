#include "calc.h"
#include <ctype.h>
#include <stdio.h>

// int getop(char s[]) {
//   int i = 0, c, next;
//
//   while ((s[0] = c = getch()) == ' ' || c == '\t')
//     ;
//
//   s[1] = '\0';
//   if (!isdigit(c) && c != '.' && c != '-')
//     return c;
//   if (c == '-') {
//     next = getch();
//     if (!isdigit(next) && next != '.') {
//       ungetch(next);
//       return c;
//     }
//     s[++i] = c = next;
//   }
//   if (isdigit(c)) {
//     while (isdigit(s[++i] = c = getch()))
//       ;
//   }
//   if (c == '.') {
//     while (isdigit(s[++i] = c = getch()))
//       ;
//   }
//   s[i] = '\0';
//   if (c != EOF)
//     ungetch(c);
//   return NUMBER;
// }

int getop(char s[]) {
  static int last_ch = 0;
  int i = 0;
  int c;

  c = (last_ch != 0) ? last_ch : getch();
  last_ch = 0;

  while (s[0] == ' ' || s[0] == '\t') {
    s[0] = c;
    c = getch();
  }

  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }

  if (c == '-') {
    last_ch = getch();
    if (!isdigit(last_ch) && last_ch != '.') {
      return '-';
    }
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

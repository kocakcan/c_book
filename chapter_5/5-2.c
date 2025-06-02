/* Write getloat, the floating-point analog of getint. What type does getfloat
 * return as its function value? */
#include <ctype.h>
#include <stdio.h>

extern int getch(void);
extern void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    // take a peek at the next character
    if (!isdigit(c = getch())) {
      ungetch(c);    /* it is not a number */
      ungetch(sign); /* push back the sign as well */
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

/* getfloat: get next float from input into *pf */
float getfloat(float *pf) {
  // TODO: Implement this function
  float val, power;
  int c, sign;

  while (isspace(c = getch()))
    ;
}

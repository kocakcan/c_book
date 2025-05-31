/* As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on input. */
#include <ctype.h>
#include <stdio.h>

extern int getch(void);
extern void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch()))	/* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); 		/* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
	  // take a peek at the next character
	  if (!isdigit(c = getch())) {
	    ungetch(c);		/* it is not a number */
	    ungetch(sign);	/* push back the sign as well */
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

int main(void) {
	int n, array[10];

	for (n = 0; n < 10 && getint(&array[n]) != EOF; n++)
		;

	printf("Here's your array\n");

	for (n = 0; n < 10; n++)
		printf("%d\n", array[n]);
	putchar('\n');

	return 0;
}

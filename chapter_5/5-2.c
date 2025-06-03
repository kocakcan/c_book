/* Write getloat, the floating-point analog of getint. What type does getfloat
 * return as its function value? */
#include <ctype.h>
#include <stdio.h>

extern int getch(void);
extern void ungetch(int);

/* getfloat: get next float from input into *pf */
int getfloat(float *pf) {
	int c, sign;
	float power;
	
	while (isspace(c = getch()))
		;

	if (!isdigit(c) && c != '+' && c != '-' && c != '.' && c != EOF) {
		ungetch(c);
		return 0;
	}

	sign = 1;
	if (c == '+' || c == '-') {
		int next = getch();
		if (!isdigit(next) && next != '.') {
			ungetch(next);
			ungetch(c);
			return 0;
		}
		sign = (c == '-') ? -1 : 1;
		c = next;
	}

	*pf = 0.0;
	while (isdigit(c)) {
		*pf = 10.0 * *pf + (c - '0');
		c = getch();
	}

	power = 1.0;
	if (c == '.') {
		c = getch();
		while (isdigit(c)) {
			*pf = 10.0 * *pf + (c - '0');
			power *= 10;
			c = getch();
		}
	}

	*pf = sign * *pf / power;

	if (c != EOF)
		ungetch(c);

	return 1;
}

int main(void) {
  int n;
  float array[10];

  for (n = 0; n < 10 && getfloat(&array[n]) != EOF; n++)
    ;

  printf("Here's your array\n");

  for (n = 0; n < 10; n++)
    printf("%.1f\n", array[n]);
  putchar('\n');

  return 0;
}

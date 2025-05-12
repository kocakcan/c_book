#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
	int i = 0, c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	if (c == '-') {
		next = getch();
		if (!isdigit(next) && next != '.') {
			ungetch(next);
			return c;
		}
		s[++i] = c = next;
	}
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch()))
				;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()))
				;
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

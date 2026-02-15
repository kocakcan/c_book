#include <stdio.h>
#include <ctype.h>

int strcmp_(const char *, const char *);

int main(int argc, char *argv[]) {
	int c;

	if (strcmp_("./lower", argv[0]) == 0)
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (strcmp_("./upper", argv[0]) == 0)
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	else
		while ((c = getchar()) != EOF)
			putchar(c);
	return 0;
}

int strcmp_(const char *s, const char *t) {
	while (*s && *s == *t)
		s++, t++;
	return (unsigned char)*s - (unsigned char)*t;
}

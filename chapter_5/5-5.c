/* Write versions of the library functions strncpy, strncat, and strcncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s, t, n) copies at most n characters of t to s. */
#include <stdio.h>

void strcpy_(char *s, char *t) {
	while (*s)
		s++;
	while (*s++ = *t++)
		;
}

int main(void) {
	char s[50] = "Can";
	char t[] = " Kocak";
	strcpy_(s, t);
	printf("My full name is %s\n", s);

	return 0;
}

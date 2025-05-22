/* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine. */
#include <stdio.h>
#include <limits.h>

/*** Actual flow for the call itoa(123, s, 0):
 *
 * itoa(1, s, 0) writes '1' at s[0], returning 1
 * itoa(12, s, 0) receives i = 1, writes '2' at s[1], returning 2
 * itoa(123, s, 0) receives i = 2, writes '3' at s[2], returning 3
 *
 * Each recursive call waits at this line:
 *
 * if (n / 10)
 * 	i = itoa(n / 10, s, i);
 */
int utoa(unsigned int n, char s[], int i) {
	if (n / 10)
		i = utoa(n / 10, s, i);

	s[i++] = n % 10 + '0';
	s[i] = '\0';
	return i;
}

int itoa(int n, char s[], int i) {
	if (n < 0) {
		s[i++] = '-';
		return utoa((unsigned int)(~n + 1), s, i);
	}

	return utoa((unsigned int)n, s, i);
}

void itoa_wrapper(int n, char s[]) {
	itoa(n, s, 0);
}

int main(void) {
	char s[20];
	itoa_wrapper(INT_MIN, s);
	int x = 1530, y = -3150;
	printf("%s\n", s);

	itoa_wrapper(INT_MAX, s);
	printf("%s\n", s);

	itoa_wrapper(x, s);
	printf("%s\n", s);

	itoa_wrapper(y, s);
	printf("%s\n", s);

	return 0;
}

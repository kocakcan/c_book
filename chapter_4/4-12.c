/* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine. */
#include <stdio.h>

void itoa(int n, char s[]) {
	static int i, sign;

	if ((sign = n) < 0)
		n = -n;

	i = 0;

	// do {
		// s[i++] = n % 10 + '0';
	// } while ((n /= 10) > 0);
	
	if (n / 10)
		itoa(n / 10, s);
	s[i++] = n % 10 + '0';

	// TODO: sign is not processed properly
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	// reverse(s);
}

int main(void) {
	char s[10];
	int n = -1923;
	itoa(n, s);
	printf("%s\n", s);

	return 0;
}

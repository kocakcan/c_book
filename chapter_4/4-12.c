/* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine. */
#include <stdio.h>

void itoa(int n, char s[]) {
	// Need not initialize i as it is static
	// it will be initialized to zero by default
	static int i;
	int sign;

	if ((sign = n) < 0)
		n = -n;

	if (sign < 0)
		s[i++] = '-';

	// do {
		// s[i++] = n % 10 + '0';
	// } while ((n /= 10) > 0);
	
	if (n / 10)
		itoa(n / 10, s);
	s[i++] = n % 10 + '0';

	s[i] = '\0';
	// reverse(s);
}

int main(void) {
	char s[10];
	int n = -1965;
	itoa(n, s);
	printf("%s\n", s);

	return 0;
}

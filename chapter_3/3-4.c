/* In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not. Modify it to print that value correctly, regardless of the machines on which it runs. */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, char *argv[]) {
	int n = INT_MIN;
	char s[100];

	itoa(n, s);

	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[]) {
	int i, sign;
	unsigned int num;	

	if ((sign = n) < 0) {
		// n = -n; wouldn't work as you can't represent positive version
		// of INT_MIN, it would overflow.
		// To avoid this, we can cast the integer to an unsigned integer type.
		num = (unsigned int)(~n + 1);
	} else {
		num = n;
	}

	i = 0;

	do {
		s[i++] = num % 10 + '0';
	} while ((num /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	int i, j, c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

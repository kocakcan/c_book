/* Write the function itob(n, s, b) that converts the integer n into a base b character representation in the string s. In particular, itob(n, s, 16) formats s as a hexadecimal integer in s. */
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(int argc, char *argv[]) {
	int n = 0xabcff;
	char s[100];

	itob(n, s, 8);
	printf("%s\n", s);

	return 0;
}

void itob(int n, char s[], int b) {
	int i, sign;
	char digits[] = "0123456789abcdef";

	if ((sign = n) < 0)
		n = -n;

	i = 0;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) != 0);

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

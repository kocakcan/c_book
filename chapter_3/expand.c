/***
 * Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters for either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 */
#include <stdio.h>

int main() {
	char s[50];

	// Given a-z,
	// a would be 97 and z would be 122
	char x[] = "a-z";
	char y[100];

	int c = 33;

	printf("%d\n", 'a' - '2');
	printf("%c\n", c);

	// should print out a
	// printf("%d\n", x[0]);

	// 97
	printf("%d\n", x[0]);
	
	for (int i = x[0]; i < x[2] + 1; i++)
		y[i - x[0]] = i;

	// for (int i = x[0]; i < x[2] + 1; i++)
		// printf("%c", y[i - x[0]]);
		
	printf("%s\n", y);

	return 0;
}

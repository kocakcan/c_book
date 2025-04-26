/*** Extend atof to handle scientific notation of the form
 * 	
 * 	123.45e-6
 *   where a floating-point number may be followed by a e or E and optionally
 *   signed exponent. */
#include <stdio.h>
#include <ctype.h>

double atof(char s[]) {
	int i, sign;
	double val, power;

	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '-' || s[i] == '+')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = val * 10 + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = val * 10 + (s[i] - '0');
		power *= 10;
	}

	return sign * val / power;
}

int main(void) {
	double x = 123.456e-6;
	char s[] = " -14.532";
	printf("%e\n", x);
	printf("%.3f\n", atof(s));
}

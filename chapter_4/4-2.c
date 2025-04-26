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

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		int exp_sign = (s[i] == '-') ? -1 : 1;
		i++;
		// subtracting s[i] from '0' is essential here otherwise
		// s[i] would be the numeric value of the current character
		for (int j = 1; j <= (s[i] - '0'); j++)
			power *= 10;
		// power *= exp_sign;
	}
	return sign * val / power;
}

int main(void) {
	char x[] = "123.456e-6";
	char y[] = " -123.45";
	double scientific = 123.456e-6;
	char s[] = " -14.532";
	printf("%e\n", atof(x));
	printf("%.2f\n", atof(y));
	printf("%e\n", scientific);
}

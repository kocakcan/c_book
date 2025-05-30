/***
 * 4.2 Functions Returning Non-integers
 *
 * - Many numerical functions like sqrt, sin, and cos return double; other
 *   specialized functions return other types.
 * - To illustrate how to deal with this, let's write and use the function
 *   atof(s), which converts the string s to its double-precision
 *   floating-point equivalent. atof is an extension of atoi. It handles an
 *   optional sign and decimal point, and the presence or absence of either
 *   part or fractional part. The standard library includes an atof; the header
 *   <stdlib.h> declares it. */

// First, atof itself must declare the type of value it returns, since it is
// not int. The type name precedes the function name:
#include <ctype.h>
#include <stdio.h>

/* atof: convert string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign;

  for (i = 0; isspace(s[i]); i++)
    ; /* skip white space */

  sign = (s[i] == '-') ? -1 : 1; /* record sign */
  if (s[i] == '+' || s[i] == '-')
    i++; /* skip sign */

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++; /* skip dot sign */

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  return sign * val / power; /* perform some magic */
}

/***
 * - Second, just as important, the calling routine must know that atof returns
 *   a non-int value. One way to ensure this is to declare atof explicitly in
 *   the calling routine. The declaration is shown in this primitive calculator
 *   (barely adequate for check-book balancing), which reads one number per
 *   line, optionally preceeded with a sign, and adds them up, printing the
 *   running sum after each input:
 *
 *   #include <stdio.h>
 *   #define MAXLINE	1000
 *
 *   main()
 *   {
 *   	double sum, atof(char []);
 *   	char line[MAXLINE];
 *   	int getline(char line[], int max);
 *
 *   	sum = 0;
 *   	while (getline(line, MAXLINE) > 0)
 *   		printf("\t%g\n", sum += atof(line));
 *
 *   	return 0;
 *   }
 *
 *   The declaration
 * 	    double sum, atof(char []);
 *   says that sum is a double variable, and that atof is a function that takes
 *   one char[] argument and returns a double.
 *
 * - The function atof must be declared and defined consistenly. If atof itself
 *   and the call to it in main have inconsistent types in the same source
 *   file, the error will be detected by the compiler. But if (as is more
 *   likely) atof were compiled seperately, the mismatch would not be detected,
 *   atof would return a double that main would treat as an int, and
 *   meaningless answers would result.
 *
 * - In the light of what we have said about how declarations must match
 *   definitions, this might seem surprising. The reason a mismatch can happen
 *   is that if there is no function prototype, a function is implicitly
 *   declared by its first appearance in an expression, such as
 *
 *   	  sum += atof(line)
 *   If a name that has not been previously declared occurs in an expression
 *   and is followed by a left parantheses, it is declared by context to be a
 *   function name, the function is assumed to return an int, and nothing is
 *   assumed about its arguments. Furthermore, if a function declaration does
 *   not include arguments, as in
 *
 *   	  double atof();
 *   that too is taken to mean that nothing is to be assumed about the
 *   arguments of atof; all parameter checking is turned off. This special
 *   meaning of the empty argument list is intended to permit older C programs
 *   to compile with new compilers. But it's a bad idea to use it with new C
 *   programs. If the function takes arguments, declare them; if it takes no
 *   arguments, use void.
 *
 * - Given atof, properly declared, we could write atoi(convert a string to
 *   int) in terms of it:
 *
 *	int atoi(char s[])
 *	{
 *		double atof(char s[]);
 *		return (int) atof(s);
 *	}
 * - Notice the structure of the declarations and the return statement. The
 *   value of the expression in
 *   	return expression;
 *   is converted to the type of the function before the return is taken.
 *   Therefore, the value of atof, a double, is converted automatically to int
 *   when it appears in this return, since the function atoi returns an int.
 *   This operation potentionally discard information, however, so some
 *   compilers warn of it. The cast states explicitly that the operation is
 *   intended, and suppresses any warning.
 */

int atoi(char s[]) {
  double atof(char s[]);

  return (int)atof(s);
}

// This is how functions with no arguments must be declared
// Otherwise, the parameter checking is turned off
void func_with_no_args(void) {
  printf("Since this function takes in no parameters void is used in the "
         "arguments list.\n");
}

int main() {
  double atof(char[]);

  char s[] = " 	3.14";
  char z[] = "	-14.69";

  printf("%.2f\n", atof(s));
  printf("%d\n", atoi(z));

  return 0;
}

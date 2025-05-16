/***
 * 4.8 Block Structure
 *
 * C is not a block-structured language in the sense of Pascal or similar
 * languages, because functions may not be defined within other functions. On
 * the other hand, variables can be defined in a block-structured fashion
 * within a function. Declaration of variables (including initializations) may
 * follow the left brace that introduces any compound statement, not just one
 * that begins a function. Variables declared in this way hide any identically
 * named variables in outer blocks, and remain in existence until the matching
 * right brace. For example, in
 *
 * 	if (n > 0) {
 * 		int i;	-> declare new i
 *
 * 		for (i = 0; i < n; i++)
 * 			...
 * 	}
 *
 * the scope of the variable i is the "true" branch of the if; this i is
 * unrelated to any i outside the block. An automatic variable declared and
 * initialized in a block is initialized each time the block is entered.
 *
 * Automatic variables, including formal parameters, also hide external
 * variables and functions of the same name. Given the declarations
 *
 * 	int x;
 * 	int y;
 *
 * 	f(double x)
 * 	{
 * 		double y;
 * 	}
 *
 * then within the function f, occurrences of x refer to the parameter, which
 * is a double; outside f, they refer to the external int. The same is true of
 * the variable y.
 *
 * As a matter of style, it's best to avoid variable names that conceal names
 * in an outer scope; the potential for confusion and error is too great. */
#include <stdio.h>

// External variables
int x = 19;
int y = 97;

double f(double x) {
	double y = .5;

	printf("This x is internal variable/formal parameter -> %.1f\n", x);

	return x + y;
}

int main(void) {
	printf("This x is external one -> %d\n", x);
	printf("This y is external one -> %d\n", y);
	double y = .3;
	printf("The result is: %.1f\n", f(y));

	for (int i = 0; i < 100; i++) {
		// x will be declared and initialized each time this block is
		// entered.
		int x = 10;
		// unlike x, y will only be initialized once as it is a static
		// variable.
		static int y = 50;
		printf("x is %d\n", x);
		printf("y is %d\n", y);
	}

	return 0;
}

/***
 * 4.9 Initialization
 *
 * In the absence of explicit initialization, external and static variables are
 * guaranteed to be initialized to zero; automatic and register variables have
 * undefined (i.e., garbage) initial values.
 *
 * Scalar variables may be initialized when they are defined, by following the
 * name with an equals sign and an expression.
 *
 * 	int x = 1;
 * 	char squota = '\'';
 * 	long day = 1000L * 60L * 60L * 24L; -> milliseconds/day
 *
 * For external and static variables, the initializer must be a constant
 * expression; the initialization is done once, conceptionally before the
 * program begins execution. For automatic and register variables, the
 * initializer is not restricted to being a constant; it may be any expression
 * involving previously defined values, even function calls. For example, the
 * initialization of the binary search program could be written as
 *
 * 	int binsearch(int x, int v[], int n)
 * 	{
 * 		int low = 0;
 * 		int high = n - 1;
 * 		int mid;
 * 	}
 *
 * instead of
 *
 * 	int low, high, mid;
 *
 * 	low = 0;
 * 	high = n - 1;
 *
 * In effect, initialization of automatic variables are just shorthand for
 * assignment statements. Which form to prefer is largely a matter of taste.
 *
 * An array may be initialized by following its declaration with a list of
 * initializers enclosed in braces and seperated by commas. For example, to
 * initialize an array days with the number of days in each month:
 *
 * 	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
 *
 * When the size of the array is omitted, the compiler will compute the length
 * by counting the initializers, of which there are 12 in this case.
 *
 * If there are fewer initializers for an array than the specified size, the
 * others will be zero for external, static and automatic variables. It is an
 * error to have too many initializers. There is no way to specify repetition
 * of an initializer, nor to initialize an element in the middle of the array
 * without supplying all the preeceding values as well.
 *
 * Character arrays are a special case of initialization; a string may be used
 * instead of braces and commas notation:
 *
 * 	char pattern = "ould";
 * is a shorthand for the longer but equivalent
 * 	char pattern[] = { 'o', 'u', 'l', 'd', '\0' };
 *
 * In this case, the array size is five (four character plus the terminating
 * '\0').
 */
#include <stdio.h>

// External variable
long day = 1000L * 60L * 60L * 24L;

// Static variable (Internal static variable)
int give_ext(void) {
	static int x;

	return x;
}

int give_number(int x) {
	return x;
}
// This wouldn't compile as one can't assign dynamic expression to
// external/static variables
// int faulty_variable = give_number(5);

int main(void) {
	printf("day is an external variable and it is initialized to: %ld\n", day);
	printf("x is an internal static variable with no explicit initializer, meaning it will be initialized to 0 by default: %d\n", give_ext());

	int auto_variable;
	register int reg_variable;

	printf("These will contain garbage values as they are automatic and register variables respectively. %d %d\n", auto_variable, reg_variable);

	// Specified less initializers than the array size, meaning the other
	// values will be zero
	int numbers[10] = { 0, 1, 3 };

	for (int i = 0; i < 10; i++)
		printf("%d\n", numbers[i]);
	printf("\n");

	return 0;
}

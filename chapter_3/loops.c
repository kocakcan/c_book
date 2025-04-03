/***
 *   while (expression)
 *     statement
 *
 * - In the while loop, the expression is evaluated. If it is non-zero,
 *   statement is executed and expression is re-evaluated. This cycle continues
 *   until expression becomes zero, at which point execution resumes after
 *   statement.
 *
 * - The for statement
 *
 *   for (expr1; expr2; expr3)
 *     statement
 *
 *   is equivalent to
 *
 *   expr1;
 *   while (expr2) {
 *     statement
 *     expr3;
 *   }
 *
 *   except for the behaviour of continue.
 *
 * - Grammatically, the three components of a for loop are expressions.
 * - Most commonly, expr1 and expr3 are assignments or function calls and expr2
 *   is a relational expression.
 * - Any of the three parts can be omitted, although the semicolons must remain.
 * - If expr1 or expr3 is omitted, it is simply dropped from the expansion.
 * - If the test, expr2, is not present, it is taken as permanently true, so
 *
 *   for (;;) {
 *     ...
 *   }
 *
 *   is an "infinite" loop, presumably to be broken by other means, such as
 *   break and return.
 *
 * - Whether to use while or for is largely a matter of personal preference. For
 *   example. in
 *
 *     while ((c = getchar()) == ' ' || c == '\n' || c == '\t')
 *       ; // skip white space characters
 *
 *   there is no initialization or re-initialization, so the while is most
 *   natural.
 *
 * - The for is preferable when there is a simple initialization and increment
 *   since it keeps the loop control statements close together and visible at
 *   the top of the loop. This is most obvious in
 *
 *     for (i = 0; i < n; i++)
 *
 *   which is the C idiom for processing the first n elements of an array.
 *
 * - Because the components of the for are arbitrary expressions, for loops are
 *   not restricted to arithmetic progressions. Nonetheless, it is a bad style
 *   to force unrelated computations into the initialization and increment of a
 *   for, which are better reserved for loop control operations.
 *
 * - As a larger example, here is another version of atoi for converting a
 *   string to its numeric equivalent.
 *
 * - The structure of the program reflects the form of the input
 *
 *   skip white space, if any
 *   get sign, if any
 *   get integer part and convert it
 *
 * - Each step does its part, and leaves thing in a clean state for the next.
 *   The whole process terminates on the first character that could not be part
 *   of a number.
 */
#include <ctype.h>
#include <stdio.h>

/* atoi: convert s to integer; version 2 */
int atoi(char s[]) {
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++)	// skip white spaces
		;

	sign = (s[i] == '-') ? -1 : 1;	// get sign

	if (s[i] == '+' || s[i] == '-')	// skip sign
		i++;

	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');

	return n * sign;
}

/***
 * - The advantages of keeping loop control centralized are even more obvious when there are several nested loops.
 * - The following function is a Shell sort for sorting an array of integers.
 * - The basic idea of this sorting algorithm, which was invented in 1959 by D. L. Shell, is that in early stages, far-apart elements are compared, rather than adjacent ones as in simpler interchange sorts.
 * - This tends to eliminate large amounts of disorder quickly. so later stages have less work to do. The interval between compared elements is gradually decreased to one, at which point the sort effectively becomes an adjacent interchange method.
 */

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n) {
	int gap, i, j, temp;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
}

/***
 * - There are three nested loops. The outermost controls the gap between compared elements, shrinking it from n/2 by a factor of two each pass until it becomes zero. The middle loop steps along the elements. The innermost loop compares each pair of elements that is seperated by gap and reverses any that are out of order.
 * - Since gap is eventually reduced to one, all elements are eventually ordered correctly.
 * - Notice how the generally of the for makes the outer loop fit in the same form as the others, even though it is not an arithmetic progression.
 * - One final C operator is the comma ",", which most often finds use in the for statement.
 * - A pair of expressions seperated by a comma is evaluated left to right, and the type and value of the result are the type and value of the right operand.
 * - Thus in a for statement, it is possible to place multiple expressions in the various parts, for example to process two indices in parallel.
 */

/***
 * - The commas that seperate function arguments, variables in declarations, etc., are not comma operators, and do not guarantee left to right evaluation.
 * - Comma operators should be used sparingly. The most suitable uses are for constructs strongly related to each other, as in the for loop in reverse, and in macros where a multistep computation has to be a single expression.
 * - A comma expression might also be appropriate for the exchange of elements in reverse, where the exchange can be brought of a single operation:
 *   for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
 *   	c = s[i], s[i] = s[j], s[j] = c;
 */

int main() {
	char s[] = "-1997";
	int arr[] = {1, 3, 5, 2, -10, 7, 9, 4};
	int size = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n");

	shellsort(arr, size);

	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n");
	
	printf("%d\n", atoi(s));
	// TODO: I'm onto something here
	char buffer[50];

	for (int i = 65; i < 91; i++)
		buffer[65 - i] = i;

	for (int i = 65; i < 91; i++)
		printf("%c", buffer[65 - i]);
	printf("\n");

	return 0;
}

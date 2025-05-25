/* Define a macro swap(t, x, y) that interchanges two arguments of type t.
 * (Block structure will help) */
#include <stdio.h>
#define swap(t, x, y)	{t = x, x = y, y = t;}

int main(void) {
	// int t, x = 10, y = 30;
	// char t, x = 'a', y = 'b';
	double t, x = .5, y = 3.14;
	swap(t, x, y)
	// printf("x: %d, y: %d\n", x, y);
	// printf("x: %c, y: %c\n", x, y);
	printf("x: %g, y: %g\n", x, y);

	return 0;
}

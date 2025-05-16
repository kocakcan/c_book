/***
 * 4.7 Register Variables
 *
 * A register declaration advises the compiler that the variable in question
 * will be heavily used. The idea is that register variables are to be placed
 * in machine registers, which may result in smaller and faster programs. But
 * compilers are free to ignore the advice.
 *
 * The register declaration looks like
 *
 * 	register int x;
 * 	register char c;
 *
 * and so on. The register declaration can only be applied to automatic
 * variables and to the formal parameters of a function. In this later case, it
 * looks like
 *
 * 	f(register unsigned m, register long n)
 * 	{
 * 		register int i;
 * 		...
 * 	}
 *
 * In practice, there are restrictions on register variables, reflecting the
 * realities of underlying hardware. Only a few variables in each function may
 * be kept in registers, and only certain types are allowed. Excess register
 * declarations are harmless, however, since the word register is ignored for
 * excess or disallowed declarations. And it is not possible to take the
 * address of a register variable, regardless of whether the variable is
 * actually placed in a register. The specific restrictions on number and type
 * of register variables vary from machine to machine. */
#include <stdio.h>

int sum(register int x, register int y) {
	return x + y;
}

int main(void) {
	int x[1000];
	int y[1000];

	for (int i = 0; i < 1000; i++) {
		x[i] = i;
		y[i] = i + i * 3;
	}

	for (int i = 0; i < 1000; i++)	
		printf("%d + %d = %d\n", x[i], y[i], sum(x[i], y[i]));

	return 0;
}

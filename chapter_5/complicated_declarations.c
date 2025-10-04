/***
 * 5.12 Complicated Declarations
 *
 * C is sometimes castigated for the syntax of its declarations, particularly ones that involve pointers to functions. The syntax is an attempt to make the declaration and the use agree; it works well for simple cases, but it can be confusing for the harder ones, because declarations cannot be read left to right, and because parantheses are over-used. The difference between
 *
 * 	int *f();	f: function returning pointer to int
 *	int (*pf)();	pf: pointer to function returning int
 * illustrates the problem: * is a prefix operator and it has lower precedence than (), so parantheses are necessary to force the proper association.
 *
 * Although truly complicated declarations rarely arise in practice, it is important to know how to understand them, and, if necessary, how to create them. One good way to synthesize declarations is in small steps with typedef. As an alternative, in this section we will present a pair of programs that convert from valid C to a word description and back again. The word description reads left to right.
 *
 * The first, dcl, is the more complex. It converts a C declaration into a word description, as in these examples:
 *
 * char **argv
 * 	argv: pointer to pointer to char
 * int (*daytab)[13]
 * 	daytab: pointer to array[13] of int
 * int *daytab[13]
 * 	daytab: array[13] of pointer to int
 * void *comp()
 * 	comp: function returning pointer to void
 * char (*(*x())[])()
 * 	x: function returning pointer to array[] of
 * 	pointer to function returning char
 * char (*(*x[3])())[5]
 * 	x: array[3] of pointer to function returning
 * 	pointer to array[5] of char
 * dcl is based on the grammar that specifies a declarator.
 */

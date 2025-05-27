/***
 * Chapter 5 - Pointers and Arrays
 *
 * A pointer is a variable that contains the address of a variable. Pointers
 * are much used in C, partly because they are sometimes the only way to
 * express a computation, and partly because they usually lead to more compact
 * and efficient code than can be obtained in other ways. Pointers and arrays
 * are closely related; this chapter also explores this relationship and shows
 * how to exploit it.
 *
 * Pointers have been lumped with the goto statement as a marvelous way to
 * create impossible-to-understand programs. This is certainly true when they
 * are used carelessly, and it is easy to create pointers that point somewhere
 * unexpected. With discipline, however, pointers can also be used to achieve
 * clarity and simplicity.
 *
 * In ANSI C, the type void * (pointer to void) replaces char * (pointer to
 * char) as the proper type for a generic pointer.
 *
 * 5.1 Pointers and Addresses
 *
 * A typical machine has an array of consecutively numbered or addressed memory
 * cells that may be manipulated individually or in contiguous groups. One
 * common situation is that any byte can be a char, a pair of one-byte cells
 * can be treated as a short integer, and four adjacent bytes form a long. A
 * pointer is a group of cells (often two or four) that can hold an address.
 *
 * The unary operator & gives the address of an object, so the statement
 *
 *  p = &c;
 * assigns the address of c to the variable p, and p is said to "point to" c.
 * The & operator only applies to objects in memory, variables and array
 * elements. It cannot be applied to expressions, constants, or register
 * variables.
 *
 * The unary operator * is the indirection or dereferencing operator; when
 * applied to a pointer, it accesses the object the pointer points to. Suppose
 * that x and y are integers and ip is a pointer to int. This artificial
 * sequence shows how to declare a pointer and how to use & and *:
 *
 *  int x = 1, y = 2, z[10];
 *  int *ip;                  -> ip is a pointer to int
 *  ip = &x;                  -> ip now points to x
 *  y = *ip;                  -> y is now 1
 *  *ip = 0;                  -> x is now 0
 *  ip = &z[0];               -> ip now points to z[0]
 * The declaration of the pointer ip,
 *
 *  int *ip;
 * is intended as a mnemonic; it says the expression *ip is an int. The syntax
 * of the declaration for a variable mimics the syntax of expressions in which
 * the variable might appear. This reasoning applies to function declarations
 * as well. For example,
 *
 *  double *dp, atof(char *);
 * says that in an expression *dp and atof(s) have values of double, and that
 * argument of atof is a pointer to char.
 *
 * You should also note the implication that a pointer is constrained to point
 * to a particular kind of object: every pointer points to a specific data
 * type. (There is one exception: a "pointer to void" is used to hold any type
 * of pointer but cannot be dereferenced itself.)
 *
 * If ip points to the integer x, then *ip can occur in any context where x
 * could, so
 *
 *  *ip = *ip + 10;
 * increments *ip by 10.
 *
 * The unary operators * and & bind more tightly than arithmetic operators, so
 * the assignment
 *
 *  y = *ip + 1
 * takes whatever ip points at, adds 1, and assigns the result to y, while
 *
 *  *ip += 1
 * increments what ip points to, as do
 *
 *  ++*ip
 * and
 *
 *  (*ip)++
 * The parantheses are necessary in this last example; without them, the
 * expression would increment ip instead of what ip points to, because unary
 * operators like * and ++ associate right to left.
 *
 * Finally, since pointers are variables, they can be used without
 * dereferencing. For example, if iq is another pointer to int,
 *
 *  iq = ip
 * copies the contents of ip into iq, thus making iq point to whatever ip
 * pointed to.
 */

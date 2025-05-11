/***
 * 4.4 Scope Rules
 *
 * The functions and external variables that make up a C program need not all
 * be compiled at the same time; the source text of the program may be kept in
 * several files, and previously compiled routines may be loaded from
 * libraries. Among the questions of interest are
 * 	- How are declarations written so that variables are properly declared
 * 	during compilation?
 * 	- How are declarations arranged so that all the pieces will be properly
 * 	connected when the program is loaded?
 * 	- How are declarations organized so there is only one copy?
 * 	- How are external variables initialized?
 *
 * The scope of a name is the part of the program within which the name can be
 * used. For an automatic variable declared at the beginning of a function, the
 * scope is the function in which the name is declared. Local variables of the
 * same name in different functions are unrelated. The same is true of the
 * parameters of the function, which are in effect local variables.
 *
 * The scope of an external variable or a function lasts from the point at
 * which it is declared to the end of the file being compiled. For example, if
 * main, sp, val, push, and pop are defined in one file, in the order shown
 * above, that is,
 * 	main() { ... }
 * 	int sp = 0;
 * 	double val[MAXVAL];
 *
 * 	void push(double f) { ... }
 * 	double pop(void) { ... }
 * then the variables sp and val may be used in push and pop simply by naming
 * them; no further declarations are needed. But these names are not visible in
 * main, nor are push and pop themselves.
 * TODO: Continue from this point
 */

/***
 * 4.6 Static Variables
 *
 * The variables sp and val in stack.c, and buf and bufp in getch.c, are for
 * private use of the functions in their respective source files, and are not
 * meant to be accessed by anything else. The static declaration, applied to an
 * external variable or function, limits the scope of that object to the rest of
 * the source file being compiled. External static thus provides a way to hide
 * names like buf and bufp in the getch-ungetch combination, which must be
 * external so they can be shared, yet which should not be visible to users of
 * getch and ungetch.
 *
 * Static storage is specified by prefixing the normal declaration with the word
 * static. If the two routines and the two variables are compiled in one file,
 * as in
 *
 *   static char buf[BUFSIZE]; -> buffer for ungetch
 *   static int bufp = 0;      -> next free position in buf
 *
 *   int getch(void) { ... }
 *
 *   void ungetch(int c) { ... }
 *
 * then no other routine will be able to access buf and bufp, and those names
 * will not conflict with the same names in other files of the same program. In
 * the same way, the variables that push and pop for stack manipulation can be
 * hidden, by declaring sp and val to be static.
 *
 * The external static declaration is most often used for variables, but it can
 * be applied to functions as well. Normally, function names are global, visible
 * to any part of the entire program. If a function is declared static, however,
 * its name is invisible outside of the file in which it is declared.
 *
 * The static declaration can also be applied to internal variables. Internal
 * static variables are local to a particular function just as automatic
 * variables are, but unlike automatics, they remain in existence rather than
 * coming and going each time the function is activated. This means that
 * internal static variables provide private, permanent storage within a single
 * function.
 */

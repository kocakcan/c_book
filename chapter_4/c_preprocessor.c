/***
 * 4.11 The C Preprocessor
 *
 * C provides certain language facilities by means of a preprocessor, which is
 * conceptually a seperate step in compilation. The two most frequently used
 * features are #include, to include the contents of a file during compilation,
 * and #define, to replace a token by an arbitrary sequence of characters.
 * Other features described in this section include conditional compilation and
 * macros with arguments.
 *
 * 4.11.1 File Inclusion
 *
 * File inclusion makes it easy to handle collection of #defines and
 * declarations (among other things). Any source line of the form
 * 	#include "filename"
 * or
 * 	#include <filename>
 * is replaced by the contents of the filename. If the filename is quoted,
 * searching for the file typically begins where the source program was found;
 * if it is not there, or the name is enclosed in < and >, searching follows an
 * implementation-defined rule to find the file. An included file may itself
 * contain #include lines.
 *
 * There are often several #include lines at the beginning of a source file, to
 * include common #define statements and extern declarations, or to access the
 * function prototype declarations for library functions from headers like
 * <stdio.h>. (Strictly speaking, these need not be files; the details of how
 * headers are accessed are implementation-dependent.)
 *
 * #include is the preferred way to tie the declarations together for a large
 * program. It guarantees that all the source files will be supplied with the
 * same definitions and variable declarations, and thus eliminates a
 * particularly nasty kind of bug. Naturally, when an included file is changed,
 * all files that depend on it must be recompiled.
 *
 * 4.11.2 Macro Substitution
 *
 * A definition has the form
 *
 * 	#define name replacement text
 * It calls for a macro substitution of the simplest kind - subsequent
 * occurrences of the token name will be replaced by the replacement text. The
 * name in a #define has the same form as a variable name; the replacement text
 * is arbitrary. Normally the replacement text is the rest of the line, but a
 * long definition may be continued onto several lines by placing a \ at the
 * end of each line to be continued. The scope of a name defined with #define
 * is from its point of definition to the end of the source file being
 * compiled. A definition may use previous definitions. Substitutions are made
 * only for tokens, and do not take place within quoted strings. For example,
 * if YES is a defined name, there would be no substitution in printf("YES") or
 * in YESMAN.
 *
 * Any name may be defined with any replacement text. For example
 * 	
 * 	#define forever	for (;;) -> infinite loop
 * defines a new word, forever, for an infinite loop.
 *
 * It is also possible to define macros with arguments, so the replacement text
 * can be different for different calls of the macro. As an example, define a
 * macro called max:
 *
 * 	#define max(A, B)	((A) > (B) ? (A) : (B))
 * Although it looks like a function call, a use of max expands into in-line
 * code. Each occurrence of a formal parameter (here A or B) will be replaced
 * by the corresponding actual argument. Thus the line
 *
 * 	x = max(p+q, r+s);
 * will be replaced by the line
 *
 * 	x = ((p+q) > (r+s) ? (p+q) : (r+s));
 * So long as the arguments are treated consistently, this macro will serve for
 * any data type; there is no need for different kinds of max for different
 * data types, as there would be with functions. If you examine the expansion
 * of max, you will notice some pitfalls. The expressions are evaluated twice;
 * this is bad if the involve side effects like increment operators or input
 * and ouput. For instance
 *
 * 	max(i++, j++) -> WRONG
 * will increment the larger twice. Some care also has to be taken with
 * parantheses to make sure the order of evaluation is preserved; consider what
 * happens when the macro
 *
 * 	#define square(x)	x * x -> WRONG
 * is invoked as square(z + 1).
 *
 * TODO: Continue from this point
 * Nonetheless, macros are valuable.
 */
#include <stdio.h>
#define NAME	"Can"
#define SURNAME	" Kocak"
#define FULLNAME	NAME SURNAME
#define forever	for (;;)
#define square(x)	(x) * (x)

int main(void) {
	printf("My full name is %s\n", FULLNAME);
	int x = 19;
	// forever
	// 	printf("What's going on?\n");
	printf("20 squared is: %d\n", square(19 + 1));

	return 0;
}

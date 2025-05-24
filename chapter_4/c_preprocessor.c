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
 */

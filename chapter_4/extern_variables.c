/***
 * 4.3 External Variables
 *
 * - A C program consists of a set of external objects, which are either
 *   variables or functions. The adjective "external" is used in contrast to
 *   "internal", which describes the arguments and variables defined inside
 *   functions. External variables are defined outside of any function, and are
 *   thus potentionally available to many functions. Functions themselves are
 *   always external, because C does not allow functions to be defined inside
 *   other functions. By default, external variables and functions have the
 *   property that all references to them by the same name, even from functions
 *   compiled seperately, are references to the same thing. (The standard calls
 *   this property external linkage.) Because external variables are globally
 *   accessible, they provide an alternative to function arguments and return
 *   values for communicating data between functions. Any function may access
 *   an external variable by referring to it by name, if the name has been
 *   declared somehow.
 *
 * - If a large number of variables must be shared among functions, external
 *   variables are more convenient and efficient than long argument lists.
 *   However, this reasoning should be applied with some caution, for it can
 *   have a bad effect on program structure, and lead to programs with too many
 *   data connections between functions.
 *
 * - External variables are also useful because of their greater scope and
 *   lifetime. Automatic variables are internal to function; they come into
 *   existence when the function is entered, and disappear when it is left.
 *   External variables, on the other hand, are permanent, so they can retain
 *   values from one function invocation to the next. Thus if two functions
 *   must share some data, yet neither calls the other, it is often most
 *   convenient if the shared data is kept in external variables rather than
 *   being passed in and out via arguments.
 *
 * - The problem is to write a calculator program that provides the operators
 *   +, -, *, /. Because it is easier to implement, the calculator will use
 *   reverse Polish notation instead of infix. (Reverse Polish notation is used
 *   by some pocket calculators, and in languages like Forth and Postscript.)
 *
 * - In reverse Polish notation, each operator follows its operands; an infix
 *   expression like
 *   	(1 - 2) * (4 + 5)
 *   is entered as
 *   	1 2 - 4 5 + *
 *   Parantheses are not needed; the notation is unambiguous as long as we know
 *   how many operands each operator expects.
 *
 * - The implementation is simple. Each operand is pushed onto a stack, when an
 *   operator arrives, the proper number of operands (two for binary operators)
 *   is popped, the operator is applied to them, and the result is pushed back
 *   onto the stack. In the example above, for instance, 1 and 2 are pushed,
 *   then replaced by their difference, -1. Next, 4 and 5 are pushed and the
 *   replaced by their sum, 9. The product of -1 and 9, which is -9, replaces
 *   them on the stack. The value on the top of the stack is popped and printed
 *   when the end of the input line is encountered.
 *
 * - The structure of the program is thus a loop that performs the proper
 *   operation on each operator and operand as it appears:
 *
 *   	while (next operator or operand is not end-of-file indicator)
 *   		if (number)
 *   			push it
 *   		else if (operator)
 *   			pop operands
 *   			do operation
 *   			push result
 *   		else if (newline)
 *   			pop and print top of stack
 *   		else
 *   			error
 *
 *  The operation of pushing and popping a stack are trivial, but by the time
*   error detection and recovery are added, they are long enough that it is
*   better to put each in a seperate function than to repeat the code
*   throughout the whole program. And there should be a seperate function for
*   fetching the next input operator or operand.
*
*   The main design decision that has not yet been discussed is where the stack
*   is, that is, which routines access it directly. On possibility is to keep
*   it in main, and pass the stack and the current stack position to the
*   routines that push and pop it. But main doesn't need to know about the
*   variables that control the stack; it only does push and pop operations. So
*   we have decided to store the stack and its associated information in
*   external variables accessible to the push and pop functions but no to main.
*
*   Translating this outline into code is easy enough. If for now we think of
*   the program as existing in one source file, it will look like this:
*
*   	#includes
*   	#defines
*
*   	function declarations for main
*
*   	main() { ... }
*
*   	external variables for push and pop
*
*   	 void push(double f) { ... }
*   	 double pop(void) { ... }
*
*   	 int getop(char s[]) { ... }
*   	 routines called by getop
*
*   The function main is a loop containing a big switch on the type of operator
*   or operand; this is a more typical use of switch.
*/
*

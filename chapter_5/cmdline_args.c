/***
 * 5.10 Command-line Arguments
 *
 * In environments that support C, there is a way to pass command-line
 * arguments or parameters to a program when it begins executing. When main is
 * called, it is called with two arguments. The first (conventionally called
 * argc, for argument count) is the number of command-line arguments the
 * program was invoked with; the second (argv, for argument vector) is a
 * pointer to an array of character strings that contain the arguments, one per
 * string. We customarily use multiple levels of pointers to manipulate these
 * character strings.
 *
 * The simplest illustration is the program echo, which echoes its command-line
 * arguments on a single line, seperated by blanks. That is, the command
 *
 *  echo hello, world
 * prints the output
 *
 *  hello, world
 * By convention, argv[0] is the name by which the program was invoked, so argc
 * is at least 1. If argc is 1, there are no command-line arguments after the
 * program name. In the example above, argc is 3, and argv[0], argv[1], and
 * argv[2] are "echo", "hello", and "world" respectively. The first optional
 * argument is argv[1] and the last is argv[argc-1]; additionally, the standard
 * requires that argv[argc] be a null pointer.
 *
 * The first version of echo treats argv as an array of character pointers:
 */
#include <stdio.h>

/* echo command-line arguments; 1st version */
// int main(int argc, char *argv[]) {
//   int i;
//
//   for (i = 1; i < argc; i++)
//     printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
//   printf("\n");
//   return 0;
// }

/***
 * Since argv is a pointer to an array of pointers, we can manipulate the
 * pointer rather than index the array. This next variant is based on
 * incrementing argv, which is a pointer to pointer to char, while argc is
 * counted down:
 */

/* echo command-line arugments; 2nd version */
int main(int argc, char *argv[]) {
  while (--argc > 0)
    // Alternatively, we could write the printf statement as
    printf((argc > 1) ? "%s " : "%s", *++argv);
  // This shows that the format argument of printf can be an expression too
  // printf("%s%s", *++argv, (argc > 1) ? " " : "");
  printf("\n");
  return 0;
}

/***
 * In the second version of echo, while argc is pre-decremented, argv is
 * pre-incremented as well to make sure that we ignore the first command-line
 * argument, which is the name the program was invoked with.
 */

/***
 * Since argv is a pointer to the beginning of the array of argument strings,
 * incrementing it by 1 (++argv) makes it point at the original argv[1] instead
 * of argv[0]. Each successive increment moves it along to the next argument;
 * *argv is then the pointer to that argument. At the same time, argc is
 * decremented; when it becomes zero, there are no arguments left to print.
 */

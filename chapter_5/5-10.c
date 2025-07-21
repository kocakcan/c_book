/* Write the program expr, which evaluates a reverse Polish expression from the
 * command line, where each operator or operand is a seperate argument. For
 * example,
 *
 * 	expr 2 3 4 + *
 * evaluates 2 * (3 + 4).
 */
#include <stdio.h>

/* expr: evaluate reverse Polish expression from the command line */
int main(int argc, char *argv[]) {
  if (argc == 1)
    printf("expr: Reverse Polish expression evaluator 😎\n");

  return 0;
}

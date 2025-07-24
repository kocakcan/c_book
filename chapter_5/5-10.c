/* Write the program expr, which evaluates a reverse Polish expression from the
 * command line, where each operator or operand is a seperate argument. For
 * example,
 *
 * 	expr 2 3 4 + *
 * evaluates 2 * (3 + 4).
 */
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

/* expr: evaluate reverse Polish expression from the command line */
int main(int argc, char *argv[]) {
  int type;
  double op2;

  if (argc == 1) {
    printf("Usage: ./main [operands] [operators]\n");
    return 1;
  }

  while (--argc > 0) {
    char *arg = *++argv;

    if ((type = getop(arg)) == NUMBER) {
      push(atof(arg));
    } else {
      switch (type) {
      case '+':
        push(pop() + pop());
        break;
      case '-':
        op2 = pop();
      case '*':
        push(pop() * pop());
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else {
          printf("error: zero divisor\n");
          push(0.0);
        }
        break;
      default:
        if (*arg == '\0')
          printf("error: empty argument\n");
        else
          printf("error: unknown command %s\n", arg);
        break;
      }
    }
  }

  printf("RESULT: %.8g\n", pop());

  return 0;
}

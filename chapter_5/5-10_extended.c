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
#include <string.h>
#define MAXLINE 1000

/* expr: evaluate reverse Polish expression from the command line */
int main(int argc, char *argv[]) {
  char line[MAXLINE];
  while (fgets(line, MAXLINE, stdin) != NULL) {
    int type;
    char *arg;
    double op2;

    arg = strtok(line, " \t\n");
    while (arg != NULL) {
      if ((type = getop(arg)) == NUMBER) {
        push(atof(arg));
      } else {
        switch (type) {
        case '+':
          push(pop() + pop());
          break;
        case '-':
          op2 = pop();
          push(pop() - op2);
          break;
        case '*':
          push(pop() * pop());
          break;
        case '/':
          op2 = pop();
          if (op2 != 0.0)
            push(pop() / op2);
          else
            printf("error: zero divisor\n");
          break;
        default:
          printf("error: unknown command %s\n", arg);
          break;
        }
      }
      arg = strtok(NULL, " \t\n"); /* move to the next token */
    }

    if (!is_empty())
      printf("RESULT: %.8g\n", pop());
    else
      printf("RESULT: error (empty stack)\n");

    clear_stack();
  }

  return 0;
}

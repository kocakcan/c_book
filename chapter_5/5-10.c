/* Write the program expr, which evaluates a reverse Polish expression from the
 * command line, where each operator or operand is a seperate argument. For
 * example,
 *
 * 	expr 2 3 4 + *
 * evaluates 2 * (3 + 4).
 */
#include "../chapter_4/calc.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100

/* expr: evaluate reverse Polish expression from the command line */
int main(int argc, char *argv[]) {
  int type;
  double op2;
  char s[MAXOP];
  if (argc == 1)
    printf("expr: Reverse Polish expression evaluator 😎\n");

  return 0;
}

#include <stdio.h>

// /* - Statements are instructions or actions (e.g., declarations, assignments)
// *   that do not return a value but control the flow of execution.
// * - Statements end with a semicolon and may compries one or more expressions.
// *   - Expressions are combinations of variables, constants, operators, and
// *   function calls that are evaluated to produce a value.
// *   - Expressions do not necessarily end with a semicolon, but they can be
// part
// *   of a statement.
// - Declaring a function is a statement but calling a function can be either a
// statement or an expression depending on whether the function returns a value
// * /

int main(void) {
  int x = 5;

  printf("x is %d\n", x);

  // x = x + 19;
  x += 19;

  printf("x is %d\n", x); // 24

  // 00000011 = 3
  // 00000101 = 5
  int y = 3;

  // 00000011
  // 00000101
  // 00000110 = 6

  // 00000011
  // 00000101
  // 00000111 = 7
  y = y | 5;

  if (y == 7) {
    printf("That's correct\n");
  }

  // 8 * 24 = 192
  // x = x * (y + 1)
  x *= y + 1;

  if (x == 192) {
    printf("Digging of the earth\n");
  } else if (x == 169) {
    printf("That's correct matey!\n");
  }

  int z; // Statement: declaration

  z = 3 + 4; // Statement: assignment (3 + 4 is expression)

  if (z > 5) { // Statement: conditional (where z > 5 is an expression)
    printf("z is greater than 5\n");
  }
}

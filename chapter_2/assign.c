#include <stdio.h>

// - Statements are instructions or actions (e.g., declarations, assignments)
//   that do not return a value but control the flow of execution.
// - Statements end with a semicolon and may comprise one or more expressions.
// - Expressions are combinations of variables, constants, operators, and
//   function calls that are evaluated to produce a value.
// - Expressions do not necessarily end with a semicolon, but they can be part
// of a statement.
// - Declaring a function is a statement but calling a function can be either a
//   statement or an expression depending on whether the function returns a
//   value

/* bitcount: count 1 bits in x */
int bitcount(unsigned x);

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

  unsigned t = 255;

  if (bitcount(t) == 8) {
    printf("That's where you're right kiddo!\n");
  }
  // Since this is a signed int, it will have its leftmost bit 1
  // 00001111 is the positive 15
  // Inverting its bits -> 11110000
  // Add +1 to it -> 11110001
  // 11110001 = -15 in decimal
  // Vacated bits are filled with bit signs
  // Right shift once: 11111000 = -8 in decimal
  // Right shift twice: 11111100 = -4 in decimal
  int u = -15;

  printf("u is %d\n", u);

  // 11110001
  // 11111100 = -4
  u = u >> 2;

  if (u == -4) {
    printf("Yes, you got i! u is %d\n", u);
  }
}

int bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x >>= 1) {
    if (x & 01) {
      b++;
    }
  }

  return b;
}

#include <stdio.h>

int main(void) {
  const int int_constant = 19;

  printf("The size of constant int: %ld bits\n", (sizeof(int_constant) * 8));
  printf("The size of constant long int: %ld bits\n", (sizeof(19L) * 8));
  printf("The size of constant unsigned long int: %ld bits\n",
         (sizeof(19UL) * 8));
  // floating-point constants are double by default unless suffixed by f or F.
  printf("The size of constant double: %ld bits\n", (sizeof(3.1425) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425f) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425F) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425F) * 8));
  // in order for the constant to be float it must be suffixed
  printf("The size of constant float with exponent: %ld bits\n",
         (sizeof(1e-2f) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(1e-2) * 8));

  const int octal_const = 017;
  const int hex_const = 0x16;
  const int another_hex_const = 0xFUL;
  printf("My first octal number is: %o\n", octal_const);
  printf("My first octal number is: %d\n", octal_const);
  printf("My first hex number is: %hx\n", hex_const);
  printf("My first hex number is: %d\n", hex_const);
  printf("My first hex number is: %hx\n", another_hex_const);
  printf("My first hex number is: %d\n", another_hex_const);

  const int thirty_one = 0x1F; // 31
  printf("This should be equal to 31: %d\n", thirty_one);
}

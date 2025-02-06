/* In a two's complement number system, x &= (x - 1) deletes the rightmost
 * 1-bit in x. Explain why. Use this observation to write a faster version of
 * bitcount. */
#include <stdio.h>

int old_bitcount(unsigned x);
int new_bitcount(unsigned x);

int main(void) {
  // Contains 8 1-bits
  unsigned x = 255;

  if (old_bitcount(x) == 8) {
    printf("That's correct!\n");
  }

  if (new_bitcount(x) == 8) {
    printf("That's also correct and faster!\n");
  }

  // Given x = x & (x - 1), x and x - 1 would have different rightmost bits and
  // in order for result to be 1 using bitwise AND two operands must be the
  // same. This would make sure that rightmost bit of the left operand will be
  // 0 after the assignment
  // This feature can be used instead of x >>= 1 and the if block that comes
  // after
}

int old_bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x >>= 1) {
    // In order for this if block to execute x must be 1
    // 01 is octal for 00000001
    if (x & 01) {
      b++;
    }
  }

  return b;
}

int new_bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x &= (x - 1))
    b++;

  return b;
}

#include <limits.h>
#include <stdio.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n);

int main() {
  int n = 255; // 11111111 (binary)

  printf("Original n: %d\n", n);

  // Apply the mask (0177 in octal is 127 in decimal)
  n = n & 0177;

  // Display the result
  printf("Modified n after masking with 0177: %d\n", n);
  printf("Binary representation of n: ");
  // Using bitwise AND we can turn all but the low-order 7 bits of n
  for (int i = 7; i >= 0; --i) {
    printf("%d", (n >> i) & 1); // Print each bit
  }
  printf("\n");

  // The unary operator ~ yields the one's complement of an integer; that is,
  // it converts each 1-bit into a 0-bit and vice versa.
  // Below example sets the last six bits of x to zero.
  int x = 50;
  x = x & ~077;

  printf("x is %d\n", x);

  // When a negative signed value is assigned to an unsigned variable, it leads
  // to an implicit conversion as follows:
  // The signed integer is interpreted using its binary representation as an
  // unsigned integer. This effectively transforms the negative value into a
  // large positive integer due to the two's complement representation used for
  // storing negative numbers.
  unsigned z = -5;

  printf("z is %u\n", z);

  return 0;
}

unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

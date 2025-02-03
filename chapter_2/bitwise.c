#include <stdio.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n);

void sth(char s[], const int size);

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

  // 01111110
  // 01000000 = ~077 (octal) = -64 (decimal)
  // Below sets the last six bits of x to zero
  // ~077 is independent of word length and is thus preferable to
  int c = ~077;
  // ~0 flips all the bits thus making every bit 1 which is the binary
  // representation of -1
  int d = ~0;

  printf("x is %d\n", x);
  printf("c is %d\n", c);
  printf("d is %d\n", d);

  if (d == -1) {
    printf("That's where you are right kiddo");
  }

  char s[] = "Antepli Seyfi";
  const int size = sizeof(s) / sizeof(s[0]);

  sth(s, size);
}

unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

void sth(char s[], const int size) {
  for (int i = 0; i < size; ++i) {
    if (s[i] == ' ') {
      putchar(s[i]);
    } else {
      putchar(s[i]);
      putchar(' ');
    }
  }
}

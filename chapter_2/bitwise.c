#include <stdio.h>

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

  return 0;
}

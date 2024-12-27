/*  Write a program to determine the ranges of char, short, int, and long
 *  variables, both signed and unsigned, by printing appropriate values from
 *  standard headers and by direct computation. Harder if you compute them:
 *  determine the ranges of the various floating-point types.
 */
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  // -2^(N - 1) to 2^(N - 1) - 1 -> Signed
  // 0 to 2^N - 1 -> Unsigned
  // 10000000 -> Minimum negative
  // 01111111 -> Maximum positive
  // In two's complement representation, zero is considered part of the
  // positive range, which is why it is subtracted from the upper limit but not
  // from the lower limit.

  // short and long are type qualifiers applied to integers.
  printf("On this machine:\n");
  printf("int: %ld bits\n", (sizeof(int) * 8));
  printf("INT_MIN: %d\n", INT_MIN);
  printf("INT_MAX: %d\n", INT_MAX);
  printf("signed int: %ld bits\n", (sizeof(signed int) * 8));
  printf("unsigned int: %ld bits\n", (sizeof(unsigned int) * 8));
  printf("UINT_MAX: %ud\n", UINT_MAX);
  printf("short: %ld bits\n", (sizeof(short) * 8));
  printf("signed short: %ld bits\n", (sizeof(signed short) * 8));
  printf("unsigned short: %ld bits\n", (sizeof(unsigned short) * 8));
  printf("USHRT_MAX: %d\n", USHRT_MAX);
  printf("SHRT_MAX: %d\n", SHRT_MAX);
  printf("long: %ld bits\n", (sizeof(long) * 8));
  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("unsigned long: %ld bits\n", (sizeof(unsigned long) * 8));
  printf("signed long: %ld bits\n", (sizeof(signed long) * 8));
  printf("ULONG_MAX: %lu\n", ULONG_MAX);

  // chars are signed by default on this machine
  printf("char: %lu bits\n", (sizeof(char) * 8));
  printf("char: %d\n", CHAR_MAX);
  printf("unsigned char: %d\n", UCHAR_MAX);
  printf("short char: %d\n", CHAR_MAX);
  printf("SCHAR_MAX: %d\n", SCHAR_MAX);
  printf("SCHAR_MIN: %d\n", SCHAR_MIN);

  int nchars = printf("Today I've learned that printf returns the numbers of "
                      "characters successfully read. Wow!\n");

  printf("There were %d characters in above sentence.\n", nchars);

  return 0;
}

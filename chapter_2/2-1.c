/*  Write a program to determine the ranges of char, short, int, and long
 *  variables, both signed and unsigned, by printing appropriate values from
 *  standard headers and by direct computation. Harder if you compute them:
 *  determine the ranges of the various floating-point types.
 */
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  printf("On this machine:\n");
  printf("int: %ld bits\n", (sizeof(int) * 8));
  printf("signed int: %ld bits\n", (sizeof(signed int) * 8));
  printf("unsigned int: %ld bits\n", (sizeof(unsigned int) * 8));
  printf("short: %ld bits\n", (sizeof(short) * 8));
  printf("long: %ld bits\n", (sizeof(long) * 8));

  printf("unsigned int max: %ld bits\n", UINT_MAX);
  printf("signed int max: %d bits\n", INT_MAX);

  int nchars = printf("Today I've learned that printf returns the numbers of "
                      "characters successfully read. Wow!\n");

  printf("There were %d characters in above sentence.\n", nchars);

  return 0;
}

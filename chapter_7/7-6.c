/*
 * Write a program to compare two files, printing the first line where they
 * differ.
 */
#include <stdio.h>

int main(void) {
  int c;

  while ((c = getc(stdin)) != EOF)
    putc(c, stdout);
  return 0;
}

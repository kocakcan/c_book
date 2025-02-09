/* Rewrite function lower, which converts upper case letters to lower case,
 * with a conditional expression instead of if-else. */
#include <stdio.h>

/* lower: convert c to lower case; ASCII only */
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

/* lower_: convert c to lower case; ASCII only, using conditional expression */
int lower_(int c) { return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c; }

int main(void) {
  char c = 'A';

  if ('a' == lower_(c))
    printf("That's correct mate!\n");
}

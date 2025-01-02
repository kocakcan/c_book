/*
 * for (int i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *  s[i] = c;
 * Write a for loop equivalent to the for loop above without using && or ||.
 */
#include <stdio.h>

enum boolean { NO, YES };
enum boolean check = YES;

int main(void) {
  int c, lim = 1000;
  char s[lim];

  // for (int i = 0; i < lim - 1; ++i) {
  //   if ((c = getchar()) != '\n') {
  //     if (c != EOF) {
  //       s[i] = c;
  //     } else
  //       break;
  //   } else
  //     break;
  // }

  int i = 0;

  while (check) {
    if (i >= lim - 1) {
      check = NO;
    } else if ((c = getchar()) == '\n') {
      check = NO;
    } else if (c == EOF) {
      check = NO;
    } else {
      s[i] = c;
      ++i;
    }
  }

  // for (int i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
  //   s[i] = c;

  printf("Here is the line we've just read: %s\n", s);
}

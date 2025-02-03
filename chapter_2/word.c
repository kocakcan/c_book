#include <stdio.h>

enum STATUS { OUT, IN };

int main() {
  int c;
  int STATE = OUT;

  // a program to prints its output one word per line
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (STATE == IN) {
        putchar('\n');
        STATE = OUT;
      } else if (STATE == OUT) {
        STATE = IN;
        putchar(c);
      } else {
        putchar(c);
      }
    }
    putchar(c);
  }

  return 0;
}

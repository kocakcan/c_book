/* Extend entab and detab to accept the shorthand
 *
 *   entab -m +n
 *  to mean tab stops every n columns, starting at column m. Choose convenient
 *  (for the user) default behaviour. */
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_EVERY_COL 8
#define DEFAULT_INIT_POS 1

int main(int argc, char *argv[]) {
  int c, init_pos = DEFAULT_INIT_POS, every_col = DEFAULT_EVERY_COL, pos = 1;

  for (size_t i = 0; i < 2; ++i) {
    char *arg = *++argv;
    if (*arg == '-' && *(arg + 1) != '\0') {
      int val = atoi(arg + 1);
      if (val > 0)
        init_pos = val;
    } else if (*arg == '+' && *(arg + 1) != '\0') {
      int val = atoi(arg + 1);
      if (val > 0)
        every_col = val;
    } else {
      printf("error: unknown argument %c\n", *arg);
      return 1;
    }
  }

  printf("init_pos: %d | every_col: %d\n", init_pos, every_col);

  return 0;
}

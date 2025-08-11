/* Extend entab and detab to accept the shorthand
 *
 *   entab -m +n
 *  to mean tab stops every n columns, starting at column m. Choose convenient
 *  (for the user) default behaviour. */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int c, init_pos, every_col;

  if (argc == 1)
    printf("Usage: -<starting_column> +<tabstop>\n");
  else {

    if ((*++argv)[0] == '-') {
      if (c = atoi(*(argv) + 1))
        init_pos = c;
    } else {
      exit(EXIT_FAILURE);
    }

    if ((*++argv)[0] == '+') {
      if (c = atoi(*(argv) + 1))
        every_col = c;
    } else {
      exit(EXIT_FAILURE);
    }

    // printf("1st char of 2nd arg string: %c\n", (*++argv)[0]);
    // printf("1st char of 2nd arg string: %c\n", (*++argv)[0]);

    printf("init_pos: %d | every_col: %d\n", init_pos, every_col);
    printf("\\0 is: %d\n", '\0');
  }

  return 0;
}

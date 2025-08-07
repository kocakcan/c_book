/* Extend entab and detab to accept the shorthand
 *
 *   entab -m +n
 *  to mean tab stops every n columns, starting at column m. Choose convenient
 *  (for the user) default behaviour. */
#include <stdio.h>

int main(int argc, char *argv[]) {
  int c, init_pos, every_col;

  while (--argc > 0 && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
      case 'c':
        init_pos = 1;
        break;
      case 's':
        every_col = 1;
        break;
      default:
        printf("entab: illegal option: %c\n", c);
      }

  printf("init_pos: %d | every_col: %d\n", init_pos, every_col);

  return 0;
}

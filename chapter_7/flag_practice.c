#include <ctype.h>
#include <stdio.h>

/* convert the given input to upper or lower case depending on the flags passed
 * (lower case by default) */
int main(int argc, char *argv[]) {
  int c, flag;
  int lower = 0, upper = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    if (lower || upper)
      break;
    while (flag = *++argv[0])
      switch (flag) {
      case 'l':
        lower = 1;
        break;
      case 'u':
        upper = 1;
        break;
      default:
        printf("unknown argument %c\n", flag);
        break;
      }
    break; /* break after parsing one character */
  }

  while ((c = getchar()) != EOF)
    putchar((upper > 0) ? toupper(c) : tolower(c));

  return 0;
}

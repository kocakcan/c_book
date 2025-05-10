/* Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what
 * their properties ought to be if an EOF is pushed back, then implement your
 * design. */
#include <stdio.h>

// Declared as int to accommodate EOF
int c = 0;

int getch(void) {
  int temp = c;
  c = 0;

  return (temp) ? temp : getchar();
}

void ungetch(int ch) {
  if (c)
    printf("ungetch: already read a character\n");
  else
    c = ch;
}

int main(void) {
  // int to accommodate EOF
  int ch;

  printf("Enter a character: ");
  ch = getch();
  printf("You've entered: %c (ASCII: %d)\n", ch, ch);

  ungetch(ch);
  ch = getch();
  printf("After ungetch: %c (ASCII: %d)\n", ch, ch);

  ungetch(EOF);
  if (getch() == EOF) {
    printf("After pushing back EOF, received EOF again.\n");
  }
}

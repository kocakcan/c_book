/* Suppose that there will never be more than one character of pushback. Modify
 * getch and ungetch accordingly. */
#include <stdio.h>

char c = 0;

/* getch: return a possibly pushed-back character */
// int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
// int getch(void) { return (c) ? c : getchar(); }
int getch(void) {
  int temp = c;
  c = 0;

  return (temp != 0) ? temp : getchar();
}

/* ungetch: push character back on input */
void ungetch(int ch) {
  // Ensure no more than one character is pushed back
  if (c != 0)
    printf("ungetch: already have a pushed character\n");
  else
    // Push back the character
    c = ch;
}

int main() {
  char ch;

  printf("Enter a character: ");
  ch = getch();
  printf("You entered: %c\n", ch);

  ungetch(ch);
  ch = getch();
  printf("After ungetch: %c\n", ch);

  return 0;
}

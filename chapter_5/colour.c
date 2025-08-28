#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printc(const char *text, int color) {
  printf("\033[1;%dm%s\033[0m", color, text); /* Bold + Color */
}

int main() {
  srand(time(NULL));

  char *words[] = {"Hello", "World", "C", "Loves", "Colors!"};
  int nwords = sizeof(words) / sizeof(words[0]);
  char **wp = words;

  while (nwords--) {
    int color_code = 31 + (rand() % 7); /* Random color (31 - 37) */
    printc(*wp++, color_code);
    printf(" "); /* Add spacing between words */
  }
  printf("\n");
  return 0;
}

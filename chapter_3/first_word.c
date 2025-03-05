/* Write a program that prints the first word in the sentence. */
#include <stdio.h>
#define SIZE 50

int main() {
  int c, i = 0;
  char buffer[SIZE];

  while ((c = getchar()) != EOF && i < SIZE) {
    if (c == ' ' || c == '\t' || c == '\n') {
      break;
    } else {
      buffer[i] = c;
      i++;
    }
  }

  buffer[i] = '\0';

  // Checking only i here as it would be 0 (false) if buffer was empty
  if (i)
    printf("The first word in the given sentence is: %s\n", buffer);
  return 0;
}

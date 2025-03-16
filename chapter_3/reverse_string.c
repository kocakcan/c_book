#include <stdio.h>

void reverse_string(char *str);
void copy(char to[], char from[]);

int main(void) {
  char s[] = "Knight Artorias, the Abysswalker";
  char buffer[100];

  printf("Original string: %s\n", s);

  // Reverse the string
  reverse_string(s);
  printf("Modified string: %s\n", s);
  copy(buffer, s);
  printf("Modified string: %s\n", buffer);
}

void reverse_string(char *str) {
  int left = 0;  // Start index
  int right = 0; // End index

  while (str[right] != '\0')
    right++;

  right--; // Go back once since the current character is the null
  // terminator

  // Swap characters until the middle is reached
  while (left < right) {
    char temp = str[left];  // Store the current character in a temp variable
    str[left] = str[right]; // Swap characters
    str[right] = temp;      // Restore the temp variable
    left++;                 // Move towards the center
    right--;                // Move towards the center
  }
}

void copy(char to[], char from[]) {
  int i = 0;

  while ((to[i] = from[i]) != '\0')
    i++;
}

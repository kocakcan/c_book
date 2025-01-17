#include "header.h"
#include <stdio.h>

enum bool { NO, YES };

/* squeeze: delete all c from s */
void squeeze(char s[], int c);

/* strcat: concatenate t to the end of s; s must be big enough */
void strcat_(char s[], char t[]);

int main() {
  int my_bool = NO;
  enum bool bool_var = 5;
  printf("The value of bool_var is: %d\n", bool_var);
  printf("Sekiro is an amazing game mate\n");
  int flag = nil;

  if (!flag)
    printf("This is the worst TV show ever mate.\n");

  char name[] = "Can Kocak";

  printf("Here's my name before: %s\n", name);
  squeeze(name, 'a');
  printf("Here's my name after: %s\n", name);

  // We can define arrays larger than our original string
  // Rest of the characters would be initialized to null character
  // But that doesn't mean that our string is also larger than it should be
  // as only the first null character matter when it comes to finding the
  // length of the string
  // char s[] = {'\0', '\0', '\0', '\0', '\0', '\0'};
  // char s[6] is different though as it has no initializer it contains garbage
  // values.
  char s[6] = {};
  char t[] = "Kocak";

  strcat_(s, t);
  printf("Here's my surname: %s\n", s);

  return 0;
}

void squeeze(char s[], int c) {
  int i, j;

  for (int i = j = 0; s[i] != '\0'; ++i) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

void strcat_(char s[], char t[]) {
  int i = 0, j = 0;

  while (s[i] != '\0')
    ++i;

  while ((s[i++] = t[j++]) != '\0')
    ;
}

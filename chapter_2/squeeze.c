#include "header.h"
#include <stdio.h>

enum bool { NO, YES };

/* squeeze: delete all c from s */
void squeeze(char s[], int c);

int main() {
  int my_bool = NO;
  enum bool bool_var = 5;
  printf("The value of bool_var is: %d\n", bool_var);
  printf("Sekiro is an amazing game mate\n");
  int flag = nil;
  int nums[10] = {};
  const int size = sizeof(nums) / sizeof(nums[0]);

  for (int i = 0; i < 10; ++i) {
    for (int k = 0; k < size; ++k) {
      nums[k] = i * k;
    }
  }

  printf("Here's the array: \n");

  for (int i = 0; i < size; ++i)
    printf("%d ", nums[i]);

  printf("\n");

  if (!flag)
    printf("This is the worst TV show ever mate.\n");

  char name[] = "Can Kocak";

  printf("Here's my name before: %s\n", name);
  squeeze(name, 'a');
  printf("Here's my name after: %s\n", name);

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

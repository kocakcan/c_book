#include <stdio.h>

int main() {
  int age = 27;

  printf("I am %d years old.\n", age);

  int *const ptr = &age;

  *ptr = 30;

  printf("I'll be %d years old in 3 years.\n", *ptr);

  int other_age = 59;

  return 0;
}

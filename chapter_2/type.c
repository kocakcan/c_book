#include <stdio.h>

int atoi_(char s[]);

int main(void) {
  int arr[] = {0, -2, 5, 4, 3, 11, 245, 523};

  unsigned long x = 9178273986123986;
  short y = x;

  printf("Here's my short variable: %d\n", y);
  char z = '9';
  int u = 19 * z;
  char t = 65;

  printf("Here's my char variable %c and its numeric value %d\n", z, z);
  printf("Here's my char variable %c and its numeric value %d\n", t, t);
  printf("Here's the result matey: %d\n", u);

  char *name = "612";

  printf("Here is the integer version of %s -> %d\n", name, atoi_(name));
  int result = '9' - '7';

  if (result == 2)
    printf("Damn son\n");
}

int atoi_(char s[]) {
  int n = 0;

  for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    n = 10 * n + (s[i] - '0');

  return n;
}

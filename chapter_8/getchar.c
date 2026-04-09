#include <stdio.h>
#include <unistd.h>

/* getchar: simple buffered version */
int getchar(void) {
  char c;

  return (read(0, &c, 1) == 1) ? (unsigned char)c : EOF;
}

int main(void) {
  char name[] = "Can";
  int n = read(0, name, 1);
  if (n == 1)
    printf("Read 1 byte from the stdin into name\n");
  else if (n == 0)
    printf("No character was read\n");
  else
    printf("ERROR!");
  printf("Name: %s\n", name);
  return 0;
}

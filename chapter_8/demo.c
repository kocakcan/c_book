#include "_stdio.h"
#include <unistd.h>

int main(void) {
  _FILE *fp = _fopen("test.txt", "r");
  if (fp == NULL)
    return 1;

  int c;
  while ((c = getc(fp)) != EOF) {
    char ch = (char)c;
    write(1, &ch, 1);
  }
  return 0;
}

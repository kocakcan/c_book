#include "_stdio.h"

int main(void) {
  _FILE *fp = _fopen("test.txt", "r");
  if (!fp) {
    return 1;
  }
  int c;
  while ((c = getc(fp)) != EOF) {
    putcher(c);
  }
  return 0;
}

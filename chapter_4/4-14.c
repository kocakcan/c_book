/* Define a macro swap(t, x, y) that interchanges two arguments of type t.
 * (Block structure will help) */
#include <stdio.h>
#define swap(t, x, y)                                                          \
  {                                                                            \
    t temp = x;                                                                \
    x = y;                                                                     \
    y = temp;                                                                  \
  }

int main(void) {
  double x = .5, y = 3.14;
  char t = 'a', u = 'b';
  int i = 10, j = 30;
  float m = .69f, n = .19f;
  swap(double, x, y);
  swap(char, t, u);
  swap(int, i, j);
  swap(float, m, n);
  printf("x: %g, y: %g\n", x, y);
  printf("t: %c, u: %c\n", t, u);
  printf("i: %d, j: %d\n", i, j);
  printf("m: %.2f, n: %.2f\n", m, n);

  return 0;
}

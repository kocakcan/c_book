/***
 * 5.9 Pointers vs. Multi-dimensional Arrays
 *
 * Newcomers to C are sometimes confused about the difference between a
 * two-dimensional array and an array of pointers, such as name in the
 * month_name example. Given the definitions:
 *
 *  int a[10][10];
 *  int *b[10];
 * then a[3][4] and b[3][4] are both syntactically legal references to a single
 * int. But a is a true two-dimensional array. 200 int-sized locations have
 * been set aside, and the conventional rectangular subscript calculation 20 *
 * row + col is used to find the element a[row, col]. For b, however, the
 * definition only allocates 10 pointers and does not initialize them;
 * initialization must be done explicitly, either statically or with code.
 * Assuming that each element of b does point to a twenty-element array, then
 * there will be 200 ints set aside, plus ten cells for the pointers. The
 * important advantage of the pointer array is that the rows of the array may
 * be of different lengths. That is, each element of b need not point to a
 * twenty-element vector; some may point to two elements, some to fifty, and
 * some to none at all.
 *
 * Although we have phrased this discussion in terms of integers, by far the
 * most frequent use of array of pointers is to store character strings of
 * diverse lengths, as in the function month_name. Compare the declaration for
 * an array of pointers.
 *
 *  char *name[] = {"Illegal month", "Jan", "Feb", "Mar"};
 * with a two-dimensional array:
 *
 *  char name[][15] = {"Illegal month", "Jan", "Feb", "Mar"};
 */
#include <stdio.h>

char *name[4] = {"Illegal month", "Jan", "Feb", "Mar"};
char name_[][35] = {"Illegal month", "Jan", "Feb", "Mar"};

int main(void) {
  // Each element is 8 bytes aside, as they are ints
  // Pointers are stored
  printf("name points to: %p\n", (void *)name);
  printf("name + 1 points to: %p\n", (void *)(name + 1));
  printf("name + 2 points to: %p\n", (void *)(name + 2));
  printf("name + 3 points to: %p\n", (void *)(name + 3));

  // Each element is 35 bytes aside, hence the size
  // Character strings itself are stored
  printf("name_ points to: %p\n", (void *)name_);
  printf("name_ + 1 points to: %p\n", (void *)(name_ + 1));
  printf("name_ + 2 points to: %p\n", (void *)(name_ + 2));

  return 0;
}

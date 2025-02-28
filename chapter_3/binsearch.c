#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void) {

  int arr[] = {0, 1, 5, 6, 7};

  printf("Result is %d\n", binsearch(5, arr, 5));
}

/* This implementation properly locates the item in the array as long as it's
 * in the array albeit with a much more slower and suboptimal way. */
// int binsearch(int x, int v[], int n) {
//   int low, mid, high;
//
//   low = 0;
//   high = n - 1;
//
//   while (low <= high) {
//     mid = (low + high) / 2;
//
//     printf("Before -> low: %d, high: %d, mid: %d\n", low, high, mid);
//     if (x < v[mid])
//       high = mid - 1;
//     else
//       low = mid + 1;
//     printf("After -> low: %d, high: %d, mid: %d\n", low, high, mid);
//   }
//
//   if (low > high)
//     return mid;
//
//   return -1;
// }

/* binsearch with one test in the loop; v[] must be sorted in ascending order
 * */
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  mid = (low + high) / 2;

  while (low <= high && x != v[mid]) {
    if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;

    mid = (low + high) / 2;
  }

  if (x == v[mid]) /* found match */
    return mid;

  return -1; /* no match */
}

// def main():
//     numbers: list[int] = [1, 2, 3, 4, 5]
//     print(list(filter(lambda x: x % 2 != 0, numbers)))
//
// if __name__ == "__main__":
//     main()
// TODO: Implement filter in C

// filter(function, iterable, /)
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define printa(arr, size)                                                      \
  printf("[");                                                                 \
  for (size_t i = 0; i < size; i++) {                                          \
    if (i == size - 1)                                                         \
      printf("%d", arr[i]);                                                    \
    else                                                                       \
      printf("%d, ", arr[i]);                                                  \
  }                                                                            \
  printf("]\n");

int *filter(int (*)(int *), int *, int);
int is_even(int *);

int main(void) {
  int nums[SIZE], *res;

  for (size_t i = 0; i < SIZE; i++)
    nums[i] = i;
  printa(nums, SIZE);
  res = filter(is_even, nums, SIZE);
  printa(res, SIZE);
  return 0;
}

int *filter(int (*f)(int *), int *v, int n) {
  int *new = malloc(n * sizeof(int));
  size_t count = 0;
  for (int *temp = v; temp - v < n; temp++)
    if ((*f)(&v[temp - v]) == 0)
      new[count++] = v[temp - v];
  return new;
}

int is_even(int *x) { return *x % 2; }

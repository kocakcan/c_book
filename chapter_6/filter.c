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

int *filter(int (*)(int), int *, int, int *);
int is_even(int);

int main(void) {
  int nums[SIZE], *res;

  for (size_t i = 0; i < SIZE; i++)
    nums[i] = i;
  printa(nums, SIZE);
  int new_size;
  res = filter(is_even, nums, SIZE, &new_size);
  printa(res, new_size);
  return 0;
}

int *filter(int (*f)(int), int *v, int n, int *out_size) {
  int count = 0;

  for (size_t i = 0; i < n; i++)
    if ((*f)(v[i]) == 0)
      count++;

  int *new = malloc(count * sizeof(int));
  if (new == NULL)
    return NULL;
  int j = 0;
  for (size_t i = 0; i < n; i++)
    if ((*f)(v[i]) == 0)
      new[j++] = v[i];

  *out_size = count;
  return new;
}

int is_even(int x) { return x % 2; }

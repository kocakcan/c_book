#include <stddef.h>
#include <stdio.h>
#define SIZE 50

void printa(const int arr[], size_t size);

int main() {
  int arr[SIZE];
  for (size_t i = 0; i < SIZE; ++i)
    arr[i] = i + (3 * i);

  size_t size = sizeof(arr) / sizeof(arr[0]);

  printa(arr, size);
  return 0;
}

void printa(const int arr[], size_t size) {
  printf("[");
  for (size_t i = 0; i < size; ++i) {
    if (i == size - 1) {
      printf("%d", arr[i]);
    } else {
      printf("%d, ", arr[i]);
    }
  }
  printf("]\n");
}

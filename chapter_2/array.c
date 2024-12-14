#include <stdio.h>

void bubble_sort(int arr[], const int size);

int main() {
  int numbers[] = {14, 11, 50, 23, 27, 41};
  const int size = sizeof(numbers) / sizeof(numbers[0]);

  printf("Unsorted array:\n");
  for (int i = 0; i < size; ++i)
    printf("%d\t", numbers[i]);

  bubble_sort(numbers, size);

  printf("Sorted array:\n");
  for (int i = 0; i < size; ++i)
    printf("%d\t", numbers[i]);

  return 0;
}

// void bubble_sort(int arr[], const int size) {
//   int temp;
//   // Goes beyond the range
//   for (int i = 0; i < size; ++i) {
//     if (arr[i] > arr[i + 1]) {
//       temp = arr[i + 1];
//       arr[i + 1] = arr[i];
//       arr[i] = temp;
//     }
//   }
// }

void bubble_sort(int arr[], const int size) {
  int temp, swapped;

  // Outer loop to make multiple passes
  for (int pass = 0; pass < size - 1; ++pass) {
    // Flag to detect any swaps in this pass
    swapped = 0;

    for (int i = 0; i < size - pass - 1; ++i) {
      if (arr[i] > arr[i + 1]) {
        // Swap adjacent elements if they are in the wrong order
        temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;

        swapped = 1;
      }
    }

    // If no swaps occurred, the array is already sorted
    if (swapped == 0) {
      return;
    }
  }
}

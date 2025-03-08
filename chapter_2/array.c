#include <stdio.h>

void printa(const int arr[], size_t size);
void bubble_sort(int arr[], const int size);
void selection_sort(int arr[], int n);

int main() {
  int numbers[100];

  for (int i = 0; i < 100; ++i)
    numbers[i] = i + (i % 2);

  const int size = sizeof(numbers) / sizeof(numbers[0]);

  printf("Unsorted array:\n");
  printa(numbers, size);

  selection_sort(numbers, size);

  printf("Sorted array:\n");
  printa(numbers, size);

  return 0;
}

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
      break;
    }
  }
}

void selection_sort(int arr[], int n) {
  // Outer loop to track # of passes 
  for (int i = 0; i < n - 1; i++) {
    // Assume that the first element is the minimum element initally
    int min_idx = i;
    // Inner loop to locate the next minimum element
    for (int j = i + 1; j < n; j++) {
      // Check if the current element is smaller than the current minimum
      if (arr[j] < arr[min_idx]) {
        // Update the minimum element index
        min_idx = j;
      }
    }
    // Store the current minimum element into a temporary variable
    int temp = arr[min_idx];

    // Swap current element with element with current minimum index
    arr[min_idx] = arr[i];

    // Store the current minimum element into the current element
    arr[i] = temp;
  }
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

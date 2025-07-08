#include <stdio.h>

int matrix[6][5] = {{-1, 3, 5, 7, 9},  {2, 4, 5, -1, 3}, {9, -3, -2, 4, 1},
                    {5, 19, 3, 4, -8}, {2, 5, 6, 7, 9},  {4, 2, -5, 1, 3}};

/* alter: alter v[i][j] using pointer arithmetics */
// TODO: Add boundary checks
void alter(int (*matrix)[5], int i, int j, int k) { *(*(matrix + i) + j) = k; }

int main(void) {
  alter(matrix, 2, 3, 30);
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 5; j++)
      printf("%d\t", matrix[i][j]);
    printf("\n");
  }

  return 0;
}

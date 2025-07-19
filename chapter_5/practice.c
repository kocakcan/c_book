#include <stdio.h>
#define ROW 6
#define COLUMN 5

int matrix[ROW][COLUMN] = {{-1, 3, 5, 7, 9},  {2, 4, 5, -1, 3},
                           {9, -3, -2, 4, 1}, {5, 19, 3, 4, -8},
                           {2, 5, 6, 7, 9},   {4, 2, -5, 1, 3}};

/* alter: alter v[i][j] using pointer arithmetics 😎 */
void alter(int (*matrix)[5], int i, int j, int k) {
  if ((i >= 0 && i < ROW) && (j >= 0 && j < COLUMN))
    *(*(matrix + i) + j) = k;
}

/* printm: print matrix using pointer arithmetics 🐒 */
void printm(int (*matrix)[COLUMN]) {
  for (size_t i = 0; i < ROW; i++) {
    for (size_t j = 0; j < COLUMN; j++)
      printf("%d\t", *(*(matrix + i) + j));
    printf("\n");
  }
}

// an array of character pointers
// since you store the pointers the character strings themselves can be of
// different lengths unlike multi-dimensional arrays 😎
static char *kocaks[5] = {"leyli kocak", "can kocak", "dilan kocak",
                          "medet kocak", "seyfi kocak"};

size_t strlen_(char *s) {
  size_t i = 0;

  // when s points to the null terminator the loop exits, not incrementing i
  // after but incrementing s one last time to point to the null terminator
  while (*s++)
    i++;

  return i;
}

int main(void) {
  alter(matrix, 0, 1, 300);
  printm(matrix);

  printf("matrix points to: %p\n", (void *)matrix);
  printf("matrix + 1 points to: %p\n", (void *)(matrix + 1));
  printf("matrix + 2 points to: %p\n", (void *)(matrix + 2));

  char *lineptr[5];
  char **copy = lineptr;
  char s[] = "can kocak";
  // lineptr[0] = "can kocak";
  lineptr[0] = s;

  lineptr[0][0] = 'x';

  printf("%s\n", *lineptr);
  int family_size = 5;
  char **familyp = kocaks;

  while (family_size--)
    printf("%s\n", *familyp++);

  printf("my name, %s, is %zd characters long\n", s, strlen_(s));

  char **ap = kocaks;
  // printf("First character of the second character string: %c\n", (*++ap)[0]);
  // printf("First character of the second character string: %c\n", **++ap);
  printf("Second character of the first character string: %c\n", *++ap[0]);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Numbers;

#define da_append(xs, x)                                                       \
  do {                                                                         \
    if (x >= xs.capacity) {                                                    \
      if (xs.capacity == 0)                                                    \
        xs.capacity = 256;                                                     \
      xs.capacity *= 2;                                                        \
      xs.items = realloc(xs.items, xs.capacity * sizeof(xs.items));            \
    }                                                                          \
    xs.items[xs.count++] = x;                                                  \
  } while (0)

int main(void) {
  Numbers xs = {0};

  for (size_t x = 0; x < 10; x++) {
    da_append(xs, x);
  }

  for (size_t i = 0; i < 10; i++)
    printf("%d\n", xs.items[i]);
}

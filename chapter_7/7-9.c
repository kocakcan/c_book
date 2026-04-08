/* Functions like isupper can be implemented to save space or to save time.
 * Explore both possibilities.
 */
#include <stdio.h>
#include <string.h>

#define ISUPPER(c) ((((c) >= 65) && ((c) <= 90)) ? 1 : 0)

int _isupper(int c) { return (c >= 65 && c <= 90) ? 1 : 0; }

int main(void) {
  const char *name = "Can Kocak";

  for (size_t i = 0; i < strlen(name); i++)
    printf("Result for %c: %d\n", name[i], ISUPPER(name[i]));
}

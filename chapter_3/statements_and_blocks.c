/*** Chapter 3 - Control Flow
 * - The control flow of a language specify the order in which computations are
 *   performed.
 */

/***
 * - An expression such as x = 0 or i++ or printf(...) becomes a statement when
 *   it is followed by a semicolon, as in
 *   x = 0;
 *   i++;
 *   printf(...);
 * - In C, the semicolon is a statement terminator, rather than a seperator as
 *   it is in languages like Pascal.
 * - Braces { and } are used to group declarations and statements together into
 *   a compound statement, or block, so that they are syntactically equivalent
 *   to a single statement.
 * - The braces that surround the statements of a function are one obvious
 *   example; braces around multiple statements after an if, else, while, or for
 *   are another.
 * - Variables can be declared inside any block.
 * - There is no semicolon after the right brace that ends a block
 */
#include <stdio.h>

int main() {
  int arr[50];
  for (int i = 0; i < 50; i++)
    if (i % 2 == 0)
      arr[i] = i + 5;
    else
      arr[i] = i;

  printf("Here's my array\n");
  for (int i = 0; i < 50; i++)
    printf("%d\n", arr[i]);

  return 0;
}

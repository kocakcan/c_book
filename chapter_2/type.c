#include <stdio.h>

/*   - Since an argument of a function call is an expression, type conversion
 *   also takes place when arguments are passed to functions.
 *   - In the absence of a function prototype, char and short become int, and
 *   float becomes double.
 *   - Explicit type conversions can be forced/coerced in any expression, with a
 *   unary operator called a cast.
 *   - The precise meaning of a cast is as if the expression were assigned to a
 *   variable of the specified type, which is then used in place of the whole
 *   construction.
 *   - Note that the cast produces a new value for the variable it was used on,
 *   the original variable would not be altered.
 *   - If arguments are declared by a function prototype, as the normally
 *   should be, the declaration causes automatic coercion of any arguments when
 *   the function is called.
 */

/* atoi: convert s to integer */
int atoi_(char s[]);

/* lower: convert c to lower case; ASCII only */
int lower_(int c);

int main(void) {
  int arr[] = {0, -2, 5, 4, 3, 11, 245, 523};

  unsigned long x = 9178273986123986;
  short y = x;

  printf("Here's my short variable: %d\n", y);
  char z = '9';
  int u = 19 * z;
  char t = 65;
  char capital_a = 65;
  char answer = '0' - 6;

  printf("Here's my char variable %c and its numeric value %d\n", z, z);
  printf("Here's my char variable %c and its numeric value %d\n", t, t);
  printf("Here's the result matey: %d\n", u);
  printf("This should print out just a capital A: %c\n", capital_a);

  char *name = "612";
  int num = 19;
  char capital_b = 'B';

  printf("Here's the lower case version of num: %d\n", lower_(num));
  printf("Here's the lower case version of B: %c\n", lower_(capital_b));

  printf("Here is the integer version of %s -> %d\n", name, atoi_(name));
  int result = '9' - '7';

  if (result == 2)
    printf("Damn son\n");

  long signed_val = -1L;
  unsigned long unsigned_val = 1UL;

  printf("signed_val = %ld\n", signed_val);
  printf("unsigned_val = %lu\n", unsigned_val);

  if (signed_val < unsigned_val) {
    printf("-1L < 1UL\n");
  } else {
    printf("-1L > 1UL\n");
  }

  int i = 1900;
  char c = 65;

  printf("%d\n", i);
  printf("%d\n", c);
  i = c;

  printf("%d\n", i);
  printf("%d\n", c);

  c = i;

  printf("%d\n", c);
}

int atoi_(char s[]) {
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    n = n * 10 + (s[i] - '0');

  return n;
}

int lower_(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';

  return c;
}

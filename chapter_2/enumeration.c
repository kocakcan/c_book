#include <limits.h>
#include <stdio.h>

enum Color { RED, GREEN, BLUE };
enum boolean { NO, YES };

int main(void) {
  enum Color my_color;
  enum boolean bool = NO;

  // Integer division truncates any fractional part.
  int x = 5, y = 2;

  printf("The result is: %d\n", x / y); // Result = 2

  // Modulus operator returns the remainder when x is divided by y thus is zero
  // when y divides x exactly.
  // For example, a year is a leap year if it is divisible by 4 but not by 100,
  // except that years divisible by 400 are leap years.
  const int year = 2025;

  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    printf("%d is a leap year\n", year);
  else
    printf("%d is not a leap year\n", year);

  // The % operator cannot be applied to a float or double.
  // The direction of truncation for / and the sign of the result for % are
  // machine-dependent for negative operands, as is the action taken on
  // overflow or underflow.

  int val1 = INT_MAX, val2 = 1;

  printf("%d\n", val1 / val2);

  my_color = RED;
  my_color = 1;
  my_color = 10;
  const double e = 2.71828182845905;
  const char msg[] = "warning: ";
  char *name = "Can";

  printf("Here is my constant double variable: %f\n", e);
  printf("Here is my constant char array: %s\n", msg);

  printf("my_color = %d\n", my_color);

  if (!NO)
    printf("Hey it works!");
}

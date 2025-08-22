#include <stdio.h>

double add(double x, double y) { return x + y; }

double subtract(double x, double y) { return x - y; }

double multiply(double x, double y) { return x * y; }

double divide(double x, double y) {
  if (y == 0.0) {
    printf("error: division by zero\n");
    return 0.0;
  }

  return x / y;
}

/* basic example of an array of function pointers */
int main(void) {
  double (*ftop[])(double, double) = {add, subtract, multiply, divide};

  // double (*ftop[4])(double, double);
  //
  // *ftop = add;
  // *(ftop + 1) = subtract;
  // *(ftop + 2) = multiply;
  // *(ftop + 3) = divide;

  double x = 30.14, y = 30.25;

  double (*(*last))(double, double) = ftop + 4;

  for (double (*(*current))(double, double) = ftop; current < last; current++)
    printf("%.2f (operation) %.2f = %.2f\n", x, y, (*current)(x, y));

  return 0;
}

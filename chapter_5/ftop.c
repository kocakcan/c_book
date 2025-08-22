#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double (*afp[4])(double, double);
  char operations[4];
} Calculator;

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

Calculator *init_calc(double (*funcs[])(double, double), char ops[],
                      size_t nops) {
  Calculator *new_calc = malloc(sizeof(Calculator));

  if (new_calc == NULL) {
    fprintf(stderr, "error: memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < nops; i++) {
    new_calc->afp[i] = funcs[i];
    new_calc->operations[i] = ops[i];
  }

  return new_calc;
}

/* basic example of an array of function pointers */
int main(void) {
  double (*ftop[])(double, double) = {add, subtract, multiply, divide};
  char ops[] = {'+', '-', '*', '/'};
  double x = 45.14, y = 45.25;

  // double (*ftop[4])(double, double);
  //
  // *ftop = add;
  // *(ftop + 1) = subtract;
  // *(ftop + 2) = multiply;
  // *(ftop + 3) = divide;

  // double x = 30.14, y = 30.25;
  //
  // double (*(*last))(double, double) = ftop + 4;
  //
  // for (double (*(*current))(double, double) = ftop; current < last;
  // current++)
  //   printf("%.2f (operation) %.2f = %.2f\n", x, y, (*current)(x, y));

  Calculator *calc = init_calc(ftop, ops, 4);

  for (size_t i = 0; i < 4; i++)
    printf("%.2f %c %.2f = %.2f\n", x, calc->operations[i], y,
           calc->afp[i](x, y));

  return 0;
}

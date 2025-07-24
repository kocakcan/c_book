#include "calc.h"
#include <stdio.h>
#define MAXVAL 100

// External variables
static double val[MAXVAL];
static double *sp = val;

void push(double f) {
  if (sp - val < MAXVAL)
    *sp++ = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp - val > 0)
    return *--sp;
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int is_empty(void) { return sp == val; }
void clear_stack(void) { sp = val; }

/*
 * Revise minprintf to handle more of the other facilities of printf.
 */
#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...) {
  va_list ap;
  char *s, *sval;
  int ival;
  double dval;

  va_start(ap, fmt);
  for (s = fmt; *s; s++) {
    if (*s != '%') {
      putchar(*s);
      continue;
    }
    switch (*++s) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    default:
      putchar(*s);
      break;
    }
  }
  va_end(ap);
}

int main(void) {
  char *str = "Fuck Brother Asterion from Blasphemous 2";
  int damage = 1905; /* that's a lot of damage */
  double eulers_constant = 2.71;

  minprintf("%s\n", str);
  minprintf("%d\n", damage);
  minprintf("%f\n", eulers_constant);
  return 0;
}

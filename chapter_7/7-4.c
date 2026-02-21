/* Write a private version of scanf analogous to minprintf from the previous
 * section. */
#include <stdarg.h>
#include <stdio.h>

void minscanf(char *, ...);

int main(void) { return 0; }

void minscanf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  double dval;
  int ival;

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      getchar();
      continue;
    }
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);
      scanf("%d", &ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      scanf("%lf", &dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        getchar();
      break;
    default:
      getchar();
      break;
    }
  }
  va_end(ap);
}

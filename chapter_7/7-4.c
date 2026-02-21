/* Write a private version of scanf analogous to minprintf from the previous
 * section. */
#include <stdarg.h>
#include <stdio.h>

void minscanf(char *, ...);

int main(void) {
  printf("char * int double ");
  char name[100];
  int ival;
  double dval;
  minscanf("%s %d %f", name, &ival, &dval);
  printf("%s %d %f\n", name, ival, dval);
  return 0;
}

void minscanf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  double *dval;
  int *ival;

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      getchar();
      continue;
    }
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int *);
      scanf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double *);
      scanf("%lf", dval);
      break;
    case 's':
      sval = va_arg(ap, char *);
      scanf("%s", sval);
      break;
    default:
      getchar();
      break;
    }
  }
  va_end(ap);
}

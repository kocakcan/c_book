#include "calc.h"
#include <ctype.h>

int getop(char *s) {
  if (!isdigit(*s) && *s != '.' && *s != '-')
    return *s;

  if (*s == '-' && !isdigit(*(s + 1)) && *(s + 1) != '.')
    return '-';

  return NUMBER;
}

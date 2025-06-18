/* Write a pointer version of the function strcat(s, t) which copies t to the
 * end of s */
#include <stdio.h>

/* strcat__: concatenate t to the end of s; pointer version */
void strcat_(char *s, char *t) {
  if (s == NULL || t == NULL)
    return;
  while (*s)
    s++;
  while (*s++ = *t++)
    ;
}

int main(void) {
  char s[] = "Knight";
  char t[] = " Artorias";
  strcat_(s, t);

  printf("My favorite boss in Dark Souls is %s\n", s);

  return 0;
}

/* Write a pointer version of the function strcat(s, t) which copies t to the
 * end of s */
#include <stdio.h>

/* strcat_: concatenate t to the end of s; s must be big enough */
void strcat_(char s[], char t[]) {
  int i, j;

  i = j = 0;
  while (s[i] != '\0')
    i++;
  while ((s[i++] = t[j++]) != '\0')
    ;
}

/* strcat__: concatenate t to the end of s; pointer version */
void strcat__(char *s, char *t) {
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
  strcat__(s, t);

  printf("My favorite boss in Dark Souls is %s\n", s);

  return 0;
}

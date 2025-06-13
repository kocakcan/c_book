/* Write the function strend(s, t), which returns 1 if the string t occurs at
 * the end of the string s, and zero otherwise. */
#include <stdio.h>

/* strend: return 1 if string t occurs at the end of string s, and 0 otherwise
 * */
int strend(char *s, char *t) {
  int i, j;

  j = 0;
  while (*s) {
    s++;
    j++;
  }

  i = 0;
  while (*t) {
    t++;
    i++;
  }

  if (j < i)
    return 0;

  for (; *s-- == *t--; i--) {
    if (i == 0)
      return 1;
  }

  return 0;
}

int main(void) {
  char *s = "Knight Artorias";
  char *t = "Artorias";

  if (strend(s, t))
    printf("%s appears at the end of %s\n", t, s);

  return 0;
}

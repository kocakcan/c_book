/* Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include getline, atoi,
 * itoa, and their variants, reverse, strindex and getop */
#include <stdio.h>

int strindex(char *s, char *t) {
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }

  return -1;
}

int main(void) {
  char *s = "Can Kocak";
  char *t = "Kocak";
  printf("%s is at index %d in %s\n", t, strindex(s, t), s);

  return 0;
}

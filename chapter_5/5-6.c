/* Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include getline, atoi,
 * itoa, and their variants, reverse, strindex and getop */
#include <stdio.h>

/* strindex: return index of t in s, -1 if none */
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

/* strindex: return index of t in s, -1 if none; pointer version */
int strindex_(char *s, char *t) {
  int i, j, k;

  for (i = 0; *s; i++, s++) {
    for (j = i, k = 0; *t && *s == *t; j++, k++, s++, t++)
      ;
    if (k > 0 && *t == '\0')
      return i;
  }

  return -1;
}

int main(void) {
  char *s = "Can Kocak";
  char *t = "Kocak";
  printf("%s is at index %d in %s\n", t, strindex_(s, t), s);

  return 0;
}

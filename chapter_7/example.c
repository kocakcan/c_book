#include <stdio.h>

#define MAXLINE 100

int getline_(char *, int);

int main(void) {
  char buffer[MAXLINE];
  int day, month, year;
  char monthname[20];

  while (getline_(buffer, sizeof(buffer)) > 0) {
    if (sscanf(buffer, "%d %s %d", &day, monthname, &year) == 3)
      printf("valid: %s\n", buffer); /* 25 Dec 1988 form */
    else if (sscanf(buffer, "%d/%d/%d", &day, &month, &year) == 3)
      printf("valid: %s\n", buffer); /* mm/dd/yy form */
    else
      printf("invalid: %s\n", buffer); /* invalid form */
  }

  return 0;
}

int getline_(char *s, int lim) {
  int c, i = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    *s++ = c, i++;
  if (c == '\n')
    *s++ = c, i++;
  *s = '\0';
  return i;
}

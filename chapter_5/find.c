/***
 * Following the lead of the UNIX program grep, let us enhance the
 * pattern-finding program so the pattern to be matched is specified by the
 * first argument on the command line.
 */
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline_(char *line, int max) {
  int i, c;

  i = 0;
  while (--max > 0 && (c = getchar()) != EOF && c != '\n') {
    *line++ = c;
    i++;
  }

  if (c == '\n') {
    *line++ = c;
    i++;
  }

  *line = '\0';
  return i;
}

char *strindex_(char *s, char *t) {
  char *ps, *pt;

  for (; *s; s++) {
    for (ps = s, pt = t; *pt && *ps == *pt; ps++, pt++)
      ;
    if (pt > t && *pt == '\0')
      return s;
  }
  return NULL;
}

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (getline_(line, MAXLINE) > 0)
      if (strindex_(line, argv[1]) != NULL) {
        printf("%s", line);
        found++;
      }
  return found;
}

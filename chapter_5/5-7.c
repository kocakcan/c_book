/* Rewrite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program? */
#include <stdio.h>
#include <string.h>
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000   /* max length of any input line */
#define MAXSTORE 10000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], char *line, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
  int nlines; /* number of input lines read */
  char line[MAXSTORE];

  if ((nlines = readlines(lineptr, line, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    printf("# - Result - #\n");
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }

  printf("line is: %s", line);
}

int getline_(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], char *line, int maxlines) {
  int len, nlines;

  char *p =
      line + strlen(line); /* p points to the first empty position in line */

  nlines = 0;
  while ((len = getline_(p, MAXLEN)) > 0) {
    if (nlines >= maxlines || line + MAXSTORE - p < len)
      return -1;
    p[len - 1] = '\0';
    lineptr[nlines++] = p;
    p += len;
  }

  return nlines;
}

/* getline_: get a line */
int getline_(char *s, int lim) {
  int i, c;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
    i++;
  }
  if (c == '\n') {
    *s++ = c;
    i++;
  }
  *s = '\0';
  return i;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
  char *temp;

  temp = v[i], v[i] = v[j], v[j] = temp;
}

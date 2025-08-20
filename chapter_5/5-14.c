/* Modify the sort program to handle a -r flag, which indicates sorting in
 * reverse (decreasing) order. Be sure that -r works with -n.
 */
#include <stdio.h>
#include <stdlib.h>
#define ALLOCSIZE 10000
#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int getline_(char *s, int lim);
void swap(void *v[], int left, int right);
char *alloc(int n);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void strcpy_(char *, char *);

void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmp_(char *, char *);

int main(int argc, char *argv[]) { return 0; }

int getline_(char *s, int lim) {
  int c, i = 0;

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

void swap(void *v[], int left, int right) {
  void *temp = v;

  // temp = v[left], v[left] = v[right], v[right] = temp;
  temp = *(v + left), *(v + left) = *(v + right), *(v + right) = temp;
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}

void strcpy_(char *s, char *t) {
  while (*s++ = *t++)
    ;
}

int readlines(char *lineptr[], int maxlines) {
  int len, nlines = 0;
  char line[MAXLEN], *p;

  while ((len = getline_(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    line[len - 1] = '\0';
    strcpy_(p, line);
    lineptr[nlines++] = p;
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s\n", *lineptr++);
}

int strcmp_(char *s, char *t) {
  while (*s && *s == *t)
    s++, t++;

  return (unsigned char)*s - (unsigned char)*t;
}

int numcmp(char *s, char *t) {
  double v1, v2;

  v1 = atof(s);
  v2 = atof(t);

  if (v1 > v2)
    return -1;
  else if (v1 < v2)
    return 1;
  else
    return 0;
}

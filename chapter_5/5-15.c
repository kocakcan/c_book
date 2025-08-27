/* Add the option -f to fold upper and lower case together, so that case
 * distinctions are not made during sorting; For example, a and A compare equal.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLINES 5000
#define MAXLEN 5000
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
static char *lineptr[MAXLINES];
char *alloc(int);

int getline_(char *, int);
void strcpy_(char *, const char *);
int readlines(char **, int);
void writelines(char **, int);
int strcmp_(const char *, const char *);
int fstrcmp(const char *, const char *);
void swap(void **, int, int);
void qsort_(void **, int, int, int (*)(const void *, const void *));

int main(int argc, char *argv[]) {
  int nlines, fold = 0;

  if (--argc > 0 && strcmp_(*++argv, "-f") == 0)
    fold = 1;

  printf("fold: %d\n", fold);

  const char *s = "snake", *t = "Snake";
  printf("result: %d\n", fstrcmp(s, t));

  return 0;
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
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

void strcpy_(char *s, const char *t) {
  while (*s++ = *t++)
    ;
}

int readlines(char **lineptr, int maxlines) {
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

void writelines(char **lineptr, int nlines) {
  while (nlines--)
    printf("%s\n", *lineptr++);
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

void swap(void **v, int left, int right) {
  void *temp;

  temp = *(v + left), *(v + left) = *(v + right), *(v + right) = temp;
}

void qsort_(void **v, int left, int right,
            int (*comp)(const void *, const void *)) {
  int i, last;

  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort_(v, left, last - 1, comp);
  qsort_(v, last + 1, right, comp);
}

int fstrcmp(const char *s, const char *t) {
  while (*s && tolower(*s) == tolower(*t))
    s++, t++;
  return (unsigned char)tolower(*s) - (unsigned char)tolower(*t);
}

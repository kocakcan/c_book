/* Modify the sort program to handle a -r flag, which indicates sorting in
 * reverse (decreasing) order. Be sure that -r works with -n.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

int _strcmp_(void *a, void *b) {
	return strcmp_((char *)a, (char *)b);
}

int rstrcmp(void *a, void *b) {
	return -strcmp_((char *)a, (char *)b);
}

int is_number(const char *s) {
	if (*s == '-' || *s == '+') s++;
	int has_digit = 0, has_dot = 0;
	while (*s) {
		if (isdigit((unsigned char)*s))
			has_digit = 1;
		else if (*s == '.' && !has_dot)
			has_dot = 1;
		else
			return 0;
		s++;
	}

	return has_digit;
}

int numcmp_with_fallback(char *s, char *t) {
	if (is_number(s) && is_number(t)) {
		double v1 = atof(s);
		double v2 = atof(t);
		if (v1 < v2) return -1;
		else if (v1 > v2) return 1;
		else return 0;
	}
	return strcmp_(s, t);
}

int rnumcmp_with_fallback(char *s, char *t) {
	return -numcmp_with_fallback(s, t);
}

int cmp_numeric(void *a, void *b) {
	return numcmp_with_fallback((char *)a, (char *)b);
}

int cmp_numeric_r(void *a, void *b) {
	return rnumcmp_with_fallback((char *)a, (char *)b);
}

int main(int argc, char *argv[]) {
  int c, nlines, numeric = 0, reverse = 0;
  int (*cmp)(void *, void *) = _strcmp_;

  while (--argc > 0 && (*++argv)[0] == '-') {
    while (c = *++argv[0])
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      default:
        printf("invalid argument %c\n", **argv);
        argc = 0;
        break;
      }
  }

  if (numeric)
	cmp = reverse ? cmp_numeric_r : cmp_numeric;
  else
	cmp = reverse ? rstrcmp : _strcmp_;

	if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
	qsort_((void **) lineptr, 0, nlines - 1, cmp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}

  return 0;
}

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
  void *temp;

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

  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void qsort_(void *v[], int left, int right, int (*comp) (void *, void *)) {
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

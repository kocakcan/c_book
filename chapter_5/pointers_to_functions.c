/***
 *
 * 5.11 Pointers to Functions
 *
 * In C, a function itself is not a variable, but it is possible to define
 * pointers to functions, which can be assigned, placed in arrays, passed to
 * functions, returned by functions, and so on. We will illustrate this by
 * modifying the sorting procedure written earlier in this chapter so that if
 * the optional argument -n is given, it will sort the input lines numerically
 * instead of lexicographically.
 *
 * A sort often consists of three parts - a comparison that determines the
 * ordering of any pair of objects, an exchange that reverses their order, and a
 * sorting algorithm that makes comparisons and exchanges until the objects are
 * in order. The sorting algorithm is independent of the comparison and exchange
 * operations, so by passing different comparison and exchange functions to it,
 * we can arrange to sort by different criteria. This is the approach taken in
 * our new sort.
 *
 * Lexicographic comparison of two lines is done by strcmp, as before; we will
 * also need a routine numcmp that compares two lines on the basis of numeric
 * value and returns the same kind of condition as strcmp does. These functions
 * are declared ahead of main and a pointer to the appropriate one is passed to
 * qsort. We have skimped on error processing for arguments, so as to
 * concentrate on the main issues.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLINES 5000   /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmp_(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;      /* number of input lines read */
  int numeric = 0; /* 1 if numeric sort */

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort_((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))(numeric ? numcmp : strcmp_));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/***
 * In the call to qsort, strcmp and numcmp are addresses of functions. Since
 * they are known to be functions, the & is not necessary, in the same way that
 * it is not needed before an array name.
 *
 * We have written qsort so it can process any data type, not just character
 * strings. As indicated by the function prototype, qsort expects an array of
 * pointers, two integers, and a function with two pointer arguments. The
 * generic pointer type void * is used for the pointer arguments. Any pointer
 * can be cast to void * and back again without loss of information, so we can
 * call qsort by casting arguments to void *. The elaborate cast of the function
 * argument casts the arguments of the comparison function. These will generally
 * have no effect on actual representation, but assure the compiler that all is
 * well.
 */

/* qsort: sort v[left]...v[right] into increasing order */
void qsort_(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;

  void swap(void *v[], int, int);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort_(v, left, last - 1, comp);
  qsort_(v, last + 1, right, comp);
}

/* The declarations should be studied with some care. The fourth parameter of
 * qsort is
 *
 *   int (*comp) (void *, void *)
 * which says that comp is a pointer to a function that has two void * arguments
 * and return an int.
 *
 * The use of comp in the line
 *
 *   if ((*comp)(v[i], v[left]) < 0)
 * is consistent with the declaration: comp is a pointer to a function, *comp is
 * the function, and
 *
 *   (*comp) (v[i], v[left])
 * is the call to it. The parantheses are needed so the components are correctly
 * associated; without them,
 *
 *   int *comp(void *, void *) -> WRONG
 * says that comp is a function returning a pointer to an int, which is very
 * different.
 *
 * We have already shown strcmp, which compares two strings. Here is numcmp,
 * which compares two strings on a leading numeric value, computed by calling
 * atof:
 */

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

/* The swap function, which exchanges two pointers, is identical to what we
 * presented earlier in the chapter, except that the declarations are changed to
 * void *.
 */

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int strcmp_(char *s, char *t) {
  while (*s && *s == *t)
    s++, t++;

  return (unsigned char)*s - (unsigned char)*t;
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

/* alloc: return pointer to n characters */
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* if it fits */
    allocp += n;
    return allocp - n; /* return old p */
  } else {
    return 0;
  }
}

int readlines(char *lineptr[], int maxlines) {
  int len, nlines = 0;
  char line[MAXLEN], *p;

  while ((len = getline_(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s\n", *lineptr++);
}

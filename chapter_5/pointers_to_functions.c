/***
 *
 * 5. 11 Pointers to Functions
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
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;      /* number of input lines read */
  int numeric = 0; /* 1 if numeric sort */

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort((void **)lineptr, 0, nlines - 1,
          (int (*)(void *, void *))(numeric ? numcmp : strcmp));
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
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
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
  qsort(v, left, last - 1, comp);
  qsort(v, last + 1, right, comp);
}

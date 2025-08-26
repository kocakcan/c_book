/* Add the option -f to fold upper and lower case together, so that case
 * distinctions are not made during sorting; For example, a and A compare equal.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
#define MAXLEN 5000
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
static char *lineptr[MAXLEN];
char *alloc(int);

int getline_(char *, int);
int readlines(char **, int);
void writelines(char **, int);
int strcmp_(const char *, const char *);
int numcmp(const char *, const char *);
void qsort_(void **, int, int, int (*)(const void *, const void *));
void swap(void **, int, int);

int main(void) {
  printf("aye, siwmae\n");
  return 0;
}

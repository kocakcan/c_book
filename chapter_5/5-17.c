/* Add a field-searching capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers.)
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
int strncmp_(const char *, const char *, size_t);
int fstrcmp(const char *, const char *);
int dstrcmp(const char *, const char *);
int dfstrcmp(const char *, const char *);
void get_field(const char *, int, char *, int);
void swap(void **, int, int);
void qsort_(void **, int, int, int (*)(const void *, const void *));

/* Wrappers for field-based compare */
int field_strcmp(const char *, const char *, int);
int field_fstrcmp(const char *, const char *, int);
int field_dstrcmp(const char *, const char *, int);
int field_dfstrcmp(const char *, const char *, int);

/* Adapter functions for qsort_ */
int cmp_field_strcmp(const void *, const void *);
int cmp_field_fstrcmp(const void *, const void *);
int cmp_field_dstrcmp(const void *, const void *);
int cmp_field_dfstrcmp(const void *, const void *);

/* Global field number (used by adapter functions) */
int g_field_num = 0; 

int main(int argc, char *argv[]) {
  int c, nlines, fold = 0, dir = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    while (c = **++argv)
      switch (c) {
      case 'f':
        fold = 1;
        break;
      case 'd':
        dir = 1;
        break;
      default:
        printf("sort: illegal option %c\n", c);
        break;
      }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    int (*comp)(const char *, const char *);

    if (fold && dir)
      comp = dfstrcmp;
    else if (fold)
      comp = fstrcmp;
    else if (dir)
      comp = dstrcmp;
    else
      comp = strcmp_;

    qsort_((void **)lineptr, 0, nlines - 1,
           (int (*)(const void *, const void *))comp);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }

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

int strncmp_(const char *s, const char *t, size_t n) {
	while (n--) {
		if (*s != *t)
			return (unsigned char)*s - (unsigned char)*t;
		if (*s == '\0')
			return 0;
		s++, t++;
	}

	return 0;
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

int dstrcmp(const char *s, const char *t) {
  while (*s && *t) {
    while (*s && !isalnum(*s) && !isspace(*s))
      s++;
    while (*t && !isalnum(*t) && !isspace(*t))
      t++;

    if (*s != *t)
      return (unsigned char)*s - (unsigned char)*t;
    if (*s == '\0')
      return 0;
    s++, t++;
  }
  return (unsigned char)*s - (unsigned char)*t;
}

int dfstrcmp(const char *s, const char *t) {
  while (*s && *t) {
    while (*s && !isalnum(*s) && !isspace(*s))
      s++;
    while (*t && !isalnum(*t) && !isspace(*t))
      t++;

    if (tolower(*s) != tolower(*t))
      return (unsigned char)tolower(*s) - (unsigned char)tolower(*t);
    if (*s == '\0')
      return 0;
  }
  return (unsigned char)tolower(*s) - (unsigned char)tolower(*t);
}

/* get_field: extract the nth field from a line (1-based index) */
void get_field(const char *line, int field_num, char *field_buf, int bufsize) {
	int i = 0, f = 1;
	while (*line && f < field_num) {
		if (isspace(*line)) {
			while (isspace(*line))
				line++;
			f++;
		} else
			line+;;
	}

	while (*line && !isspace(*line) && i < bufsize - 1)
		field_buf[i++] = *line++;

	field_buf[i] = '\0';
}

int field_strcmp(const char *s, const char *t, int field_num) {
	char fs[MAXLEN], ft[MAXLEN];
	get_field(s, field_num, fs, MAXLEN);
	get_field(t, field_num, ft, MAXLEN);
	return strcmp_(fs, ft);
}

int field_fstrcmp(const char *s, const char *t, int field_num) {
	char fs[MAXLEN], ft[MAXLEN];
	get_field(s, field_num, fs, MAXLEN);
	get_field(t, field_num, ft, MAXLEN);
	return fstrcmp(fs, ft);
}

int field_dstrcmp(const char *s, const char *t, int field_num) {
	char fs[MAXLEN], ft[MAXLEN];
	get_field(s, field_num, fs, MAXLEN);
	get_field(t, field_num, ft, MAXLEN);
	return dfstrcmp(fs, ft);
}

int cmp_field_strcmp(const void *a, const void *b) {
	return field_strcmp(*(const char **)a, *(const char **)b, g_field_num);
}

int cmp_field_fstrcmp(const void *a, const void *b) {
	return field_fstrcmp(*(const char **)a, *(const char **)b, g_field_num);
}

int cmp_field_dstrcmp(const void *a, const void *b) {
	return field_dstrcmp(*(const char **)a, *(const char **)b, g_field_num);
}

int cmp_field_dfstrcmp(const void *a, const void *b) {
	return field_dfstrcmp(*(const char **)a, *(const char **)b, g_field_num);
}

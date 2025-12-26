/* Our version of getword does not properly handle underscores, string
 * constants, comments, or preprocessor control lines. Write a better version.
 */
#include <ctype.h>
#include <stdio.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
  char *word;
  int count;
} keytab[] = {"auto",  0, "break",    0, "case",    0, "char",     0,
              "const", 0, "continue", 0, "default", 0, "unsigned", 0,
              "void",  0, "volatile", 0, "while",   0};

int getch(void);
void ungetch(int);
int strcmp_(const char *, const char *);
int comment(void);
int getword(char *, int);
int binsearch(char *, struct key *, int);

static char buf[MAXWORD];
static char *bufp = buf;

/* count C keywords */
int main() {
  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);
}

/* binsearch: find word int tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp_(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }

  return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, d;
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (isalpha(c) || c == '_' || c == '#') {
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  } else if (c == '\'' || c == '"') {
    for (; --lim > 0; w++) {
      if ((*w = getch()) == '\\')
        *++w = getch();
      else if (*w == c) {
        w++;
        break;
      } else if (*w == EOF)
        break;
      else if (c == '/') {
        if ((d = getch()) == '*')
          c = comment();
        else
          ungetch(d);
      }
    }
  }
  *w = '\0';
  return c;
}

/* comment: skip over comment and return a character */
int comment(void) {
  int c;
  while ((c = getch()) != EOF)
    if (c == '*') {
      if ((c = getch()) == '/')
        break;
      else
        ungetch(c);
    }
  return c;
}

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (c == EOF)
    return;
  if (bufp - buf >= MAXWORD)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}

int strcmp_(const char *s, const char *t) {
  for (; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

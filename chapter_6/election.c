#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define NCANDIDATES (sizeof candidates / sizeof(candidates[0]))

struct candidate {
  char *name;
  int ballot;
} candidates[] = {{"Eli", 0},    {"Huey", 0},  {"Kaz", 0},
                  {"Ocelot", 0}, {"Quiet", 0}, {"Snake", 0}};

int getword(char *, int);
struct candidate *binsearch(char *, struct candidate *, int);
int getch(void);
void ungetch(int);
int strcmp_(const char *, const char *);

static char buf[MAXWORD];
static char *bufp = buf;

int main(void) {
  char word[MAXWORD];
  struct candidate *p;

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((p = binsearch(word, candidates, NCANDIDATES)) != NULL)
        p->ballot++;
  for (p = candidates; p < candidates + NCANDIDATES; p++)
    if (p->ballot > 0)
      printf("%4d %s\n", p->ballot, p->name);

  return 0;
}

struct candidate *binsearch(char *word, struct candidate *x, int n) {
  int cond;
  struct candidate *low = x;
  struct candidate *high = x + n;
  struct candidate *mid;

  while (low < high) {
    mid = low +
          (high - low) / 2; /* can't use low + high / 2 as they are pointers */
    if ((cond = strcmp_(word, mid->name)) < 0)
      high = mid;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return NULL;
}

// TODO: currently handles up to the whitespace character, could try to parse
// two words
int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t) {
    if (*s == '\0')
      return 0;
    s++, t++;
  }
  return (unsigned char)*s - (unsigned char)*t;
}

int getch(void) { return (bufp - buf > MAXWORD) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (bufp - buf >= MAXWORD)
    printf("error: too many characters\n");
  else
    *bufp++ = c;
}

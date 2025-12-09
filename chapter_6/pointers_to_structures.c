/***
 * 6.4 Pointers to Structures
 *
 * To illustrate some of the considerations involved with pointers to arrays of
 * structures, let us write the keyword-counting program again, this time using
 * pointers instead of array indices.
 *
 * The external declaration of keytab need not change, but main and binsearch
 * do need modification.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

struct key {
  char *word;
  int count;
} keytab[] = {"auto",  0, "break",    0, "case",    0, "char",     0,
              "const", 0, "continue", 0, "default", 0, "unsigned", 0,
              "void",  0, "volatile", 0, "while",   0};

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);
int comment(void);
int strcmp_(const char *, const char *);

static char buf[MAXWORD];
static char *bufp = buf;

/* count C keywords; pointer version */
int main(void) {
  char word[MAXWORD];
  struct key *p;

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((p = binsearch(word, keytab, NKEYS)) != NULL)
        p->count++;
  for (p = keytab; p < keytab + NKEYS; p++)
    if (p->count > 0)
      printf("%4d %s\n", p->count, p->word);
  const char *name = "can";
  const char *nick = "can";
  if (strcmp_(name, nick))
    printf("that's correct\n");
  return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
struct key *binsearch(char *word, struct key *tab, int n) {
  int cond;
  struct key *low = &tab[0];
  struct key *high = &tab[n];
  struct key *mid;

  while (low < high) {
    mid = low + (high - low) / 2;
    if ((cond = strcmp_(word, mid->word)) < 0)
      high = mid;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return NULL;
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
        *w++ = getch();
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

/* strcmp_: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t) {
    if (*s == '\0')
      return 0;
    s++, t++;
  }
  return (unsigned char)*s - (unsigned char)*t;
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

int getch(void) { return (bufp - buf > MAXWORD) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (bufp - buf >= MAXWORD)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}

/***
 * There are several things worthy of note here. First, the declaration of
 * binsearch must indicate that it returns a pointer to struct key instead of an
 * integer; this is declared both in the function prototype and in binsearch. If
 * binsearch finds the word, it returns a pointer to it, if it fails, it returns
 * NULL.
 *
 * Second, the elements of keytab are now accessed by pointers. This requires
 * significant changes in binsearch.
 *
 * The initializers for low and high are now pointers to the beginning and just
 * past the end of the table.
 *
 * The computation of the middle element can no longer be simply
 *
 *   mid = (low + high) / 2; -> WRONG
 * because the addition of pointers is illegal. Subtraction is legal, however,
 * so high-low is the number of elements, and thus
 *
 *   mid = low + (high - low) / 2
 * sets mid to the element halfway between low and high.
 *
 * The most important change is to adjust the algorithm to make sure that it
 * does not generate an illegal pointer or attempt to access an element outside
 * the array. The problem is that &tab[-1] and &tab[n] are both outside the
 * limits of the array tab. The former is strictly illegal, and it is illegal to
 * dereference the latter. The language definition does guarantee, however, that
 * pointer arithmetic that involves the first element beyond the end of an array
 * (that is, &tab[n]) will work correctly.
 *
 * In main we wrote
 *
 *   for (p = keytab; p < keytab + NKEYS; p++)
 * If p is a pointer to a structure, arithmetic on p takes into account the size
 * of the structure, so p++ increments p by the correct amount to get the next
 * element of the array of structures, and the test stops the loop at the right
 * time.
 *
 * Don't assume, however, that the size of a structure is the sum of the sizes
 * of its members. Because of alignment requirements for different objects,
 * there may be unnamed "holes" in a structure. Thus, for instance, if a char is
 * one byte and an int four bytes, the structure
 *
 *   struct {
 *     char c;
 *     int i;
 *   };
 * might well require eight bytes, not five. The sizeof operator returns the
 * proper value.
 *
 * Finally, an aside on program format: when a function returns a complicated
 * type like a structure pointer, as in
 *
 *   struct key *binsearch(char *word, struct key *tab, int n)
 * the function name can be hard to see, and to find with a text editor.
 * Accordingly an alternate style is sometimes used:
 *
 *   struct key *
 *   binsearch(char *word, struct key *tab, int n)
 * This is a matter of personal taste; pick the form you like and hold to it.
 */

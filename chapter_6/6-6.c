/***
 * Implement a simple version of the #define processor (i.e., no arguments)
 * suitable for use with C programs, based on the routines of this section. You
 * may also find getch and ungetch helpful.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define HASHSIZE 101

struct nlist {        /* table entry */
  struct nlist *next; /* next entry in the chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

static char buf[MAXWORD];
static char *bufp = buf;
static struct nlist *hashtab[HASHSIZE];

void error(int, char *);
int getch(void);
void getdef(void);
int getword(char *, int);
unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
void skipblanks(void);
void undef(char *);
void ungetch(int);
void ungets(char *);
void freetable(void);

int main(void) {
  char w[MAXWORD];
  struct nlist *p;

  while (getword(w, MAXWORD) != EOF)
    if (strcmp(w, "#") == 0) /* beginning of direct. */
      getdef();
    else if (!isalpha(w[0]))
      printf("%s", w); /* cannot be defined */
    else if ((p = lookup(w)) == NULL)
      printf("%s", w); /* not defined */
    else
      ungets(p->defn); /* push definition */
  return 0;
}

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *p;
  unsigned hashval;
  char *newname = NULL;
  char *newdef = NULL;

  p = lookup(name);
  if (p == NULL) { /* does not exist, create a new entry */
    p = (struct nlist *)malloc(sizeof(*p));
    if (p == NULL) {
      fprintf(stderr, "install failed\n");
      return NULL;
    }
    newname = strdup(name);
    if (newname == NULL) {
      free(p);
      return NULL;
    }
    newdef = strdup(defn);
    if (newdef == NULL) {
      free(newname);
      free(p);
      return NULL;
    }
    hashval = hash(name);
    p->name = newname;
    p->defn = newdef;
    p->next = hashtab[hashval];
    hashtab[hashval] = p;
  } else { /* entry exists, supersede the definition */
    newdef = strdup(defn);
    if (newdef == NULL)
      return NULL;
    free(p->defn);
    p->defn = newdef;
  }
  return p;
}

struct nlist *lookup(char *name) {
  struct nlist *p;

  for (p = hashtab[hash(name)]; p != NULL; p = p->next)
    if ((strcmp(p->name, name)) == 0)
      return p;
  return NULL;
}

void undef(char *name) {
  unsigned hashval = hash(name);
  struct nlist *curr = hashtab[hashval]; /* points to the head of the bucket */
  struct nlist *prev = NULL;             /* NULL as curr points to the head */

  while (curr != NULL) {                 /* traverse the linked list */
    if (strcmp(curr->name, name) == 0) { /* found a match */
      if (prev == NULL)                  /* node to remove at the head */
        hashtab[hashval] = curr->next;   /* update head to be the next node */
      else /* otherwise, bypass the current node */
        prev->next = curr->next;
      free(curr->name); /* free allocated resources */
      free(curr->defn);
      free(curr);
      return; /* exit early */
    }
    // advance pointers
    prev = curr;
    curr = curr->next;
  }
  fprintf(stderr, "definition not found\n"); /* the name was not found */
}

void freetable(void) {
  struct nlist *p, *next;
  int i;

  for (i = 0; i < HASHSIZE; i++) {
    for (p = hashtab[i]; p != NULL; p = next) {
      next = p->next;
      free(p->name);
      free(p->defn);
      free(p);
    }
    hashtab[i] = NULL;
  }
}

int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()) && c != '\n')
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

int getch(void) { return (bufp - buf > 0) ? *--bufp : getchar(); }

void ungetch(int c) {
  if (c == EOF)
    return;
  if (bufp - buf >= MAXWORD)
    printf("ungetch: too many characters\n");
  else
    *bufp++ = c;
}

/* getdef: get definition and install it */
void getdef(void) {
  int c, i;
  char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

  skipblanks();
  if (!isalpha(getword(dir, MAXWORD)))
    error(dir[0], "getdef: expecting a directive after #");
  else if (strcmp(dir, "define") == 0) {
    skipblanks();
    if (!isalpha(getword(name, MAXWORD)))
      error(name[0], "getdef: non-alpha - name expected");
    else {
      skipblanks();
      for (i = 0; i < MAXWORD - 1; i++)
        if ((def[i] = getch()) == EOF || def[i] == '\n')
          break; /* end of definition */
      def[i] = '\0';
      if (i <= 0) /* no definition? */
        error('\n', "getdef: incomplete define");
      else
        install(name, def); /* install definition */
    }
  } else if (strcmp(dir, "undef") == 0) {
    skipblanks();
    if (!isalpha(getword(name, MAXWORD)))
      error(name[0], "getdef: non-alpha in undef");
    else
      undef(name);
  } else {
    error(dir[0], "getdef: expecting a directive after #");
  }
}

/* error: print error message and skip the rest of the line */
void error(int c, char *s) {
  printf("error: %s\n", s);
  while (c != EOF && c != '\n')
    c = getch();
}

/* skipblanks: skip blank and tab characters */
void skipblanks(void) {
  int c;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  ungetch(c);
}

void ungets(char *s) {
  int i = strlen(s);

  while (i)
    ungetch(*(s + (--i)));
}

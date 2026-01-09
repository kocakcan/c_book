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
  struct nlist *key = install("NAME", "Can");
  if (key == NULL) {
    fprintf(stderr, "install failed mate\n");
    return 1;
  }
  struct nlist *query = lookup("NAME");
  if (query == NULL) {
    fprintf(stderr, "definition not found\n");
    freetable();
    return 1;
  }
  printf("%s is mapped to %s\n", query->name, query->defn);
  freetable();

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
  struct nlist *curr = hashtab[hashval];
  struct nlist *prev = NULL;

  while (curr != NULL) {
    if (strcmp(curr->name, name) == 0) {
      if (prev == NULL)
        hashtab[hashval] = curr->next;
      else
        prev->next = curr->next;
      free(curr->name);
      free(curr->defn);
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  fprintf(stderr, "definition not found\n");
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

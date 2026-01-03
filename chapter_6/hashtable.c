#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
void freetable(void);

/* hash: from hash value for string s */
unsigned hash(const char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(const char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(const char *name, const char *defn) {
  struct nlist *np;
  unsigned hashval;
  char *newname = NULL;
  char *newdef = NULL;

  np = lookup(name);
  if (np == NULL) { /* not found, create a new entry */
    np = malloc(sizeof(*np));
    if (np == NULL)
      return NULL;
    newname = strdup(name);
    if (newname == NULL) {
      free(np);
      return NULL;
    }
    newdef = strdup(defn);
    if (newdef == NULL) {
      free(newname);
      free(np);
      return NULL;
    }
    hashval = hash(name);
    np->name = newname;
    np->defn = newdef;
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else { /* already exists, supersede the entry */
    newdef = strdup(defn);
    if (newdef == NULL)
      return NULL;
    free(np->defn);
    np->defn = newdef;
  }
  return np;
}

int main(void) {
  struct nlist *first = install("NAME", "Can");
  if (first == NULL) {
    fprintf(stderr, "install failed\n");
    return 1;
  }
  struct nlist *result = lookup("NAME");
  if (result == NULL) {
    fprintf(stderr, "lookup not found\n");
    freetable();
    return 1;
  }
  struct nlist *occupation = install("OCCUPATION", "Software Engineer");
  if (occupation == NULL) {
    fprintf(stderr, "install failed\n");
    return 1;
  }
  struct nlist *value = lookup("OCCUPATION");
  printf("%s is mapped to %s\n", result->name, result->defn);
  printf("%s is mapped to %s\n", value->name, value->defn);
  freetable();

  return 0;
}

void freetable(void) {
  struct nlist *np, *next;
  int i;

  for (i = 0; i < HASHSIZE; i++) {
    for (np = hashtab[i]; np != NULL; np = next) {
      next = np->next;
      free(np->name);
      free(np->defn);
      free(np);
    }
    hashtab[i] = NULL;
  }
}

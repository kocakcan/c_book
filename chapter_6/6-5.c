/***
 * Write a function undef that will remove a name and definition from the table
 * maintained by lookup and install.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(const char *);
struct nlist *install(const char *, const char *);
struct nlist *lookup(const char *);
void freetable(void);
void undef(const char *);

int main(void) {
  struct nlist *key = install("NAME", "Can");
  if (key == NULL) {
    fprintf(stderr, "install failed\n");
    return 1;
  }
  struct nlist *query = lookup("NAME");
  if (query == NULL) {
    fprintf(stderr, "query not found\n");
    freetable();
    return 1;
  }
  struct nlist *test = install("TEST", "BEST");
  if (!test)
    return 1;
  struct nlist *result = lookup("TEST");
  if (!result) {
    freetable();
    return 1;
  }
  printf("%s is mapped to %s\n", query->name, query->defn);
  printf("%s is mapped to %s\n", result->name, result->defn);
  undef("TEST");
  if (lookup("TEST") == NULL)
    printf("TEST was successfully removed!\n");
  else
    printf("TEST still present :/n");
  freetable();

  return 0;
}

unsigned hash(const char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *install(const char *name, const char *defn) {
  unsigned hashval;
  struct nlist *np;
  char *newname = NULL;
  char *newdef = NULL;

  np = lookup(name);
  if (np == NULL) { /* does not exist, create a new entry */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL)
      return NULL;
    newname = strdup(name);
    if (newname == NULL) {
      free(np);
      return NULL;
    }
    newdef = strdup(defn);
    if (newdef == NULL) {
      free((void *)newname);
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

struct nlist *lookup(const char *name) {
  struct nlist *np;

  for (np = hashtab[hash(name)]; np != NULL; np = np->next)
    if ((strcmp(np->name, name)) == 0)
      return np;
  return NULL;
}

void undef(const char *name) {
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
  fprintf(stderr, "definition not found!\n");
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

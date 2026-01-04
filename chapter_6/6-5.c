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

/***
 * 6.7 Typedef
 *
 * C provides a facility called typedef for creating new data type names. For
 * example, the declaration
 *
 *  typedef int Length;
 * makes the name Length a synonym for int. The type Length can be used in
 * declarations, casts, etc., in exactly the same ways that the int type can
 * be:
 *
 *  Length len, maxlen;
 *  Length *lengths[];
 * Similarly, the declaration
 *
 *  typedef char *String;
 * makes String a synonym for char * or character pointer, which may then be
 * used in declarations and casts:
 *
 *  String p, lineptr[MAXLINES], alloc(int);
 *  int strcmp(String, String);
 *  p = (String) malloc(100);
 * Notice that the type being declared in a typedef appears in the position of
 * a variable name, not right after the word typedef. Syntactically, typedef is
 * like the storage classes extern, static, etc. Using capitalized names for
 * typedefs makes them stand out.
 *
 * As a more complicated example, we could make typedefs for the tree nodes
 * shown earlier in this chapter:
 *
 *  typedef struct tnode *Treeptr;
 *
 *  typedef struct tnode {  -> the tree node
 *    char *word;           -> points to the text
 *    int count;            -> number of occurrences
 *    struct tnode *left;   -> left child
 *    struct tnode *right;  -> right child
 *  } Treenode;
 * This creates two new type keywords called Treenode (a structure) and Treeptr
 * (a pointer to the structure). Then the routine talloc could become
 *
 *  Treeptr talloc(void) {
 *    return (Treeptr) malloc(sizeof(Treenode));
 *  }
 * It must be emphasized that a typedef declaration does not create a new type
 * in any sense; it merely adds a new name for some existing type. Nor are there
 * any new semantics: variables declared this way have exactly the same
 * properties as variables whose declarations are spelled out explicitly. In
 * effect, typedef is like #define, except that since it is interpreted by the
 * compiler, it can cope with textual substitutions that are beyond the
 * capabilities of the preprocessor. For example,
 *
 *  typedef int (*PFI)(char *, char *);
 * creates the type PFI, for "pointer to function (of to char * arguments)
 * returning int," which can be used in contexts like
 *
 *  PFI strcmp, numcmp
 * Besides purely aesthetic issues, there are two main reasons for using
 * typedefs. The first is to parameterize a program against portability
 * problems. If typedefs are used for data types that may be machine-dependent,
 * only the typedefs need change when the program is moved. One common situation
 * is to use typedef names for various integer quantities, then make an
 * appropriate set of choices of short, int, and long for each host machine.
 * Types like size_t and ptrdiff_t from the standard library are examples.
 *
 * The second purpose of typedefs is to provide better documentation for a
 * program - a type called Treeptr may be easier to understand than one declared
 * only as a pointer to a complicated structure.
 */
#include <stdio.h>
#include <stdlib.h>

#define TEAM_SIZE 5

typedef char *String;

typedef struct {
  String name;
  int health;
  int ad;
  int speed;
  int defense;
  float luck;
} Expeditioner;

static Expeditioner expedition_33[TEAM_SIZE] = {
    {"Verso", 756, 700, 450, 600, 0.1f},
    {"Lune", 950, 400, 238, 371, 0.05f},
    {"Maelle", 1742, 749, 321, 826, 0.15f},
    {"Sciel", 1289, 629, 311, 499, 0.05f},
    {"Monoco", 400, 632, 354, 411, 0.05f}};

void printe(Expeditioner *);
int get_max_ad(Expeditioner *);
int strcmp_(const char *, const char *);
int namecmp(const void *, const void *);

int main(void) {
  printf("Max AD amongst expeditioners is: %d\n", get_max_ad(expedition_33));
  qsort(expedition_33, TEAM_SIZE, sizeof(Expeditioner), namecmp);
  printe(expedition_33);
  return 0;
}

/* printe: print the names of the Expeditioners */
void printe(Expeditioner *e) {
  for (size_t i = 0; i < TEAM_SIZE; i++)
    printf("Name: %s\n", e++->name);
}

int get_max_ad(Expeditioner *e) {
  int max = e++->ad;

  for (size_t i = 1; i < TEAM_SIZE; i++) {
    if (e->ad > max)
      max = e->ad;
    e++;
  }
  return max;
}

int strcmp_(const char *s, const char *t) {
  while (*s && *s == *t)
    s++, t++;
  return (unsigned char)*s - (unsigned char)*t;
}

int namecmp(const void *s, const void *t) {
  const Expeditioner *a = (const Expeditioner *)s;
  const Expeditioner *b = (const Expeditioner *)t;
  return strcmp_(a->name, b->name);
}

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
 */
#include <stdio.h>

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

int main(void) {
  printe(expedition_33);
  printf("Max AD amongst expeditioners is: %d\n", get_max_ad(expedition_33));
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

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

#define TEAM_SIZE 4

typedef char *String;

static String expedition_33[TEAM_SIZE] = {"Lune", "Maelle", "Sciel", "Verso"};

void printk(String *);

int main(void) {
  printk(expedition_33);
  return 0;
}

void printk(String *s) {
  for (size_t i = 0; i < TEAM_SIZE; i++)
    printf("%s\n", *s++);
}

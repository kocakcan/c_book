#include <stdio.h>
#include <stdlib.h>

typedef struct {
  const char *name;
  int age;
  const char *occupation;
} People;

const char *get_name(const People *ppl);
void alter_age(People *ppl, const int new_age);
const int get_age(const People *ppl);

int main(void) {
  const int int_constant = 19;

  printf("The size of constant int: %ld bits\n", (sizeof(int_constant) * 8));
  printf("The size of constant long int: %ld bits\n", (sizeof(19L) * 8));
  printf("The size of constant unsigned long int: %ld bits\n",
         (sizeof(19UL) * 8));
  // floating-point constants are double by default unless suffixed by f or F.
  printf("The size of constant double: %ld bits\n", (sizeof(3.1425) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425f) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425F) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(3.1425F) * 8));
  // in order for the constant to be float it must be suffixed
  printf("The size of constant float with exponent: %ld bits\n",
         (sizeof(1e-2f) * 8));
  printf("The size of constant float: %ld bits\n", (sizeof(1e-2) * 8));

  const int octal_const = 017;
  const int hex_const = 0x16;
  const int another_hex_const = 0xFUL;
  printf("My first octal number is: %o\n", octal_const);
  printf("My first octal number is: %d\n", octal_const);
  printf("My first hex number is: %hx\n", hex_const);
  printf("My first hex number is: %d\n", hex_const);
  printf("My first hex number is: %hx\n", another_hex_const);
  printf("My first hex number is: %d\n", another_hex_const);

  const int thirty_one = 0x1F; // 31
  printf("This should be equal to 31: %d\n", thirty_one);

  People *can = malloc(sizeof(People));
  can->name = "Can";
  can->age = 27;
  can->occupation = NULL;

  printf("My age is: %d\n", get_age(can));
  printf("My name is: %s\n", get_name(can));
  alter_age(can, 19);
  printf("My new age is: %d\n", get_age(can));
  int *ptr = malloc(sizeof(int));

  // if (ptr != (void *)0) {
  //   *ptr = 19;
  // }

  if (ptr != 0) {
    *ptr = 19;
  }

  printf("My pointer points to: %d\n", *ptr);

  free(ptr);
  free(can);
}

const char *get_name(const People *ppl) { return ppl->name; }
void alter_age(People *ppl, const int new_age) { ppl->age = new_age; }
const int get_age(const People *ppl) { return ppl->age; }

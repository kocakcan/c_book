#include <stdio.h>
#include <string.h>

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING,
} DataType;

typedef struct {
  DataType type;
  union {
    int i;
    float f;
    char s[32];
  } value;
} Variant;

void printv(Variant v) {
  switch (v.type) {
  case TYPE_INT:
    printf("int: %d\n", v.value.i);
    break;
  case TYPE_FLOAT:
    printf("float: %f\n", v.value.f);
    break;
  case TYPE_STRING:
    printf("string: %s\n", v.value.s);
    break;
  }
}

int main(void) {
  Variant a = {.type = TYPE_INT, .value.i = 100};
  Variant b = {.type = TYPE_FLOAT, .value.f = 2.718f};
  Variant c = {.type = TYPE_STRING, .value.s = "hello"};

  printv(a);
  printv(b);
  printv(c);
  return 0;
}

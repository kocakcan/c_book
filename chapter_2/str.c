#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
} Rectangle;

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  const char *buffer;
  size_t len;
} String;

double get_circumference(Rectangle *rect);

// Pass by value (inefficient for large structs)
void move_point(Point p) {
  p.x++;
  p.y++;
  // Modifications to p do not affect the original struct
}

// Pass by ponter (allows modification)
void move_point_ref(Point *p) {
  p->x++;
  p->y++;
  // Modifications afffect the original struct
}

typedef struct {
  const char *name;
  int age;
  const char *occupation;
} People;

typedef struct {
  People people;
  const char *plang;
} Engineer;

void increment(int *x) { (*x)++; }

size_t get_len(String *str);
int main(void) {
  Point p1 = {3, 4};
  Point p2 = {5, 6};
  People can = {
      "Can",
      27,
      "Software Engineer",
  };

  printf("p1.x = %d, p2.y = %d\n", p1.x, p1.y);
  move_point(p1);
  printf("p1.x = %d, p2.y = %d\n", p1.x, p1.y);
  move_point_ref(&p1);
  printf("p1.x = %d, p2.y = %d\n", p1.x, p1.y);

  printf("My name is %s\n", can.name);
  int num = 19;

  printf("num before: %d\n", num);
  increment(&num);
  printf("num before: %d\n", num);

  char buffer[100];

  buffer[0] = 'C';
  buffer[1] = 'a';
  buffer[2] = 'n';
  buffer[3] = '\0';
  double result = sin(30);
  // double x = 184467440737095516164139764.0;
  // printf("Result is: %f\n", x);
  printf("Result is: %f\n", result);
  printf("double: %ld bits\n", (sizeof(double) * 8));
  printf("float: %ld bits\n", (sizeof(float) * 8));
  printf("%s\n", buffer);
  People *yo = malloc(sizeof(People));
  yo->name = "Can";
  yo->age = 39;
  yo->occupation = "Software Engineer";

  printf("I am a %s\n", yo->occupation);
  Engineer *eng = malloc(sizeof(Engineer));
  eng->people.occupation = "Engineer";
  eng->people.name = "Can";
  eng->people.age = 27;
  eng->plang = "C";

  Rectangle *rect = malloc(sizeof(Rectangle));
  rect->x = 5.0;
  rect->y = 4.0;
  printf("The circumference is: %f\n", get_circumference(rect));

  printf("My name is %s\n", eng->people.name);
  printf("My favourite programming language is: %s\n", eng->plang);
  String *str = malloc(sizeof(String));
  str->buffer = "Can";
  str->len = get_len(str);

  printf("My buffer is: %s\n", str->buffer);
  printf("Its length is: %ld\n", str->len);
  free(yo);
  free(eng);
  free(rect);
  free(str);
}

double get_circumference(Rectangle *rect) { return 2 * (rect->x + rect->y); }
size_t get_len(String *str) {
  size_t i = 0;

  while (str->buffer[i] != '\0')
    ++i;

  return i;
}

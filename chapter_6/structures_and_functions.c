/***
 * 6.2 Structures and Functions
 *
 * The only legal operations on a structure are copying it or assigning to it as
 * a unit, takings its address with &, and accessing its members. Copy and
 * assignment include passing arguments to functions and returning values from
 * functions as well. Structures may not be compared; an automatic structure may
 * also be initialized by an assignment.
 *
 * Let us investigate structures by writing some functions to manipulate points
 * and rectangles. There are at least three possible approaches: pass components
 * seperately, pass an entire structure, or pass a pointer to it. Each has its
 * good points and bad points.
 *
 * The first function, makepoint, will take two integers and return a point
 * structure.
 *
 * makepoint: make a point from x and y components
 * struct point makepoint(int x, int y) {
 *  struct point temp;
 *
 *  temp.x = x;
 *  temp.y = y;
 *  return temp;
 * }
 *
 * Notice that there is no conflict between the argument name and the member
 * with the same name; indeed the re-use of the names stresses the
 * relationship.
 *
 * makepoint can now be used to initialize any structure dynamically, or to
 * provide structure arguments to a function:
 *
 *  struct rect screen;
 *  struct point middle;
 *  struct point makepoint(int, int);
 *
 *  screen.pt1 = makepoint(0, 0);
 *  screen.pt2 = makepoint(XMAX, YMAX);
 *  middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
 *                     (screen.pt1.y + screen.pt2.y) / 2);
 * The next step is a set of functions to do arithmetic on points. For
 * instance,
 *
 *  addpoints: add two points
 *  struct addpoint(struct point p1, struct point p2) {
 *   p1.x += p2.x;
 *   p1.y += p2.y;
 *   return p1;
 *  }
 * Here both the arguments and the return value are structures. We incremented
 * the components in p1 rather than using an explicit temporary variable to
 * emphasize that structure parameters are passed by value like any others.
 */
#include <stdio.h>
#define XMAX 1920
#define YMAX 1200

struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};

/* makepoint: make a component from x and y components */
struct point makepoint(int x, int y) {
  struct point temp;

  temp.x = x;
  temp.y = y;
  return temp;
}

int main(void) {
  struct rect screen;
  struct point middle;

  screen.pt1 = makepoint(0, 0);
  screen.pt2 = makepoint(XMAX, YMAX);
  middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                     (screen.pt1.y + screen.pt2.y) / 2);

  printf("Middle point of the screen (x, y) = (%d, %d)\n", middle.x, middle.y);

  return 0;
}

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
 *
 * As another example, the function ptinrect tests whether a point is inside a
 * rectangle, where we have adopted the convention that a rectangle includes
 * its left and bottom sides but not its top and right sides:
 *
 *  ptinrect: return 1 if p in r, 0 if not
 *  int ptinrect(struct point p, struct rect r) {
 *    return p.x >= r.pt1.x && p.x < r.pt2.x
 *        && p.y >= r.pt1.y && p.y < r.pt2.y;
 *  }
 * This assumes that the rectangle is presented in a standard form where the
 * pt1 coordinates are less than pt2 coordinates. The following function
 * returns a rectangle guaranteed to be in canonical form:
 *
 *  #define min(a, b) ((a) < (b) ? (a) : (b))
 *  #define max(a, b) ((a) > (b) ? (a) : (b))
 *
 *  canonrect: canonicalize coordinates of rectangle
 *  struct rect canonrect(struct rect r) {
 *    struct rect temp;
 *
 *    temp.pt1.x = min(r.pt1.x, r.pt2.x);
 *    temp.pt1.y = min(r.pt1.y, r.pt2.y);
 *    temp.pt2.x = max(r.pt1.x, r.pt2.x);
 *    temp.pt2.y = max(r.pt1.y, r.pt2.y);
 *    return temp;
 *  }
 * If a large structure is to be passed to a function, it is generally more efficient to pass a pointer than to copy the whole structure. Structure pointers are just like pointers to ordinary variables. The declaration
 * 	
 * 	struct point *pp;
 * says that pp is a pointer to a structure of type struct point. If pp points to a point structure, *pp is the structure, and (*pp).x and (*pp).y are the members. To use pp, we might write, for example,
 *
 * 	struct point origin, *pp;
 * 	pp = &origin;
 * 	printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);
 * The parantheses are necessary in (*pp).x because the precedence of the structure member operator . is higher than *. The expression *pp.x means *(pp.x), which is illegal here because x is not a pointer.
 *
 * Pointers to structures are so frequently used that an alternative notation is provided as a shorthand. If p is a pointer to a structure, then
 *
 * 	p->member-of-structure
 * refers to the particular member. So we could write instead
 *
 * 	printf("origin is (%d,%d)\n", pp->x, pp->y);
 * Both . and -> associate from left to right, so if we have
 *
 * 	struct rect r, *rp = &r;
 * then these four expression are equivalent:
 *
 * 	r.pt1.x
 * 	rp->pt1.x
 * 	(r.pt1).x
 * 	(rp->pt1).x
 * The structure operators . and ->, together with () for function calls and [] for subscripts are at the top of the precedence hierarchy and thus bind very tightly. For example, given the declaration
 *
 * 	struct {
 * 		int len;
 * 		char *str;
 * 	} *p;
 * then
 *
 * 	++p->len
 * increments len, not p, because the implied parenthesization is ++(p->len). Parentheses can be used to alter binding: (++p)->len increments p before accessing len, and (p++)->len increments p afterward. (The last set of parentheses are unnecessary)
 *
 * In the same way, *p->str fetches whatever str points to; *p->str++ increments str after accessing whatever it points to (just like *s++); (*p->str)++ increments whatever str points to; and *p++->str increments p after accessing whatever str points to.
 */
#include <stdio.h>
#define XMAX 1920
#define YMAX 1200
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

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

/* addpoints: add two points */
struct point addpoints(struct point p1, struct point p2) {
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r) {
	return p.x >= r.pt1.x && p.x < r.pt2.x
	    && p.y >= r.pt1.y && p.y < r.pt2.y;
}

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r) {
	struct rect temp;

	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
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

  struct point pt3 = addpoints(screen.pt1, screen.pt2);
  struct point pt4 = makepoint(197, 42);
  struct point pt5 = makepoint(15, 1921);
  struct rect canrect = canonrect(screen);
  printf("screen.pt1 + screen.pt2 = (%d, %d)\n", pt3.x, pt3.y);
  printf("pt4(%d, %d) %s in screen\n", pt4.x, pt4.y, (ptinrect(pt4, screen) == 1) ? "is" : "is not");
  printf("pt5(%d, %d) %s in screen\n", pt5.x, pt5.y, (ptinrect(pt5, screen) == 1) ? "is" : "is not");
  printf("canrect((%d, %d), (%d, %d))\n", canrect.pt1.x, 
	canrect.pt1.y, canrect.pt2.x, canrect.pt2.y);

  return 0;
}

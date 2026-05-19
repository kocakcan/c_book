/* Write a routine bfree(p, n) that will free an arbitrary block p of n
 * characters into the free list maintained by malloc and free. By using bfree,
 * a user can add a static or external array to the free list at any time. */
#include <stdlib.h>
#include <unistd.h>

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;
/* bfree: free an arbitrary block p of n chars */
unsigned bfree(char *p, unsigned n) {
  Header *hp;

  if (n < sizeof(Header))
    return 0; /* too small to be useful */
  hp = (Header *)p;
  hp->s.size = n / sizeof(Header);
  free((void *)(hp + 1));
  return hp->s.size;
}

/*** The routine bfree takes two arguments: a pointer p and a number of
 * characters n. It will free the block only if its size is at least
 * sizeof(Header), otherwise it returns 0. The pointer p is cast to Header type
 * and assigned to hp:
 *
 *   hp->s.size * n / sizeof(Header);
 * The last step calls the function free. Since free expects the pointer to be
 * just past the header area, we use (hp + 1), as morecore does, and cast it to
 * type (void *). The routine bfree returns 0 if the block is too small,
 * otherwise it returns the size of the block in sizeof(Header) units.
 */

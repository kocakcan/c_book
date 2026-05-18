/* malloc accepts a size request without checking its plausibility; free
 * believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pairs with error checking. */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXBYTES (unsigned)10240

typedef long Align; /* for alignment to long boundary */

union header { /* block header */
  struct {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x;
};

typedef union header Header;

static unsigned maxalloc;    /* max number of units allocated */
static Header base;          /* empty list to get started */
static Header *freep = NULL; /* start of free list */
static Header *_morecore(unsigned);
void _free(void *);

/* _malloc: general-purpose storage allocator */
void *_malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  if (nbytes > MAXBYTES) { /* not more than MAXBYTES */
    fprintf(stderr, "alloc: can't allocate more than %u bytes\n", MAXBYTES);
    return NULL;
  }
  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) { /* no free list yet */
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {   /* big enough */
      if (p->s.size == nunits) { /* exactly */
        prevp->s.ptr = p->s.ptr;
      } else { /* allocate tail end */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) /* wrapped around free list */
      if ((p = _morecore(nunits)) == NULL)
        return NULL; /* none left */
  }
}

#define NALLOC 1024 /* minimum units to request */

/* _morecore: ask system for more memory */
static Header *_morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) { /* no space at all */
    return NULL;
  }
  up = (Header *)cp;
  up->s.size = nu;
  maxalloc = (up->s.size > maxalloc) ? up->s.size : maxalloc;
  _free((void *)(up + 1));
  return freep;
}

/* _free: put block ap in free list */
void _free(void *ap) {
  Header *bp, *p;

  bp = (Header *)ap - 1; /* point to block header */
  if (bp->s.size == 0 || bp->s.size > maxalloc) {
    fprintf(stderr, "free: can't free %u units\n", bp->s.size);
    return;
  }
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;                         /* freed block at start or end of arena */
  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }
  if (p + p->s.size == bp) { /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

int main(void) {
  char *band = _malloc(1024);
  if (band == NULL) {
    fprintf(stderr, "_malloc: failed to allocate memory!\n");
    return 1;
  }
  strcpy(band, "Amon Amarth");
  printf("My favourite band is %s\n", band);
  _free(band);
  return 0;
}

/***
 * 5.4 Address Arithmetic
 *
 * If p is a pointer to some element of an array, then p++ increments p to
 * point to the next element, and p += i increments it to point i elements
 * beyond where it currently does. These an similar constructions are the
 * simplest forms of pointer or address arithmetic.
 *
 * C is consistent and regular in its approach to address arithmetic; its
 * integration of pointers, arrays, and address arithmetic is one of the
 * strengths of the language. Let us illustrate by writing a rudimentary
 * storage allocator. There are two routines. The first, alloc(n), returns a
 * pointer to n consecutive character positions, which can be used by the
 * caller of alloc for storing characters. The second, afree(p), releases the
 * storage thus acquired so it can be re-used later. The routines are
 * "rudimentary" because the calls to afree must be made in the opposite order
 * to the calls made on alloc. That is, the storage managed by alloc and afree
 * is a stack, or last-int, first-out. The standard library provides analogous
 * functions called malloc and free that have no such restrictions.
 *
 * The easiest implementation is to have alloc hand out pieces of a large
 * character array that we will call allocbuf. This array is private to alloc
 * and afree. Since they deal in pointers, not array indices, no other routine
 * need to know the name of the array, which can be declared static in the
 * source file containing alloc and afree, and thus be invisible outside it. In
 * practical implementations, the array may well not even have a name; it might
 * instead be obtained by calling malloc or by asking the operating system for
 * a pointer to some unnamed block of storage.
 *
 * The other information needed is how much of allocbuf has been used. We use a
 * pointer, calloc allocp, that points to the next free element. When alloc is
 * asked for n characters, it checks to see if there is enough room left in
 * allocbuf. If so, alloc returns the current value of allocp (i.e., the
 * beginning of the free block), then increments it by n to point to the next
 * free area. If there is no room, alloc returns zero. afree(p) merely sets
 * allocp to p if p is inside allocbuf.
 *
 * In general a pointer can be initialized just as any other variable can,
 * though normally the only meaningful values are zero or an expression
 * involving the address of previously defined data of appropriate type. The
 * declaration
 *
 * 	static char *allocp = allocbuf;
 * defines allocp to be a character pointer and initializes it to point to the
 * beginning of allocbuf, which is the next free position when the program
 * starts. This could also have been written
 *
 * 	static char *allocp = &allocbuf[0];
 * since the array name is the address of the zeroth element.
 *
 * The test
 *
 * 	if (allocbuf + ALLOCSIZE - allocp >= n)
 * checks if there's enough room to satisfy a request for n characters. If
 * there is, the new value of allocp would be at most one beyond the end of
 * allocbuf. If the request can be satisfied, alloc returns a pointer to the
 * beginning of a block of characters (notice the declaration of the function
 * itself). If not, alloc must return some signal that there is no space left.
 * C guarantees that zero is never a valid address for data, so a return value
 * of zero can be used to signal an abnormal event, in this case no space.
 */
#include <stdio.h>
#define ALLOCSIZE	10000		/* size of available space */

static char allocbuf(ALLOCSIZE);	/* storage for alloc */
static char *allocp = allocbuf;		/* next free position */

char *alloc(int n)			/* return pointer to n characters */{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	/* if it fits */
		allocp += n;
		return allocp - n;			/* old p */
	} else {
		return 0;
	}
}

void afree(char *p)			/* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuc + ALLOCSIZE)
		allocp = p;
}

int main(void) {
	int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	printf("First element of arr: %d\n", *(arr + 0));
	printf("Second element of arr: %d\n", *(arr + 1));
	printf("Last element of arr: %d\n", *(arr + size - 1));

	return 0;
}

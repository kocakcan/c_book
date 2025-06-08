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
 */
#include <stdio.h>

int main(void) {
	int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	printf("First element of arr: %d\n", *(arr + 0));
	printf("Second element of arr: %d\n", *(arr + 1));
	printf("Last element of arr: %d\n", *(arr + size - 1));

	return 0;
}

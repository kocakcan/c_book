/* The standard library function calloc(n, size) returns a pointer to n objects o size size, with the storage initialized to zero. Write calloc, by calling malloc or by modifying it */
#include <unistd.h>
#include <stdlib.h>

/* _calloc: allocate n objects of size size */
void *_calloc(unsigned n, unsigned size) {
	unsigned i, nb;
	char *p, *q;

	nb = n * size;
	if ((p = q = malloc(nb)) != NULL)
		for (i = 0; i < nb; i++)
			*p++ = 0;
	return q;
}
/***
 * The function calloc allocates n objects of size size. The total numb-
 * er of bytes to be allocates is nb:
 *
 * 	nb = n * size;
 * malloc returns a pointer to a storage area of nb bytes. The pointers
 * p and q remember the beginning of this allocated storage area. If the
 * allocation was successful, the nb bytes are initialized to 0:
 *
 * 	for (i = 0; i < nb; i++)
 * 		*p++ = 0;
 * calloc returns a pointer to the beginning of the allocated an initia-
 * lized storage area.
 */

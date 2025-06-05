/***
 * 5.3 Pointers and Arrays
 *
 * In C, there is a strong relationship between pointers and arrays, strong
 * enough that pointers and arrays should be discussed simultaneously. Any
 * operation that can be achieved by array subscripting can also be done with
 * pointers. The pointer version will in general be faster but, at least to the
 * uninitiated, somewhat harder to understand.
 *
 * The declaration,
 *
 *   int a[10];
 * defines an array of size 10, that is, a block of 10 consecutive objects names
 * a[0], a[1], ..., a[9].
 * The notation a[i] refers to the i-th element of the array. If pa is a
 * pointer to an integer, declared as
 *
 * 	int *pa;
 * then the assignment
 *
 * 	pa = &a[0];
 * sets pa to point to element zero of a; that is, pa contains the address of
 * a[0].
 * Now the assignment
 *
 * 	x = *pa;
 * will copy the contents of a[0] into x.
 *
 * If pa points to a particular element of an array, then by definition pa+1
 * points to the next element, pa+i points i elements after pa, and pa-i points
 * i elements before. Thus, if pa points to a[0],
 *
 * 	*(pa+1)
 * refers to the contents of a[1], pa+i is the address of a[i], and *(pa+i) is
 * the contents of a[i].
 *
 * These remarks are true regardless of the type or size of the variables in
 * array a. The meaning of "adding 1 to a pointer" and by extension, all
 * pointer arithmetic, is that pa+1 points to the next object, and pa+i points
 * to the i-th object beyond pa.
 *
 * The correspondence between indexing and pointer arithmetic is very close. By
 * definition, the value of a variable or expression of type array is the
 * address of element zero of the array. Thus after the assignment
 *
 * 	pa = &a[0];
 * pa and a have identical values. Since the name of an array is an synonym for
 * the location of the initial element, the assignment pa=&a[0] can also be
 * written as
 *
 * 	pa = a;
 * Rather more surprising, at first sight, is the fact that a reference to a
 * [i] can also be written as *(a+i). In evaluating a[i], C converts it to
 * *(a+i) immediately; the two forms are equivalent. Applying the operator
 */

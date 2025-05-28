/***
 * 5.2 Pointers and Function Arguments
 *
 * Since C passes arguments to functions by value, there is no direct way for
 * the called function to alter a variable in the calling function. For
 * instance, a sorting routine might exchange two out-of-order arguments with a
 * function called swap. It is not enough to write
 *
 *   swap(a, b);
 * where the swap function is defined as
 *
 *   void swap(int x, int y) { -> WRONG
 *     int temp;
 *
 *     temp = x;
 *     x = y;
 *     y = temp;
 *   }
 * Because of call by value, swap can't affect the arguments a and b in the
 * routine that called it. The function above swaps copies of a and b.
 *
 * The way to obtain the desired effect is for the calling program to pass
 * pointers to the values to be changed:
 *
 *   swap(&a, &b);
 * Since the operator & produces the address of a variable, &a is a pointer to
 * a. In swap itself, the parameters are declared as pointers, and the operands
 * are accessed indirectly through them.
 *
 *   void swap(int *px, int *py) {
 *     int temp;
 *
 *     temp = *px;
 *     *px = *py;
 *     *py = temp;
 *   }
 */

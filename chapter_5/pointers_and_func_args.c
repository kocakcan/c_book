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
 *
 * Pointer arguments enable a function to access and change objects in the
 * function that called it. As an example, consider a function getint that
 * performs free-format input conversion by breaking a stream of characters
 * into integer values, one integer per call. getint has to return the value it
 * found and also signal end of file when there is no more input. These values
 * have to be passed back by seperate paths, for no matter what value is used
 * for EOF, that could also be the value of an input integer.
 *
 * One solution is to have getint return the end of file status as its function
 * value, while using a pointer argument to store the converted integer back
 * in the calling function. This is the scheme used by scanf as well.
 *
 * The following loop fills an array with integers by calls to getint:
 *
 *  int n, array[SIZE], getint(int *);
 *
 *  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
 *    ;
 *
 * Each call sets array[n] to the next integer found in the input and
 * increments n. Notice that it is essential to pass the address of array[n] to
 * getint. Otherwise there is no way for getint to communicate the converted
 * integer back to the caller.
 *
 * Our version of getint returns EOF for end of file, zero if the next input is
 * not a number, and a positive number if the input contains a valid number.
 */
#include <ctype.h>
#include <stdio.h>

extern int getch(void);
extern void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

/*** Throughout getint, *pn is used as an ordinary int variable. getch and
 * ungetch were also used so the one extra character that must be read can be
 * pushed back onto the input.
 */

int main(void) {
  // int number, result;
  //
  // printf("Enter an integer: ");
  // result = getint(&number);
  //
  // if (result)
  //   printf("You entered: %d\n", result);
  // else
  //   printf("Not a valid integer\n");
  int n, array[10];

  for (n = 0; n < 10 && getint(&array[n]) != EOF; n++)
    ;

  printf("Here's your array: ");
  for (n = 0; n < 10; n++)
    printf("%d ", array[n]);
  printf("\n");

  return 0;
}

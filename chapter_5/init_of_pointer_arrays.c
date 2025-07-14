/***
 * 5.8 Initialization of Pointer Arrays
 *
 * Consider the problem of writing a function month_name(n), which returns a
 * pointer to a character string containing the name of the n-th month. This is
 * an ideal application for an internal static array. month_name contains a
 * private array of character strings, and returns a pointer to the proper one
 * when called. This section shows how that array of names is initialized.
 *
 * The syntax is similar to previous initializations:
 */

/* month_name: return name of n-th month */
char *month_name(int n) {
  static char *name[] = {"Illegal month", "January",   "February", "March",
                         "April",         "May",       "June",     "July",
                         "August",        "September", "October",  "November",
                         "December"};

  return (n < 1 || n > 12) ? name[0] : name[n];
}

/***
 * The declaration of name, which is an array of character pointers, is the same
 * as lineptr in the sorting example (char *lineptr[MAXLINES];); each is
 * assigned to the corresponding position in the array. The character of the
 * i-th string are placed somewhere, and a pointer to them is stored in name[i].
 * Since the size of the array name is not specified, the compiler counts the
 * initalizers and fills in the correct number.
 */
#include <stdio.h>
#define NO_OF_MONTHS 12

int main(void) {
  for (int i = 1; i <= NO_OF_MONTHS; i++)
    printf("%d. month: %s\n", i, month_name(i));

  return 0;
}

/***
 * 5.7 Multi-dimensional Arrays
 *
 * C provides rectangular multi-dimensional arrays, although in practice they
 * are much less used than arrays of pointers.
 *
 * Consider the problem of date conversion, from day of the month to day of the
 * year and vice versa. For example, March 1 is the 60th day of a non-leap
 * year, and the 61st day of a leap year. Let us define two functions to do the
 * conversions: day_of_year converts the month and day into the day of the
 * year, and month_day converts the day of the year into the month and day.
 * Since this latter function computes two values, the month and day arguments
 * will be pointers:
 *
 *  month_day(1988, 60, &m, &d)
 * sets m to 2 and d to 29 (February 29th).
 *
 * These functions both need the same information, a table of the number of
 * days in each month ("thirdy days hath September ..."). Since the number of
 * days per month differs for leap years and non-leap years, it's easier to
 * seperate them into two rows of a two-dimensional array than to keep track of
 * what happens to Februray during computation. The array and the functions for
 * performing the transformations are as follows:
 */
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
  int i, leap;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;

  leap = leap % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}

/***
 * Recall that the arithmetic value of a logical expression, such as the one for
 * leap, is either zero (false) or one (true), so it can be used as a subscript
 * of the array daytab.
 *
 * The array daytab has to be external to both day_of_year and month_day, so
 * they can both use it. We made it char to illustrate a legitimate use of char
 * for storing small non-character integers.
 *
 * daytab is the first two-dimensional array we have dealt with. In C, a
 * two-dimensional array is really a one-dimensional array, each of whose
 * elements is an array. Hence subscripts are written as
 *
 *  daytab[i][j] -> [row][col]
 * rather than
 *
 *  daytab[i, j] -> WRONG
 * Other than this notational distinction, a two-dimensional array can be
 * treated in much the same way as in other languages. Elements are stored by
 * rows, so the rightmost subscript, or column, varies as elements are accessed
 * in storage order.
 *
 * An array is initialized by a list of initializers in braces; each row of a
 * two-dimensional array is initialized by a corresponding sub-list. We started
 * the array daytab with a column of zero so that month numbers can run from
 * the natural 1 to 12 instead of 0 to 11. Since space is not at a premium
 * here, this is clearer than adjusting the indices.
 *
 * If a two-dimensional array is to be passed to a function, the parameter
 * declaration in the function must include the number of columns; the number
 * of rows is irrelevant, since what is passed is, as before, a pointer to an
 * array of rows, where each row is an array of 13 ints. In this particular
 * case, it is a pointer to objects that are arrays of 13 ints. Thus if the
 * array daytab is to be passed to a function f, the declaration of f would be:
 *
 *  f(int daytab([2][13])) { ... }
 * It could also be
 *
 *  f(int daytab[][13]) { ... }
 * since the number of rows is irrelevant, or it could be
 *
 *  f(int (*daytab)[13]) { ... }
 * which says that the parameter is a pointer to an array of 13 characters. The
 * parantheses are necessary since brackets [] have higher precedence than *.
 * Without parantheses, the declaration
 *
 *  int *daytab[13]
 * is an array of 13 pointers to integers. More generally, only the first
 * dimension (subscript) of an array is free; all the others have to specified.
 */

int main(void) {
  // x, y, z are unprintable control characters
  // using char to store them makes a lot of sense
  // remember chars are just small integers that are the numeric values of the
  // character in the machine's character set
  char x = 30;
  char y = 31;
  char z = 29;

  // Memory address of daytab[i][j] is calculated as:
  //
  // daytab[i][j] = daytab + (i * number_of_columns + j) * sizeof(char)

  printf("x: %c\n", x);
  printf("y: %c\n", y);
  printf("z: %c\n", z);

  return 0;
}

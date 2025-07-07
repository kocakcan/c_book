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

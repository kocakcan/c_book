/* There is no error checking in day_of_year and month_day. Remedy this effect.
 * */
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
  if (month < 1 || month > 12)
    return -1;
  int i, leap;
  leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  if (day < 1 || day > daytab[leap][month]) 
    return -1;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  if (pmonth == NULL || pday == NULL)
	return;
  int i, leap;
  leap = leap % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  if (yearday < 1 || yearday > (leap ? 366 : 365)) {
	*pmonth = 0, *pday = 0;
	return;
  }
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}

int main(int argc, char *argv[]) {
  int x = day_of_year(2025, 2, 28);
  int pmonth, pday;

  month_day(2025, x, &pmonth, &pday);
  printf("today is the %dth day of the year\n", x);
  printf("pmonth: %d | pday: %d\n", pmonth, pday);

  return 0;
}

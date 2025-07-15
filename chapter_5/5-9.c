/* Rewrite the routines day_of_year and month_day with pointers instead of
 * indexing. */
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
  if (day < 1 || day > *(*(daytab + leap) + month))
    return -1;
  for (i = 1; i < month; i++)
    day += *(*(daytab + leap) + i);
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  if (pmonth == NULL || pday == NULL)
    return;
  int i, leap;
  leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  if (yearday < 1 || yearday > (leap ? 366 : 365)) {
    *pmonth = 0, *pday = 0;
    return;
  }
  for (i = 1; yearday > *(*(daytab + leap) + i); i++)
    yearday -= *(*(daytab + leap) + i);
  *pmonth = i;
  *pday = yearday;
}

int main(void) {
  int today, month;
  int yearday = day_of_year(2025, 7, 15);

  printf("today is the %dth day of the year\n", yearday);
  month_day(2025, yearday, &month, &today);
  printf("today is %dth day of %d. month\n", today, month);

  return 0;
}

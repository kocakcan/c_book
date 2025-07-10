/* There is no error checking in day_of_year and month_day. Remedy this effect.
 * */
#include <stdio.h>
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
  if (month >= 1 && month <= 12)
    printf("month looks okay\n");
  int i, leap;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  if (day > daytab[leap][month])
    day = daytab[leap][month];
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

int main(int argc, char *argv[]) {
  // This should not work as February is never 30 days long
  int x = day_of_year(2025, 2, 300);
  printf("today is the %dth day of the year\n", x);

  return 0;
}

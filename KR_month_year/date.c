#include "date.h"

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day){
  int leap;

  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

  for (char *p = *(daytab+leap),i = 0; i < month; i++)
    day += *p++;
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday){
  int leap, i = 1;

  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  for (char *p = *(daytab+leap); yearday > *p; i++)
    yearday -= *p++;
  *pmonth = i;
  *pday = yearday;
}



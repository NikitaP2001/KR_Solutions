#include "date.h"
#include <stdio.h>

int main(){
  int day, month, year;

  scanf("%d/%d/%d",&day, &month, &year);
  printf("Day of year is %d\n",day_of_year(year,month,day));
}

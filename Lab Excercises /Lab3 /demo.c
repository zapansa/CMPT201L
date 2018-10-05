#include <stdio.h>

#define DATE2_EARLIER (1)
#define DATE1_EARLIER (-1)
#define DATES_EQUAL 0

const char * get_month(int);

int main(void)
  {
  int day1, month1, year1;
  int day2, month2, year2;
  int result = DATES_EQUAL;

  printf("Enter the first date (mm/dd/yy): ");
  scanf("%d/%d/%d", &month1, &day1, &year1);

  printf("Enter the second date (mm/dd/yy): ");
  scanf("%d/%d/%d", &month2, &day2, &year2);

  if ( year1 < year2 )
  	result = DATE1_EARLIER;
  else if ( year2 < year1 )
    result = DATE2_EARLIER;
  else
    {
  	if ( month1 < month2 )
    	result = DATE1_EARLIER;
    else if ( month2 < month1 )
    	result = DATE2_EARLIER;
  	else
      {
    	if ( day1 < day2 )
    		result = DATE1_EARLIER;
    	else if ( day2 < day1 )
    		result = DATE2_EARLIER;
      }
    }

    switch (result)
      {
    	case DATE2_EARLIER:
      printf("%s %d, %d is earlier than ", get_month(month2), day2, year2);
      printf("%s %d, %d.\n", get_month(month1), day1, year1);
    		break;
    	case DATE1_EARLIER:
      printf("%s %d, %d is earlier than ", get_month(month1), day1, year1);
      printf("%s %d, %d.\n", get_month(month2), day2, year2);
    		break;
    	case DATES_EQUAL:
    		printf("The dates are equal.\n");
    		break;
      }

      if ( year1 == year2 )
        printf("The dates are from the same year.\n");
      else
        printf("The dates are not from the same year.\n");

    return 0;
}

const char* get_month(int month)
  {
  switch (month)
    {
    case 1:
      return "January";
    case 2:
      return "February";
    case 3:
      return "March";
    case 4:
      return "April";
    case 5:
      return "May";
    case 6:
      return "June";
    case 7:
      return "July";
    case 8:
      return "August";
    case 9:
      return "September";
    case 10:
      return "October";
    case 11:
      return "November";
    case 12:
      return "December";
    }
    return 0;
  }

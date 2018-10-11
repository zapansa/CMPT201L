/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #1, Exercise (#2)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

int format_days(int year);
int nth_occurence(int n, int dayOfWeek, int month, int year);

int main(void)
{
  /* Declare Variables */
  int inYear;

  /* Scan for input */
  scanf("%d", &inYear);

  /* Call function to format family day dates */
  format_days(inYear);

  return 0;
}

/* This function formats the family-day table */
int format_days(int year)
{
  /* Declare Variables */
  int z, y, j;
  int colYear = 0;
  int rowYear = year%10;
  int endYear = year+30;
  int startYear = year/10;
  int spaceYear = 0;

  /* Print the first row - row of year endings */
  for(j=0; j<=9; j++)
    {
      if(j==0)
        printf("   ");
      printf("%6d", j);
    }
  printf("\n");

  /* Prints the table of family day dates.
     Also prints the column of the first 3 digits of years */
  for(y=year; y<endYear; y++)
    {
      /* If the spacing is at 0, print the 3 digit year */
      if (spaceYear==0)
          printf("%d", startYear++);
      
      /* at the start of the family dates print some space for formatting */
      if(y==year)
        for(spaceYear=0; spaceYear<rowYear; spaceYear++)
          printf("      ");

      /* Printing the family day dates retured from nth_occurence function */
      printf("%6d", nth_occurence(3, 1, 2, y));

      /* If the spacing is >9, make a new line to print rest of dates */
      if(++spaceYear> 9)
        {
          printf("\n");
          spaceYear = 0; 
        }
    }
  printf("\n");

  return 0;
}

/* This function calculates the date of the nth dayOfWeek - Zeller's Algorithm
   Source(The function): https://bit.ly/2QGZPIM 
   Source(Zeller's Algorithm): https://bit.ly/2ORtxxi*/
int nth_occurence(int n, int dayOfWeek, int month, int year)
{
  /* Adjust month and year */
  if (month < 3)
      -- year, month += 12;
  
  /* Gregorian calendar is a 400 year cycle */
  year = year % 400;

  /* There are no leap years in y.100, 200, 300 */
  int century = year / 100;
  int leaps = year / 4 - century;

  /* A normal year is 52 weeks and 1 day, so the calendar advances one day.
     In a leap year, it advances two days. */
  int advances = year + leaps;
  int month_offset = (13 * (month + 1)) / 5;

  /* Computes day of first week of the month */
  int first = (month_offset + advances) % 7;

  /* If the dayOfWeek we're looking for is at least the day we just
     computed, we just add the difference. Otherwise, we need to add 7.
     Then we just add the desired number of weeks */
  int offset = dayOfWeek - first;
  if (offset < 0)
    offset += 7;
  return 1 + offset + (n - 1) * 7;
}

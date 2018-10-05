/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #3, Part (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include "change.h"

int main(void)
{
  /* Decalre variables */
  double owed, paid;
  double change;
  
  /* Get input */
  printf("Enter amount owed: ");
  scanf("%lf", &owed);

  printf("Enter amount paid: ");
  scanf("%lf", &paid);

  /* Converts change to pennies */
  change = -(owed - paid); 
  
  /* Case - if there is no change needed */
  if ( change <= 0 )
    {
      printf("No change is needed or amount still owing.\n");
      return 0;
    }

  /* Case - There is change so print result */
  printf("Change of: \n");

  /* call function to calculate change in dollars */
  dollar_change(change);

  return 0;
}

int dollar_change(double change)
{
  /* Declare variables */
  int dChange = (int)change;
  int fifties, twenties, tens, fives, loonies, toonies;
  double cChange = change - dChange;

  /* Calculates how many of each dollar needed */
  fifties = dChange/50;
  dChange %= 50;
  twenties = dChange/20;
  dChange %= 20;
  tens = dChange/10;
  dChange %= 10;
  fives = dChange/5;
  dChange %= 5;
  toonies = dChange/2;
  dChange %= 2;
  loonies = dChange/1;
  dChange %= 1;

  /* Print the results -- only print if theres change for specific bill */
  if ( fifties != 0 )
    printf("%d fifty dollar bill\n", fifties);
  if ( twenties != 0 )
    printf("%d twenty dollar bill\n", twenties);
  if ( tens != 0 )
    printf("%d ten dollar bill\n", tens);
  if ( fives != 0 ) 
    printf("%d five dollar bill\n", fives);
  if ( toonies != 0 )
    printf("%d two dollar coin\n", toonies);
  if ( loonies != 0 )
    printf("%d one dollar bill\n", loonies);

  /* Call cents_change func. to calculate change in cents */
  cent_change(cChange);

  return 0;
}

int cent_change(double change)
{
  /* Declare Variables */
  int cChange = round(change*100);
  int quarters, dimes, nickels, pennies;

  /* Calculate how many of each cent is needed */
  quarters = cChange/25;
  cChange %= 25;
  dimes = cChange/10;
  cChange %= 10;
  nickels = cChange/5;
  cChange %= 5;
  pennies = cChange/1;
  cChange %= 1;

  /* Print - Only print if theres a value to the cent */
  if ( quarters != 0 )
    printf("%d quarters\n", quarters);
  if ( dimes != 0 )
    printf("%d dime\n", dimes);
  if ( nickels != 0 )
    printf("%d nickel\n", nickels);
  if ( pennies != 0 )
    printf("%d penny\n", pennies);

  return 0;
}

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #1, Part (#5)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#define NOT_PRIME (1)
#define IS_PRIME (-1)

/* Declare functions */
int find_pairs(int n, int d);

int main(void) 
{
  /* Declare variables */
  int n, d;

  /* Read input */
  scanf("%d %d", &n, &d);

  /* Call function to find primes */
  find_pairs(n, d);
  
  return 0; 
}

int find_pairs(int n, int d)
{
  /* Declare Variables */
  int i, j, num;
  int add = 0; 
  int numArray[1024];

  /* Nested loop to find prime numbers. 
     Source: https://bit.ly/2RtOrB4 */
  for( i=2; i<n; i++ )
    {
      num = IS_PRIME; 
      for( j=2; j<i-1; j++)
	{
	  /* Prime number condition */
	  if( i%j == 0 )
	    num = NOT_PRIME; 
	}
      /* Case if the number is a prime */
      if( num == IS_PRIME )
	{
	  /* Add the prime number to the numArray */
	  numArray[add] = i;
	  add++;
	}
    }
  /* Iterate through numArray from index 0 */
  for ( i=0; i<add; i++)
    {
      /* Iterate through numArray from index i */
      for( j=i; j<add; j++)
	{
	  /* If the two numbers have the difference d */
	  if (numArray[i] == numArray[j] - d)
	    printf("(%d %d)\n", numArray[i], numArray[j]);
	}
    }
  return 0;
}

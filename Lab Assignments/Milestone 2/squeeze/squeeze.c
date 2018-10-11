/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #1, Exercise (#4)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>

#define MAX_LENGTH (9)
#define ARRAY_SIZE (26)

int main(void)
{
  /* Declare variables */
  char inString[1024];
  int letters[ARRAY_SIZE] = {0}; /* Initialized all ints in array to 0 */
  int c = 0;
  int counter; 

  /* Get input in stdin using gets() */
  gets(inString);
  
  /* Iterate through string. */
  while(inString[c] != '\0')
    {
      /* Assign letters from  lowercase a to z */
      if(inString[c] >= 'a' && inString[c] <= 'z')
	{
	  /* Increase occurence of letter */
	  letters[inString[c]-'a']++;
	}
      c++; 
    }

  /* Iterate through array */
  for( c=0; c<ARRAY_SIZE; c++ )
    {
      /* Case if the letter appears more than MAX_LENGTH (9) */
      if( letters[c] > MAX_LENGTH )
	{
	  counter = letters[c];
	  /* While the counter is >= MAX_LENGTH, print something and 
	     then decrease by MAX_LENGTH */
	  while( counter >= MAX_LENGTH)
	    {
	      printf("%c%d", c+'a', MAX_LENGTH);
	      counter -= MAX_LENGTH; 
	    } 
	  /* If the counter is less than MAX_LENGTH but still not 0. */
	  if(counter != 0)
	    {
	      printf("%c%d", c+'a', counter);
	    }
	  counter = 0; 
	}
      /* Case to not print the letter if it occurs 0 or 1 times - in the
         format. So you wont get eg. a0b0c0d1e1f0..... */ 
      else if( letters[c] != 0 && letters[c] != 1 )
        {
          printf("%c%d", c+'a', letters[c]);
        }
      /* Case if the occurence is just 1 times - print in this format */
      else if( letters[c] == 1 )
        {
          printf("%c", c+'a');
        }
    }
  printf("\n");

  return 0; 
}

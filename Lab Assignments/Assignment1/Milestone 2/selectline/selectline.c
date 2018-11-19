/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #1, Exercise (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IS_IN_FIFTEEN (1)

int main(void) 
  {
  /* Variables */
  char *echoInput = malloc(1);
  char *toSearch, *toEcho, *isPresent;
  int echoLen = strlen(toSearch);
  int inFifteen, c, k, i = 0; 

  /* Read string from unknown length */
  /* Read until EOF or \n */
  while((c = getchar()) != '\n' && c != EOF)
    {
      echoInput[i++] = c;
      echoInput = realloc(echoInput, i+1);
    }
  
  /* Null terminate the string */
  echoInput[i] = '\0';
 
  /* Split string from file */
  toSearch = strtok(echoInput," ");
  toEcho = strtok(NULL, " ");  

  /* Check if the first letter is in the other string */
  isPresent = strchr(toEcho, *toSearch);
  
  /* Print if isPresent is not NULL | the letter is in the string */
  if (isPresent != NULL)
    { 
      /* If isPresent, check 15 chars in toEcho to check toSearch within it */
      for(k = 0; k <= 15; k++)
	{
	  /* If condition is true atleast once */
	  if(toEcho[k] == *toSearch)
	    inFifteen = IS_IN_FIFTEEN;
	}
    }

  /* If equal, print toEcho */
  if(inFifteen == IS_IN_FIFTEEN)
    printf("%s\n", toEcho);

  free(echoInput);

  return 0;
  }

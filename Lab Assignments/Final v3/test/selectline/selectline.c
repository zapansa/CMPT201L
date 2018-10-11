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
#define NOT_IN_FIFTEEN (-1)

/* Declare functions */
int selectline(char *echoInput);

int main(void)
  {
    /* Declare Varibles */
    int maxLen = 1, currSize = 0;
    int i, j;
    char *echoInput = malloc(maxLen);
    char tch;

    /* Get input from file until it is the end of the file */
    tch = getc(stdin);

    while (tch == '\n')
      getc(stdin);

    while(tch != EOF)
      {
        ungetc(tch, stdin);
	
	/* malloc and realloc to get string of any length 
	   Source: https://bit.ly/2IRPl6C */
        currSize = maxLen;
        if (echoInput != NULL)
          {
            i = EOF;
            j = 0;
            while (( i = getchar()) != '\n' && i != EOF)
              {
                echoInput[j++]=(char)i;
                if (j == currSize)
                  {
      	             currSize = j + maxLen;
      	              echoInput = realloc(echoInput, currSize);
      	          }
              }

	    /* null terminator for the string */
	    echoInput[j] = '\0';
          }

	/* call selectline function to echo */
        selectline(echoInput);
        tch = getchar();
      }
    return 0;
  }


int selectline(char *echoInput)
  {
    /* Variables */
    char *toSearch, *toEcho, *isPresent;
    int inFifteen = NOT_IN_FIFTEEN, k;


    /* Split string from file */
    toSearch = strtok(echoInput," ");
    toEcho = strtok(NULL, " ");

    /* Check if the first letter is in the other string */
    isPresent = strchr(toEcho, *toSearch);

    /* Print if isPresent is not NULL | the letter is in the string */
    if (isPresent != NULL)
      {
        /* If isPresent, check 15 chars in toEcho to check toSearch within it */
        for(k = 0; k < 15; k++)
          {
  	         /* If condition is true atleast once */
  	          if(toEcho[k] == *toSearch)
  	           inFifteen = IS_IN_FIFTEEN;
  	  }
      }

    /* If equal, print toEcho */
    if(inFifteen == IS_IN_FIFTEEN)
      printf("%s\n", toEcho);

    return 0;
  }

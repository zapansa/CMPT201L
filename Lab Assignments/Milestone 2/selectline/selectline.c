#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) 
  {
  /* Variables */
  int echoMax = 128;
  int echoSize = 0;

  char *echoInput = malloc(echoMax);
  char *toSearch, *toEcho, *isPresent;

  /* Read string of unassumed length from input */
  echoSize = echoMax;

  if(echoInput != NULL)
    {
    int j = EOF;
    int i = 0;

    // getchar() gets a character from stdin.
    while (( j = getchar() ) != '\n' && j != EOF)
      {

      // adding each char into echoInput
      echoInput[i++]=(char)j;
      if (i == echoSize)
        { 
	echoSize = i + echoMax;
	echoInput = realloc(echoInput, echoMax);
        }
      }

    // null terminator for echoInput
    echoInput[i] = '\0';
    }

  /* Split string from file */
  toSearch = strtok(echoInput," ");
  toEcho = strtok(NULL, " ");  

  /* Check if the first letter is in the other string */
  isPresent = strchr(toEcho, *toSearch);
  
  /* Print if isPresent is not NULL | the letter is in the string */
  if (isPresent != NULL) 
    {
    printf("%s\n", toEcho);
    }

  return 0;
  }
/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #4, Part (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <stdio.h>
#define STR_MAX_LEN (25)

/* This function gets input from the user (inpStr, inChr), and
   removes all occurences of inChr in inpStr as well as
   returning the amount of times inChr occurs in inpStr
   Precondition: a str array, array len, and char need to be passed in
   Post condition: occurence (count) of inChr is returned
*/
int remove_char(char inpStr[], int inpLen, char inChr);

int main(void)
{
  /* Declare Variables */
  int i = 0, c = 0, ch, occur;
  char inpStr[STR_MAX_LEN + 1];
  char inChr;

  /* Get user input */
  printf("Enter a string (max length 25): ");

  while(((ch = getchar()) != '\n' && ch != EOF) && c < STR_MAX_LEN)
    {
      inpStr[i++] = ch;
      c++;
    }
  inpStr[i] = '\0';

  printf("Enter a character: ");
  inChr = getchar();

  /* Initalize occur with returned value from function remove_char */
  occur = remove_char(inpStr, c, inChr);

  /* Print the occurence of the character in the string */
  printf("The character %c occured %d times.\n", inChr, occur);

  return 0;
}

 /* Function that removes all occurences of inChr in inpStr */
int remove_char(char inpStr[], int inpLen, char inChr)
{
  /* Declared variables */
  char *loc = inpStr;
  int i, count = 0;

  for(i = 0; i != inpLen; i++)
    {
      /* If the char is not in inpStr move pointer to next elem
        & dereference last value */
      if(inpStr[i] != inChr)
	       *loc++ = inpStr[i];

      /* Counts how many times the character occurs */
      if(inpStr[i] == inChr)
	       count++;
    }
    *loc = 0;
  /* Print the new string without dereferenced chars */
  printf("The string: %s\n", inpStr);

  /* Return the occurence of inChr in inpStr */
  return count;
}

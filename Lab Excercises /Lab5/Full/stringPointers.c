/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #5, Part (#2)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN (100)

/* This function is your own version of the string library function strstr
   You can’t use the strstr or anything from string.h other than strlen
   Preconditions: Two C-strings passed in
   Postconditions: Returns a pointer to the first location where the string
   Search occurs in Find, or NULL if there is no substring found.
*/
char *mySubStr(char *find, char *search);

/* This function will reverse revsize characters in the C-string start.
   The characters will be reversed starting at the character start points to.
   Preconditions: a C-string passed in
   Postconsitions: The original parameter in not altered. Returns a pointer
   to the altered string, or NULL if no reverse possible.
*/
char *reverse(const char *start, int revSize);

/* This function gets the reversed string and swaps it with its original
   word in the search array.
   Preconditions: Three valid chars are passed in.
   Postconditions: The new string with the swapped word is returned.
*/
char *getString(char *location, char *search, char *find);

/* This function gets the input of the user
   Preconditions: a C-string and an int is passed in
   Postconditions: The strings passed through this have to be null terminated
*/
void getInput(char *str, int size);

char *mySubStr(char *find, char *search)
{
  /* Declare Variables */
  int i=0, j=0, ind = 0;
  char *fLocation = NULL;

  /* Searching the string until one the strings ends */
  while((*(search+j) != '\0') && (*(find+i) != '\0'))
    {
      /* If the values dont equal only increment j */
      if(*(search+j) != *(find+i))
        {
          j++;
          i=0;
        }
      /* Otherwise increment both of them */
      else
        {
          i++;
          j++;
        }
      /* Keep track of  the last place find shows up in search */
      ind++;
    }
    /* Find the first place find showd up in search */
    ind = ind-strlen(find);
    /* Make fLocation its location */
    fLocation = (search+ind);

    /* If one of the strings finished - the substring exists and */
    if (*(find+i)=='\0')
        return fLocation;
    else /* Otherwise */
      return NULL;
}

char *reverse(const char *start, int revSize)
{
  /* Make room for the new reversed string */
  char *revMal = malloc(revSize + 1);
  char *revString = revMal + revSize - 1;

  /* the last index of revstring is the first in start an so on */
  while(*start)
    *--revString = *start++;

  /* If start is not NULL */
  if(start != NULL)
    return revString;
  else /* Otherwise */
    return NULL;
}

char *getString(char *revString, char *search, char *find)
{
  /* Declare variables */
  int i=0, j=0, k=0, ind = 0;
  char *temp = search;

  /* While neither strings ends */
  while((*(search+j) != '\0') && (*(find+i) != '\0'))
    {
      /* If the strings dont equal only increment j and keep i at 0 */
      if(*(search+j) != *(find+i))
        {
          j++;
          i=0;
        }
      /* Otherwise increment both */
      else
        {
          i++;
          j++;
        }
      /* Keep track of  the last place find shows up in search */
      ind++;
    }
    /* finds first occurence of find in search */
    ind = ind-strlen(find);
    /* Swap the reversed word for the unreversed word in search */
    while(k < strlen(find))
      {
        *(temp+ind+k) = *(search+ind+k);
        *(search+ind+k) = *(revString+k);
        *(revString+k) = *(temp+ind+k);
        k++;
      }
    /* Return the string with reversed word */
    return temp;
}

void getInput(char *str, int size)
{
  /* Declare variables */
  char c;
  char *s = str;
  int count = 0;

  /* Read input until max size */
  while(((c = getchar()) !='\n') && (count<size))
  {
    *s=c;
     s++;
     count++;
  }
  /* Null terminate the string */
  *s='\0';
}

int main(void)
{
  /* 100 char arrays at start of program */
   char strSearch[MAXLEN];
   char strFind[MAXLEN];

   /* Declare Variables */
   char *locResult = NULL;
   char *revResult = NULL;
   char *getResult = NULL;

   /* Prompt for input */
   printf("Please enter two strings : ");
   getInput(strSearch, MAXLEN);
   getInput(strFind, MAXLEN);

   /* Check if substring exists */
   locResult = mySubStr(strFind, strSearch);

   /* If it isn't null then it exists */
   if(locResult != NULL)
    {
      printf("Substring was found! Reversing.... \n");
      revResult = reverse(strFind, strlen(strSearch));
    }
   else /* Otherwise */
     printf("No substring was found!\n");

   /* If not null print */
   if(revResult != NULL)
     {
       getResult = getString(revResult, strSearch, strFind);
       printf("The string is now %s\n", getResult);
     }

   return 0;
}

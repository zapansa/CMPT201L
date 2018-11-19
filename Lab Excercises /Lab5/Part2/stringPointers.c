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

/*This function is your own version of the string library function strstr
You can’t use the strstr or anything from string.h other than strlen
Gets two C-strings passed in: Search a string to look for
and Find a string into which Search is to be found
Returns a pointer to the first location
where the string Search occurs in Find,
or NULL if there is no substring found.*/
char *mySubStr(char *find, char *search);

/*This function will reverse revsize characters in the C-string start.
The characters will be reversed starting at the character start points to.
Gets a C-string passed in: start
The original parameter in not altered
and an integer revSize which specifies how many characters to be reversed
Returns a pointer to the altered string, or NULL if no reverse possible.*/
char *reverse(const char *start, int revSize);

char *getString(char *location, char *search, char *find);

void getInput(char *str, int size);

char *mySubStr(char *find, char *search)
{
  int i=0, j=0, ind = 0;
  char *fLocation = NULL;

  while((*(search+j) != '\0') && (*(find+i) != '\0'))
    {
      if(*(search+j) != *(find+i))
        {
          j++;
          i=0;
        }
      else
        {
          i++;
          j++;
        }
      ind++;
    }

    ind = ind-strlen(find);
    fLocation = (search+ind);

    if (*(find+i)=='\0')
        return fLocation;
    else
      return NULL;
}

char *reverse(const char *start, int revSize)
{
  char *revMal = malloc(revSize + 1);
  char *revString = revMal + revSize - 1;
  while(*start)
    *--revString = *start++;

  if(start == NULL)
    return NULL;
  else
   return revString;
}

char *getString(char *revString, char *search, char *find)
{
  int i=0, j=0, k=0, ind = 0;
  char *temp = search;

  while((*(search+j) != '\0') && (*(find+i) != '\0'))
    {
      if(*(search+j) != *(find+i))
        {
          j++;
          i=0;
        }
      else
        {
          i++;
          j++;
        }
      ind++;
    }

    ind = ind-strlen(find);

    while(k < strlen(find))
      {
        *(temp+ind+k) = *(search+ind+k);
        *(search+ind+k) = *(revString+k);
        *(revString+k) = *(temp+ind+k);
        k++;
      }

    return temp;
}

void getInput(char *str, int size)
{
  char c;
  char *s = str;
  int count = 0;
  while(((c = getchar()) !='\n' && c != '\0') && (count<size))
  {
    *s=c;
     s++;
     count++;
  }
  *s='\0';
}

int main(void)
{
  /* 100 char arrays at start of program */
   char strSearch[MAXLEN];
   char strFind[MAXLEN];

   char *locResult = NULL;
   char *revResult = NULL;
   char *getResult = NULL;

   printf("Please enter two strings : ");
   getInput(strSearch, MAXLEN);
   getInput(strFind, MAXLEN);

   locResult = mySubStr(strFind, strSearch);

   if(locResult != NULL)
    {
      printf("Substring was found! Reversing.... \n");
      revResult = reverse(strFind, strlen(strSearch));
    }
  else
    printf("No substring was found!\n");

  if(revResult != NULL)
    {
      getResult = getString(revResult, strSearch, strFind);
      printf("The string is now %s\n", getResult);
    }

   return 0;
}

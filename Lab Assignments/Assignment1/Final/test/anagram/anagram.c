/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #1, Exercise (#3)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Declaring functions */
int check_anagrams(char word1[], char word2[]);
int anagrams(char *anagramStr);

int main(void)
{
  /* Declare Varibles */
  int maxLen = 1, currSize = 0;
  int i, j;
  char *anagramStr = malloc(maxLen);
  char tch;

  /* Get input from file until it is the end of the file */
  tch = getchar();

  while (tch == '\n')
    getchar();

  while(tch != EOF)
    {
      ungetc(tch, stdin);

      /* Read from string of unknown length
         Source: https://bit.ly/2IRPl6C */
      currSize = maxLen;
      if (anagramStr != NULL)
        {
          i = EOF;
          j = 0;
          while (( i = getchar()) != '\n' && i != EOF)
            {
              anagramStr[j++]=(char)i;
              if (j == currSize)
                {
    	             currSize = j + maxLen;
    	              anagramStr = realloc(anagramStr, currSize);
    	        }
            }
        /* null terminator for the string */
        anagramStr[j] = '\0';
        }

      /* Call function to use string to check if anagrams or not */
      anagrams(anagramStr);

      tch = getchar();
    }
  return 0;
}

/* Function to split the string from the space and print True or False */
int anagrams(char *anagramStr)
{
  char *anagramWord1, *anagramWord2;

   /* Split the string in the space. */
  anagramWord1 = strtok(anagramStr, " ");
  anagramWord2 = strtok(NULL, " ");

  /* Two cases of what to print in diff. situations */
  if ((check_anagrams(anagramWord1, anagramWord2)) != 0)
    printf("%s %s True\n", anagramWord1, anagramWord2);
  else
    printf("%s %s False\n", anagramWord1, anagramWord2);

  return 0;
}

/* Function to count occurences in each string. */
int check_anagrams(char word1[], char word2[])
{
  int count1[26] = {0};
  int count2[26] = {0};
  int c = 0;

  /* Anagrams have the same length - check for length. */
  if (strlen(word1) != strlen(word2))
    return 0;

  /* Check for occurences of letters in each string. */
  while (word1[c] != '\0')
    {
    count1[word1[c]-'a']++;
    c++;
    }
  c = 0;
  while (word2[c] != '\0')
    {
    count2[word2[c]-'a']++;
    c++;
    }

  /* Compare letter frequences. */
  for (c = 0; c < 26; c++)
    {
    if (count1[c] != count2[c])
      return 0;
    }

  return 1;
}

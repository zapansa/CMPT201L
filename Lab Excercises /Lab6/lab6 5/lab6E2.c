/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #6, Part 2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stuff.h"
#define ARRSIZE (4)

int main(void)
{
  /* Declarations */
  int i;
  char * sArray[ARRSIZE] = {"abc", "efgh", "jklm", "12345"};
  struct stuff * mArray = makeArray(ARRSIZE);

  /* Use sArray values for makeStuff() */
  for(i=0; i<ARRSIZE; i++)
    {
      struct stuff *fill = makeStuff(sArray[i]);
      mArray[i] = *fill; /* Copy contents? */
      free(fill); /* Free allocated memory */
    }

  /* Call - Prints each in struct array */
  for(i=0; i<ARRSIZE; i++)
    printStuff(mArray+i);

  /* Call - Frees dynamically allocated struct array + contents */
  freeStuff(ARRSIZE, mArray);

  return 0;
}

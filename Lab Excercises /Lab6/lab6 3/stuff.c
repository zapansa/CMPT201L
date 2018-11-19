/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #6, Part 1
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stuff.h"

struct stuff * makeArray(int size)
{
  /* create dynamic array of struct*/
  struct stuff * mArray = malloc((size)*sizeof(struct stuff));
  /* error checking */
  if(mArray == NULL)
    {
      printf("Error in Allocating.");
      return 0;
    }
  else /* Otherwise */
    return mArray;
}

struct stuff * makeStuff(char * data)
{
  /* create new struct stuff */
  struct stuff * mStuff = malloc(sizeof(struct stuff));
  /* Error checking */
  if(mStuff == NULL)
    {
      printf("Error in Allocating.");
      return 0;
    }
  else /* Otherwise */
    {
      /* Set data to members */
      mStuff->insides = data;
      mStuff->size = strlen(data);
      return mStuff;
    }
}

void printStuff(struct stuff * printy)
{
  /* Print struct members */
  printf("%s %d\n", printy->insides, printy->size);
}

void freeStuff(int size, struct stuff * myArray)
{
  /* ???????????????? */
  free(myArray);
}

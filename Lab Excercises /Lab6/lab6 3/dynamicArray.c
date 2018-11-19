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
#include "dynamicArray.h"

float * createArray(int size, float initialValue)
{
  /* Declarations */
  int i;
  float * tArray;
  tArray = malloc(size*sizeof(float)); /* create array */

  /* Error check */
  if(tArray==NULL)
    {
      printf("Error in allocation!");
      return NULL;
    }
  else if(size == 0)
    return NULL;

  /* Otherwise */
  for(i=0; i<size; i++)
    (*(tArray+i)) = initialValue;

  return tArray;
}

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

int main(void)
{
  /* Declarations */
  int size, i;
  float initialValue;

  /* get input */
  printf("Enter array size: ");
  scanf("%d", &size);

  printf("Enter initial Value: ");
  scanf("%f", &initialValue);

  /* make an array */
  float * cA = createArray(size, initialValue);

  /* print contents */
  for(i=0; i<size; i++)
    printf("%f ", (*(cA+i)));
  printf("\n");
  free(cA);

  return 0;
}

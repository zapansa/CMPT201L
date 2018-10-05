/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #3, Part (#2c)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include "change.h"

int main(void)
{
  float fOwed, fPaid;
  char tch;

  tch = getc(stdin);
  while (tch == '\n')
    getc(stdin);
  
  while(tch != EOF)
    {
      ungetc(tch, stdin);
      
      scanf("%f %f", &fOwed, &fPaid);
      
      change(fOwed, fPaid);
      
      tch = getchar();
      while(tch != '\n')
	tch=getc(stdin);
    }
  return 0;
}

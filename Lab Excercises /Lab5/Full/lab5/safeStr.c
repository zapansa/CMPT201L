/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #5, Part (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include "safeStr.h"

void safeReadString(char *str,int size)
{
  /* Declare Variables */
  char c;
  char* s=str;
  int count=0;
  /* Get user input */
  printf("Please type a string of at most %d characters.\n",size);
  /* Get characters until '\n' or '\0' or if count<size */
  c=getchar();
  while((c!='\n') && (count<size))
  {
    *s=c;
     s++;
     count++;
     c=getchar();
  }
  /* Terminate the string */
  *s='\0';
}

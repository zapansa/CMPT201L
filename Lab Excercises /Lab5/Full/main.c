/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #5, Part (#1)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "safeStr.h"

int main(void){
  /* Initialize the first string for input */
  char mainStr[MAXSTR]="Initial string";
  /* Call function to get mainStr input */
  safeReadString(mainStr,MAXSTR);
  /* Initialize remChars - remaining input allowed */
  int remChars=MAXSTR-strlen(mainStr)-1;
  int i;
  /* If MAXSTR amount isnt exhausted yet then*/
  if (remChars>0)
  {
    /* Initialize a second string */
    char insStr[remChars];
    /* Call function to get insStr input */
    safeReadString(insStr,remChars);
    /* Initialize new string - for concatenating */
    char newStr[strlen(mainStr)+strlen(insStr)+1];
    /* For loops to concatenate strings mainStr & insStr */
    for(i=0;i<strlen(mainStr);i++)
      newStr[i]=mainStr[i];
    for(int j=0;j<=strlen(insStr);j++)
      newStr[i+j]=insStr[j];
    /* Print concatenated string and other info */
    printf("The result of concatenating:\n%s\nwith:\%s\nis:\n%s\n",mainStr,insStr,newStr);
  }
  else /* If there MAXSTR was exausted */
    printf("No room for inserting a string\n");

}

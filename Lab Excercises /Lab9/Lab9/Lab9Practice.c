/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #9
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
*------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
  int count;
  char buffer[256];

  if (fgets(buffer, strlen(buffer), stdin) != 0)
   {
       int len = strlen(buffer);
       if (len > 0 && buffer[len-1] == '\n')
           buffer[len-1] = '\0';
       else
       {
          int ch;
          while (((ch = getc(stdin) != '\n') && (ch != EOF)))
            count++;
          buffer[count] = '\0';
       }
   }
   printf("%c!\n", buffer[2]);
}

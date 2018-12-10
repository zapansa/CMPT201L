/*-------------------------------------------------------
# Student's Name: Patricia Zapansa, Alyssa Norton
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

#include "blockChain.h"
#include "peepEditor.h"

/* TO DO
   [x] Clarify what does -p -t does. Ie do if its just supposed to do whatever was on the
       timestamp, or, if you really need to replay what is going on backwards
   [x] what does -v mean, do you just verify that the file that was imported is a peep?
   [ ] Error checking in insert/delete - make sure input is correct
 ! [x] cant delete from an empty peep
   [-] appending some string to peep
   [-] returning from peep - check what happened - deleting
   [ ] check if input is an integer both insert & delete

   ERROR CHECKING
   [ ] Check if position is a char - error message if true - repeat input
*/
void peepInitialize(char *peep)
{
  /* initialize the whole array with a null terminator */
  /* so this wont print out garbage when inserting chars into array */
  int pos;
  for(pos=0; pos < PEEPLEN; pos++)
    peep[pos] = '\0';
}

void peepString(char *peep, char *peepEdit, char *peepType)
{
  /* i dont know why I did this */
  /* with the null term, a regular printf %s would work */
  /* could remove */
  printf("[%s] / %s /\n\n", peepEdit, peepType);
  int pos = 0;
  while(peep[pos] != '\0')
  {
    putchar(peep[pos]);
    pos++;
  }
  printf("\n");
}

void peepShowPositions(char *peep)
{
  int pos = 0;
  printf("\n");
  while(peep[pos] != '\0')
  {
    if(peep[pos] != ' ')
      printf("%d: %c\n", pos, peep[pos]);
    pos++;
  }
}

unsigned int editor(char *peep, struct transaction *modBuffer)
{
  /* Declare variables */
  int choice, transactionsAmt = 0;
  int choiceErr = FALSE;

  while(transactionsAmt!=MXTXNUM)
  {
    /* get the choice of how to edit the peep */
    choice = peepMenu();
    /* which function to go to, to edit the peep */
    switch(choice)
    {
      case 1:
        choiceErr = peepDelete(peep, &modBuffer[transactionsAmt]);
        break;
      case 2:
        choiceErr = peepInsert(peep, &modBuffer[transactionsAmt]);
        break;
      case 3:
        /* Return the amount/number of transactions in the buffer */
        /* Save and exit */
        return transactionsAmt;
        break;
      case 4:
        /* Does not save any of the changes */
        exit(0);
        break;
      default:
        printf("Error! Pick a valid option.\n");
	break;
    }
    /* picked an option increase transation */
    if(choiceErr == TRUE)
      transactionsAmt++;
  }
  /* Return the amount/number of transactions in the buffer */
  return transactionsAmt;
}

void peepMenuBorder()
{
  printf("-----------------------------------------\n");
}

int peepMenu()
{
  /* Declare variables */
  int choice;

  /* Peep menu instructions */
  printf("[PEEP EDITOR MENU]\n");
  printf("\nOptions:\n");
  printf("1. Delete\n");
  printf("2. Insert\n");
  printf("3. Save\n");
  printf("4. Exit\n");
  printf("\n");
  printf("Input: ");
  scanf("%d", &choice);
  /* a function so it's easier to change in the future if i decide to */
  peepMenuBorder();

  /* return choice to editor */
  return choice;
}

int peepDelete(char *peep, struct transaction *modBuffer)
{
  /* variables */
  int position;
  int positionFlag = TRUE;
  /* print the string via loop and putchar */
  peepString(peep, "DELETING", "Current Peep");
  peepShowPositions(peep);

  /* check if peep is empty */
  if(peep[0] == '\0')
  {
    printf("You cannot delete from an empty peep!\n");
    peepMenuBorder();
    return FALSE;
  }

  while(positionFlag == TRUE)
  {
    /* get user input on what to delete */
    printf("\n---\nSpecify position to delete: ");
    scanf("%d", &position);

    /* checking for valid input */
    if(position>256 || position<0)
    {
      printf("---\n");
      printf("Invalid position. Try again.\n");
    }
    /* checking if the position is deletable */
    else if(peep[position] == '\0' || peep[position] == ' ')
    {
      printf("---\n");
      printf("\nThere is nothing to delete in this position!\n");
    }
    else
    {
      /* no error on input */
      /* leave loop */
      positionFlag = FALSE;
    }
  }
  printf("---\n");

  /* next function deletes it from position */
  pDelete(peep, modBuffer, position);

  /* print the string via loop and putchar */
  peepString(peep, "DELETING", "New Peep");
  peepShowPositions(peep);
  peepMenuBorder();

  return TRUE;
}

void pDelete(char *peep, struct transaction *modBuffer, int position)
{
  /* when deleting from a string, the string shifts back */
  if(peep[position+1] == '\0')
  {
    /* if trying to delete at the end of a string just turn that position
       into a null terminator no shift needed */
    peep[position] = '\0';
  }
  else if(position == PEEPLEN)
  {
    /* entering the char at exactly the end of the array */
    peep[position] = '\0';
  }
  else /* deleted anywhere else, the peep would have to shift */
  {
    /* make it empty w/ a space */
    peep[position] = ' ';

    /* iterate through the strings past the deleted position */
    int pos, ahead = position;

    /* in a while start at the position */
    for(pos = position; peep[pos]; pos++)
      /*if it is a space */
      if(peep[pos] != ' ')
        /* the element in front of it will take its place */
        peep[ahead++] = peep[pos];

    /* null terminate the string */
    peep[ahead] = '\0';
  }

  /* change the buffer fields for this edit */
  modBuffer->timestamp = (unsigned long)getTimestamp();
  modBuffer->mod.position = position;
  modBuffer->mod.character = ' '; /* ask what is supposed to go here */
  modBuffer->mod.event_type = 1;

}

int peepInsert(char *peep, struct transaction *modBuffer)
{
  /* variables */
  unsigned char charIn = ' ';
  int position;
  int positionFlag = TRUE;
  int charInFlag = TRUE;
  int checkInt;

  /* print the string via loop and putchar */
  peepString(peep, "INSERTING", "Current Peep");
  peepShowPositions(peep);

  /* get user input on position */
  /*  error checking loop */
  while(positionFlag == TRUE)
  {
    /* repeat input until within bounds*/
    printf("---\n");
    printf("Specify position to insert: ");
    checkInt = scanf("%d", &position);

    /* check if input is within bounds */
    if(checkInt != 1)
    {
      printf("---\n");
      printf("* Please only enter integers between 0 and %d.\n", PEEPLEN);
    }
    else if(position > PEEPLEN || position < 0)
    {
      printf("---\n");
      printf("* Invalid position. Try again.\n");
      printf("* You can ony insert at an index between 0 and %d.\n", PEEPLEN);
    }
    /* check if the position is an allowed position */
    else if(position != 0 && peep[position-1] == '\0' && peep[position] == '\0')
    {
      printf("---\n");
      printf("* Invalid position. Try again.\n");
      printf("* You can ony insert at existing spaces or one after the last.\n");
    }
    else if(position != 0 && peep[position] == '\0' && peep[position+1])
    {
      /* this is valid, trying to input after the last char */
      /* mark as false and leave loop */
      positionFlag = FALSE;
    }
    else
    {
      /* the user input has no error */
      /* mark as false and leave while loop */
      positionFlag = FALSE;
    }
  }

  while(charInFlag == TRUE)
  {
    /* get user input on character */
    printf("Specify character to insert: ");
    /* this space in scan f is CRITICAL */
    scanf(" %c", &charIn);

    /* check ascii codes 32 - 127 */
    if(charIn < 32 || charIn > 127)
    {
      printf("---\n");
      /* Error message for inv input */;
      printf("* Invalid position! Try again.\n");
      printf("* You can only insert in already existing spaces or one after the last.\n");
    }
    else
    {
      /* the user input is valid */
      /* change flag as false to leave while loop */
      printf("---\n\n");
      charInFlag = FALSE;
    }
  }

  /* next function inserts it */
  pInsert(peep, modBuffer, position, charIn);

  /* print the string via loop and putchar */
  /* function - shows the string */
  peepString(peep, "INSERTING", "New Peep");
  /* function - shos position of each of the chars */
  peepShowPositions(peep);

  peepMenuBorder();

  return TRUE;
}

void pInsert(char *peep, struct transaction *modBuffer, int position, char charIn)
{
  /* enter it at a position and shift the rest right */
  /* nothing gets deleted or replaced */
  int pos, posLast = position;

  while(peep[posLast] != '\0')
    posLast++;

  for(pos = posLast; position < pos; pos--)
  {
    /* shift the array right by 1 starting at the end */
    /* up until the position the input char goes into */
    peep[pos] = peep[pos-1];
  }

  /*put the to be inputted char in the end */
  peep[position] = charIn;

  /* change the buffer fields for this edit */
  modBuffer->timestamp = getTimestamp();
  modBuffer->mod.position = position;
  modBuffer->mod.character = charIn;
  modBuffer->mod.event_type = 0;
}

unsigned long getTimestamp()
{
  /* variables */
  time_t seconds1970, seconds2018;
  unsigned long sinceJan2018;
  struct tm *tmVar;

  /* get EPOCH since 01-01-1970 LOCALTIME MOUNTAIN TIME*/
  seconds1970 = time(NULL);
  tmVar = localtime(&seconds1970);

  /* change to 01-01-2018 GMT */
  tmVar->tm_year = 118;
  tmVar->tm_mon = 0;
  tmVar->tm_mday = 1;
  tmVar->tm_hour = 0;
  tmVar->tm_min = 0;
  tmVar->tm_sec= 0;

  /* get the specified time in GMT */
  seconds2018 = mktime(tmVar);

  /* convert to LOCALTIME MOUNTAIN TIME */
  tmVar = localtime(&seconds2018);

  /* error checking */
  if(tmVar == NULL)
    {
      printf("Error getting time.\n");
      exit(0);
    }
  /* this gives you the seconds in mountain time from 01-01-18 to now */
  sinceJan2018 = seconds1970 - seconds2018;

  /* use this as a timestamop for peep edits */
  return sinceJan2018;
}

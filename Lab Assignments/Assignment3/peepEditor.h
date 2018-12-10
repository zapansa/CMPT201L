/*-------------------------------------------------------
# Student's Name: Patricia Zapansa, Alyssa Norton
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

/* macro guards */
#define TIMESTAMP_REPLAY

/* macros */
#define EXIT -1

/* edits the peep, saves transactions in modBuffer, and returns the number of transactions written in the buffer*/
unsigned int editor(char *peep, struct transaction *modBuffer);

int peepDelete(char *peep, struct transaction *modBuffer);

void pDelete(char *peep, struct transaction *modBuffer, int position);

int peepInsert(char *peep, struct transaction *modBuffer);

void pInsert(char *peep, struct transaction *modBuffer, int position, char charIn);

unsigned long getTimestamp();

int peepMenu();

void peepMenuBorder();

void peepInitialize(char *peep);

void peepString(char *peep, char *peepEdit, char *peepType);

void peepShowPositions(char *peep);

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

/* editor edits the peep, makes transactions on the peep - add or deleting
   chars in the peep
    - Params: char array, Transaction struct
    - Return: unsigned int of transaction amounts
    - Pre: all params are initalized and passed int
    - Post: an unsigned int is returned
*/
unsigned int editor(char *peep, Transaction *modBuffer);

/* this function asks for prompts for the deletion of the characters from the peep
    - Params: char array, Transaction struct
    - Return: an int is returned - signifying is successful transaction
    - Pre: all params are initalized and passed int
    - Post: an int is returned
*/
int peepDelete(char *peep, Transaction *modBuffer);

/* this function deletes from the peep in the given position
    - Params: char array, Transaction struct, int for position
    - Return: none
    - Pre: all params are initalized and passed int
    - Post: a char is deleted from the peep
*/
void pDelete(char *peep, Transaction *modBuffer, int position);

/* this function asks for prompts for the insertion (pos and char) of the characters from the peep
    - Params: char array, Transaction struct
    - Return: an int is returned - signifying is successful transaction
    - Pre: all params are initalized and passed int
    - Post: an int is returned
*/
int peepInsert(char *peep, Transaction *modBuffer);

/* this function inserts into the peep in the given position with given character
    - Params: char array, Transaction struct, int for position, and a char
    - Return: none
    - Pre: all params are initalized and passed int
    - Post: a char is inserted into the peep at a given position
*/
void pInsert(char *peep, Transaction *modBuffer, int position, char charIn);

/* this function creates a timestamp from (EPOCH time since January 1-st 2018)
   and then returns it
    - Params: none
    - Return: unsigned long - the EPOCH time since 01-01-18
    - Pre: function is cslled
    - Post: an unsigned long is returned
*/
unsigned long getTimestamp();

/* this function displays the menu of the peepEditor and prompts for choices
    - Params: none
    - Return: int
    - Pre: function is called
    - Post: menu is printed and choice int is returned
*/
int peepMenu();

/* when the transactions are exhaused, this prompts for choices on to either
   exiting ot opening up a new block or extending the block chain
    - Params: none
    - Return: char
    - Pre: function is called
    - Post: menu is printed and choice char is returned
*/
char peepExhausted();

/* this function is just s function for thr borders, function for convienience
   and cleanliness in formatting the menus and etc.
    - Params: none
    - Return: none
    - Pre: function is cslled
    - Post: a 'border' is printed
*/
void peepMenuBorder();

/* intialized all elements in the peep to '\0'
    - Params: char array
    - Return: none
    - Pre: function is called and char array is passed in
    - Post:
*/
void peepInitialize(char *peep);

/* this function shows the current peep in a string format
    - Params: 3 char array's
    - Return: none
    - Pre: all parameters are passed in the function
    - Post: peep 'string' is printed
*/
void peepString(char *peep, char *peepEdit, char *peepType);

/* this function shows the positions of all the characters in the string
    - Params: char array
    - Return: none
    - Pre: char array is passed in
    - Post: prints the positions of the chars in the peep 
*/
void peepShowPositions(char *peep);

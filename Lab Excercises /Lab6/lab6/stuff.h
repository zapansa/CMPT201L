/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #6, Part 2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

/* This function creates a dynamic array of struct stuff of size size.
   Returns a pointer to the array
   Precondition: an int is passed in
   Postcondition: a pointer to dynam. struct array is returned
*/
struct stuff * makeArray(int size);

/* Given a C-string input, this function makes a new struct stuff with
   that information stored and returns it
   Precondition: a char is passed in
   Postcondition: the new struct with info in it is returned
*/
struct stuff * makeStuff(char * data);

/* Given a valid struct stuff pointer, this function prints the stored
   string to standard output void
   Precondition: a struct pointer is passed in
   Postcondition: struct contents are printed
*/
void printStuff(struct stuff * printy);

/* This function takes a dynamic array of struct stuff and frees it
   along with all its dynamically allocated components
   Precondition: a size and a struct array is passed in
   Postcondition: the dynamically allocated array is printed.
*/
void freeStuff(int size, struct stuff * myArray);

/* Struct stuff */
struct stuff
{
  char * insides; /* a C-string */
  int size; /* stores the string length of insides */
};

#endif /*DYNAMICARRAY_H*/

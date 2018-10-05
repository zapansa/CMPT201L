/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #3, Part (#2b)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#ifndef CHANGE_H
#define CHANGE_H

/* This function gets the input from the user (fOwed, fPaid), and
   subtracts them to get another double to pass onto another function.
   Precondition: two floats have to be passed in.
   Postcondition: dollar_change() function is called.
*/
int change(float fOwed, float fPaid);

/* This function takes a double and uses it to calculate various
   equations, one of which is to be passed onto another function.
   Precondition: a double has to be passed in.
   Post condition: cent_change() function is called. 
*/
int dollar_change(double change);

/* This function takes a double and uses it to calculate various
   equations.
   Precondition: a double has to be passed in. 
   Post condition: Results from the various equations gets printed.   
*/
int cent_change(double change);

#endif /* CHANGE_H */


/*name:
 * lab section:
 * assignment:
 * last worked on:
 * due date:
 * file purpose: This is the header file for the numMod module.
 */

#ifndef NUMMOD_H
#define NUMMOD_H

/* This function re-initializes an array (myNums) of size with 1's
   Precondition: array must have the size passed in
   Post condition:  array values are all set to 1.  */
void zapArray(int *nums, int size);

/* This function sums two arrays (num1 and num2) of size together
   Precondition: both arrays (num1 and num2) must have size passed in
     (and be that size)
   Post condition: each position in the first array is changed to
     reflect the sum of the elements from both arrays.  */
void sumArray(int *num1,int *num2, int size);

/* This function sums two arrays (num1 and num2) of size together from
     an index
   Precondition: both arrays (num1 and num2) must have size passed in
     (and be that size)
   Post condition: each position in the first array is changed to
     reflect the sum of the elements from both arrays, starting at
     index.  */
void sumArrayIndex(int *num1,int *num2, int size, int index);

/* This function return the sum of the numbers in an array (num1 ) of
     size
   Precondition: both arrays (num1 and num2) must have size passed in
     (and be that size)
   Post condition: each position in the first array is changed to
     reflect the sum of the elements from both arrays.  */
int sumLinear(int *num1, int size);

#endif /* NUMMOD_H */

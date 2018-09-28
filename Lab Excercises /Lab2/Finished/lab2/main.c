/*name: Patricia Zapansa
 * lab section: CMPT 201 - X02L
 * assignment: Lab 2
 * last worked on: 09-27-2018
 * due date: 09-28-2018
 * file purpose: This is the source code file for the main program.
 */

/* Program description: This program does some simple array
   manipulation, using 2 modules, numMod and numArray. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> /*so we need to link the math library*/

#include "numArray.h"
#include "numMod.h"

int main() {
    int input[5], size = 5, option[5], temp;
    double result;
    
    printf("******Array Manipulation Program******\n");
    /*call the array filling function */
    numFill(input, size);
    
    /* do some manipulations on the arrays*/
    zapArray(option, size);
    sumArray(input, option, size);
    
    temp = sumLinear(input, size);
    /*math stuff!*/
    result = sqrt(temp);
    result = ceil(result);
    
    /*make new number for sure a valid index*/
    /* CHANGE #1, INSTRUCTION#2: adding 1 to (int)result%size for temp*/
    /* CHANGE #2, INSTRUCTION#4: add another 3, just so the result is diff from before.*/
    temp= ((int)result % size) + 1 + 3;
    sumArrayIndex(input, option, size, temp);
    
    /*print out the result array*/
    numPrint(input, size);

    return 0;
}


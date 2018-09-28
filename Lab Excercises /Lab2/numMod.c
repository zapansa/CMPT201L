/*name:
 * lab section:
 * assignment:
 * last worked on:
 * due date:
 * file purpose: This is the source code file for the numMod module.
 */
#include <stdlib.h>
#include <stdio.h>
#include "numMod.h"

void zapArray(int *nums, int size) {
    int i;
    
    /* if there is only one statement in the for loop, you don't need {} */
    for (i = 0; i < size; i++)
        /*set the current element to 1*/
        nums[i] = 1;
}

void sumArray(int *num1, int *num2, int size) {
    int i;
    
    for (i = 0; i < size; i++)
        num1[i] = num1[i] + num2[i];
}

void sumArrayIndex(int *num1, int *num2, int size, int index) {
    int i;
    
    for (i = index; i < size; i++)
        num1[i] = num1[i] + num2[i];
}

int sumLinear(int *num1, int size) {
    int i, sum = 0;
    
    for (i = 0; i < size; i++)
        sum += num1[i];
    return sum;
}

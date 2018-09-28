/*name: Patricia Zapansa
* lab section: CMPT 201 - X02L
* assignment: Lab 2
* last worked on: 09-27-2018
* due date: 09-28-2018
* file purpose: This is the source code file for the numArray module.
*/
#include <stdlib.h>
#include <stdio.h>

#include "numArray.h"

void numFill(int *myNums, int size) {
    int i;
    
    /* if there is only one statement in the for loop, you don't need {} */
    for (i = 0; i < size; i++)
        /* you must tell scanf what address to put the input at */
        scanf("%d", &myNums[i]);
}

void numPrint(int *myNums, int size) {
    int i;
    
    /* if there is only one statement in the for loop, you don't need {} */
    for (i = 0; i < size; i++)
        printf("%d ", myNums[i]);
    /* easier to read with lines ended*/
    printf("\n");
}

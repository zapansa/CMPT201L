/*name:
* lab section:
* assignment:
* last worked on:
* due date:
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

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE (128)

int main(void)
{
  /* Define Variable */
  int i;
  int *arrLeak = malloc(ARRAY_SIZE * sizeof(int)); /* Allocates space for array */

  /* Add stuff to array */
  for(i=0; i < ARRAY_SIZE; i++)
    arrLeak[i] = i*i;

  /* Print the 99th in array */
  printf("The 99th number in the array is %d.\n", arrLeak[99-1]);

  /* Ends without freeing arrLeak */
                 /* otherwise
  free(arrLeak)     should be here */

  return 0;
}

/*
WHAT SHOULD HAPPEN IN THE MEMORY LEAK?
- There is (128*4) bytes lost in a block of memory, integers are 4 bytes
  each and we have 128 of them.

RUNNING VALGRIND?
- Compile the program normally.
- Using valgrind like you would gcc.
  ie. valgrind ./[executable]
  This is show you what is lost and might be lost.
- Rerun with --leak-check=full to see the specific details.
  ie. valgrind --leak-check=full ./[executable]
  It can show you what line where the memory leak happened.

THIS PROGRAM?
- This program should have a memory leak at line 10.
- There is (128*4) bytes of space allocated for the array.
- But nothing is freed before exiting the program - memory leak.
*/

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #7, demo
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/
#include <stdio.h>

/* This function should return the result of shifting the bits of i to the
   right by n places, with the bits that were “shifted” off moved to the left
   end of i.
   Preconditions: An unsigned int and an int is passed into the function
   Postconditions: The right shifted hex is returned
*/
unsigned int rotate_right(unsigned int i, int n);

/* This function checks the parity of a number (if it has odd or even parity)
   Preconditions: An unsigned int is passed into the function
   Postconditions: 1 or 0 is returned depending on result (they are ints)
*/
int parityTest(unsigned int x);

int main(void)
{
  /* variables */
  unsigned int i, j;
  int n;

  /* get user input */
  printf("Enter Hexadecimal Digit: ");
  scanf("%x", &i);
  printf("Enter Shift Amount: ");
  scanf("%d", &n);

  /* call to rotate digit and print */
  unsigned int rotated = rotate_right(i, n);
  printf("0x%x rotated by %d is 0x%x\n", i, n, rotated);

  printf("Enter Hexadecimal for Parity Test: ");
  scanf("%x", &j);

  /* call to rotate digit and print */
  int oddEven = parityTest(j);
  printf("%d\n", oddEven);

  return 0;
}

unsigned int rotate_right(unsigned int i, int n)
{
  /* sources: https://bit.ly/2S55UiK, https://bit.ly/2S55UiK */
  /* variables */
  unsigned int a;

  /* shift i right by n */
  a = ((i>>n) | (i<<(8*sizeof(i)-n)));

  /* return shifted result */
  return a;
}

int parityTest(unsigned int x)
{
  /* sources: https://bit.ly/2SbqSwx, https://bit.ly/2PQoS06 */
  /* assumes int is 32 bit */
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1; /* gets rid of the least siginificant bit */

  return x&1;
}

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #7, demo
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>

unsigned int rotate_right(unsigned int i, int n);
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
  unsigned int oddEven = parityTest(j);
  printf("%d\n", oddEven);

  return 0;
}

unsigned int rotate_right(unsigned int i, int n)
{
  unsigned int a;

  /* shift i right by n */
  a = ((i>>n) | (i<<(8*sizeof(int)-n)));

  /* return shifted result */
  return a;
}

int parityTest(unsigned int x)
{
  unsigned int bit = 0, b = 1;
  int i;

  for(i=0; i<32; i++)
    if(x&(b<<i))
      bit++;

  if(bit%2)
    printf("%d\n", bit%2);
    return 0;
}

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Exercise  #4  Part (Demo)
# Lab Section: AS01
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/ 
#include <stdio.h> 

int main(void)
{
  // Declare Variables
  int size, row, col, trade; 

  // Get input from user
  printf("Enter the size of the matrix: ");
  scanf("%d", &size);
  
  // Matrix 1 - Get matrix 1 input
  int m1[size][size];
  printf("Enter Matrix 1 (by row)\n");
  for(row=0; row<size; row++)
    for(col=0; col < size; col++)
      scanf("%d", &m1[row][col]);

  // Matrix 2 - Get matrix 2 input
  int m2[size][size];
  printf("Enter Matrix 2 (by row)\n");
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
      scanf("%d", &m2[row][col]);

  // Multiplied Matrix - Set all values to 0
  int mm[size][size];
  printf("The result of multiplication is:\n");
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
      mm[row][col] = 0; 
  
  // Matrix multiplication
  // set new values to mm (multiplied  matrix)
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
      for(trade=0; trade<size; trade++)
	mm[row][col] += m1[row][trade]*m2[trade][col];

  // Print multiplied matrix
  int counter = 0;
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
      {
        if(counter != 0 && counter%size == 0)
            printf("\n");
        counter++;
        printf("%-3d", mm[row][col]);
      }
  printf("\n");

  return 0;
}

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Excercise #4, Part (#2)
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#define MAX_SIZE (8)

/* This function gets a 2d array and a size from main
   it asks for user input on the values inside the
   2d array (matrix) and initializes it to appropriate index.
   Precondition: 2d int array and an array to be passed in
   Post condition: values of passed 2d array are initalized
*/
void get_matrix(int matrix[MAX_SIZE][MAX_SIZE], int size);

/* This function prints the main diagonal values of the
   2d array (matrix).
   Precondition: 2d int array and an array to be passed in
   Post condition: main diagonal values are printed
*/
void get_m_diagonal(int matrix[MAX_SIZE][MAX_SIZE], int size);

/* This function multiplies all of the values of the
   secondary diagonal in the 2d array (matrix)
   Precondition: 2d int array and an array to be passed in
   Post condition: product of secondary diagonal in the matrix
   is printed
*/
void get_s_diagonal(int matrix[MAX_SIZE][MAX_SIZE], int size);

/* This function calculates the sums of each column in the
   2d array(matrix).
   Precondition: 2d int array and an array to be passed in
   Post condition: there is a call to the print_col_sums function
*/
void get_col_sums(int matrix[MAX_SIZE][MAX_SIZE], int size);

/* This function is passed an int array from get_col_sums,
   iterates through it and prints each value.
   Precondition: an int array and int is passed in
   Post condition: elements in int array are printed
*/
void print_col_sums(int colSums[], int size);

int main(void)
{
  int matrix[MAX_SIZE][MAX_SIZE];
  int size;
  
  /* Get user input */
  printf("Enter the size of the matrix (max size 8): ");
  scanf("%d", &size);

  /* Call function for input in the matrix */
  get_matrix(matrix, size);

  /* functions for some calculations */
  get_m_diagonal(matrix, size);
  get_s_diagonal(matrix, size);
  get_col_sums(matrix, size);

  return 0;
}

void get_matrix(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
  /* Declare Variables */
  int row, col;

  /* Get user input */
  printf("Enter the matrix row by row: \n");
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
        scanf("%d", &matrix[row][col]);
}

void get_m_diagonal(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
  /* Declare variables */
  int row = 0, col = 0, diag;

  /* get elements on main diagonal [ \ ] */
  printf("The elements on the main diagonal are: ");
  for(diag = 0; diag<size; diag++)
        printf("%-2d", matrix[row++][col++]);
  printf("\n");
}

void get_s_diagonal(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
  /* Declare Variables */
  int row, col, prod = 1;

  /* For loop to multiply secondary diagonal values */
  for(row=0; row<size; row++)
    for(col=0; col<size; col++)
      if((row+col) == (size-1))
        prod *= matrix[row][col];

  printf("The product of the elements on the secondary diagonal is: %d\n", prod);
}

void get_col_sums(int matrix[MAX_SIZE][MAX_SIZE], int size)
{
  /* Declare Variables */
  int i = 0, row, col, colSums[size];

  /* For loop to sum each column */
  for(col=0; col<size; col++) /* For every column */
    {
      colSums[i] = 0;
      for(row=0; row<size; row++) /* iterate through the rows */
        colSums[i] += matrix[row][col];
      i++;
    }

  /* Pass colSums to another function to print (e) */
  print_col_sums(colSums, size);
}

void print_col_sums(int colSums[], int size)
{
  /* Declare Variables */
  int i;

  /* Iterate through int array, print each element */
  for(i=0; i<size; i++)
    printf("The sum of elements on column %d is: %d\n", i+1, colSums[i]);
}

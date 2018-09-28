/* CMPT 201: Lab #1
   digits.c: a simple C program that prints out the number of digits
   in an integer
*/

#include <stdio.h>

int main() {
    int digits = 0, number;

    printf("Enter a non-negative number: ");
    scanf("%d", &number);

    while (number > 0) {
        number /= 10;
        digits++;
    }
    digits += 1;

    printf("Number of digits + 1: %d\n", digits);

    return 0;
}

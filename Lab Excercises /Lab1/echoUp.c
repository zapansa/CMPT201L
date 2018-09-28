/* CMPT 201: Lab #1
   echoUp.c: a simple C program for practising I/O redirection
*/

#include <ctype.h>
#include <stdio.h>

int main() {
    int ch;

    // read character
    ch = getchar();
    while (ch != EOF){
        // uppercase and print character
        ch = toupper(ch);
        putchar(ch);

        ch = getchar();
    }

    return 0;
}

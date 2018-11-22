/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Exercise #7, demo
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

/* 
   NOTE: 
   - compile -> gcc -std=c99 -o demo demo.c -lcrypto 
   - quick and dirty -> could separate & improve (but should I do it though thinking emoji)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <time.h>

int main(int argc, char **argv)
  {
    /* vars */
    char *filename = *(argv+(argc-1));
    unsigned char *fileBuffer;
    FILE *fd1;
    unsigned int fileSize, fileLen;

    /* open file for reading */
    fd1 = fopen(filename, "r");

    /* checking if file exists */
    if(!fd1) /* doesnt exist */
      {
        printf("File does not exist...\n");
        exit(0);
      }
    else /* exists */
      {
        /* get the file size */
        fseek(fd1, 0, SEEK_END);
        fileSize = ftell(fd1);
        fseek(fd1, 0, SEEK_SET);

        /* malloc the string array */
        fileBuffer = malloc(fileSize*sizeof(char));

        /* read content into buffer */
        fileSize = fread(fileBuffer, sizeof(char), fileSize, fd1);

        /* null terminate file */
        *(fileBuffer+fileSize) = '\0';

        printf("Input Contents:\n%s\n", fileBuffer );	
      }

    /* get the time in seconds */
    time_t seconds;
    struct tm *sec;
    unsigned int secSize = 10; 
    unsigned char *secBuffer = malloc(secSize+1);

    /* raw time */
    seconds = time(NULL);
    sec = localtime(&seconds);

    /* error check seconds */
    if(sec==NULL)
      {
        printf("Error getting the time.\n");
        exit(0);
      }
    else
      {
        /* Epoch */
	secBuffer = "hello world!";
	// strftime(secBuffer, secSize+1, "%s", sec);
        printf("Timestamp:\n%s\n\n", secBuffer);
      }
  
    /* concatenate the file + time */
    unsigned int catSize = strlen(fileBuffer) + strlen(secBuffer);
    char *catBuffer = malloc(catSize+1);

    /* make all algorithms available */
    OpenSSL_add_all_algorithms();
    EVP_MD_CTX *ctx;
    ctx = EVP_MD_CTX_create();
  
    /* produce SHA256 digest*/
    const EVP_MD *hashptr = EVP_get_digestbyname("SHA256");
    EVP_MD_CTX_init(ctx);
    EVP_DigestInit_ex(ctx, hashptr, NULL);
    EVP_DigestUpdate(ctx, fileBuffer, fileSize);
    EVP_DigestFinal_ex(ctx, catBuffer, &catSize);
    EVP_MD_CTX_cleanup(ctx); 

    /* does this print the hash lol */
    printf("Hashed Input:\n");
    for(int i=0; i< strlen(catBuffer); i++) /* great, now you have to specify c99 :'( */
        printf("%02x", catBuffer[i]);
    printf("\n\n");

    /* exit */
    return 0;
  }


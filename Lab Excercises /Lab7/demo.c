/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment 2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <time.h>

int main(int argc, char **argv)
{
  /* vars */
  char *filename = *(argv+(argc-1));
  unsigned char *buffer;
  FILE *fd1;
  int fileSize, len;

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
    buffer = malloc(fileSize*sizeof(char));

    /* read content into buffer */
    len = fread(buffer, sizeof(char), fileSize, fd1);

    /* null terminate file */
    *(buffer+len) = '\0';

    printf("%s\n", buffer );
  }
  /*----------------------------------------------*/

  OpenSSL_add_all_algorithms();

  EVP_MD_CTX ctx;
  const EVP_MD *hashptr = EVP_get_digestbyname("SHA256");

  EVP_MD_CTX_init(&ctx);
  EVP_DigestInit_ex(&ctx, hashptr, NULL);



  return 0;
}

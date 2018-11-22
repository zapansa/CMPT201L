/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Program Description: this program looks at the inside of the bins and lists
  the chunks from beginning of the list to the end. Its use is so that i can
  check if the blocks arein increasing order. It contains a function that is
  derived from the original outputBins().
*------------------------------------------------------*/
#include "memManager.h"

char SEPARATOR[] = "******************************************************";

/* testing to see if chunks get
   added to the list in increasing
   order
   no params or returns
   pre: memory is initialized
   post: results get printed
*/
void test1();

/* testing if merging works and the
   chunks are all still in order
   no params or returns
   pre: memory is initialized
   post: results get printed
*/
void test2();

/* testing to see if fixed
   sized chunks work
   no params or returns
   pre: memory is initialized
   post: results get printed
*/
void test3();

/* prints order of chunks
   no params or returns.
   pre: there is freed bins to print
   post: displays the bins
*/
void binOut();

int main(void)
{
  test1();
  test2();
  test3();
}

void test1()
{
  /* each free'd separated by a block. Multple in one bin variable size */
  initializeMem();
  void *a = myMalloc(120);
  myMalloc(400);
  void *b = myMalloc(160);
  myMalloc(400);
  void *c = myMalloc(170);
  myMalloc(400);
  void *d = myMalloc(180);
  myMalloc(400);
  void *e = myMalloc(150);
  myMalloc(400);
  void *f = myMalloc(196);
  myMalloc(400);
  void *g = myMalloc(147);
  myMalloc(400);
  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);
  myFree(e);
  myFree(f);
  myFree(g);

  // outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  binOut();
  printf("\n%s\n", SEPARATOR);

  /*
  BIN SIZE 128 CONTENTS:
  	CHUNK SIZE 124

  BIN SIZE 256 CONTENTS:
  	CHUNK SIZE 152
  	CHUNK SIZE 156
  	CHUNK SIZE 164
  	CHUNK SIZE 176
  	CHUNK SIZE 184
  	CHUNK SIZE 200

  BIN SIZE 65536 CONTENTS:
  	CHUNK SIZE 61480
 */
}

void test2()
{
  /* same as test 2 but with merged chunks */
  initializeMem();
  void *a = myMalloc(120);
  void *b = myMalloc(160);
  myMalloc(400);
  void *c = myMalloc(170);
  myMalloc(400);
  void *d = myMalloc(180);
  myMalloc(400);
  void *e = myMalloc(150);
  myMalloc(400);
  void *f = myMalloc(196);
  void *g = myMalloc(147);
  myMalloc(400);
  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);
  myFree(e);
  myFree(f);
  myFree(g);

  // outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  binOut();
  printf("\n%s\n", SEPARATOR);

  /* Correct:
      BIN

       SIZE 256 CONTENTS:
      CHUNK SIZE 156
      CHUNK SIZE 176
      CHUNK SIZE 184

      BIN SIZE 512 CONTENTS:
      CHUNK SIZE 288
      CHUNK SIZE 352

      BIN SIZE 65536 CONTENTS:
      CHUNK SIZE 62288
  */
}

void test3()
{
  /* each free'd separated by a block. Multple in one bin variable size */
  initializeMem();
  void *a = myMalloc(12);
  myMalloc(400);
  void *b = myMalloc(12);
  myMalloc(400);
  void *c = myMalloc(12);
  myMalloc(400);
  void *d = myMalloc(23);
  myMalloc(400);
  void *e = myMalloc(23);
  myMalloc(400);
  void *f = myMalloc(23);
  myMalloc(400);
  void *g = myMalloc(23);
  myMalloc(400);
  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);
  myFree(e);
  myFree(f);
  myFree(g);

  // outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  binOut();
  printf("\n%s\n", SEPARATOR);

  /*
  BIN SIZE 16 CONTENTS:
  	CHUNK SIZE 16
  	CHUNK SIZE 16
  	CHUNK SIZE 16

  BIN SIZE 28 CONTENTS:
  	CHUNK SIZE 28
  	CHUNK SIZE 28
  	CHUNK SIZE 28
  	CHUNK SIZE 28

  BIN SIZE 65536 CONTENTS:
  	CHUNK SIZE 62476
 */
}

void binOut()
{
  /* Declaring some variables */
  int bin, startBlock, nextBlock, sizeBlock;
  for(bin=0; bin<=(BIN_HEADER_END-4); bin+=4)
  {
    /* Check for non empty bins to print info */
    if(binIsEmpty(bin) == FALSE)
    {
      /* this lists the bins and the chunks in the bin */
      /* in order of what comes 'next' until the end */
      printf("\nBIN SIZE %d CONTENTS:\n", findBinSize(bin));
      startBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;
      nextBlock = *((unsigned short *)(&myMemory[startBlock+NEXT]));
      sizeBlock = *((unsigned short *)(&myMemory[startBlock]));
      printf("\tCHUNK SIZE %d\n", sizeBlock);

      while(nextBlock != (bin+PAD2))
      {
        startBlock = nextBlock-PAD4; /* goes to the next block startline*/
        nextBlock = *((unsigned short*)(&myMemory[startBlock+NEXT])); /* next block rev line */
        sizeBlock = *((unsigned short *)(&myMemory[startBlock]));
        printf("\tCHUNK SIZE %d\n", sizeBlock);
      }
    }
  }

}

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
*------------------------------------------------------*/

#ifndef MEM_H
#define MEM_H

/* System Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h> /* for command line input */
#include <unistd.h>
#include <stdint.h> /* Silence void pointer cast warning */

/* Aligns to 4 bytes Source: https://bit.ly/2FrL3EO */
#define ALIGN4(x) (((((x)-1)>>2)<<2)+4)

/* Macrodefs to make keeping track of pointers easier (for me) */
#define PAD2 2
#define PAD4 4
#define PREV 4
#define NEXT 2

/* True and False Macro Defs   */
#define TRUE 1
#define FALSE 0

/* start and ends of memory */
#define MAX_TOTAL_MEMORY 65536
#define BIN_HEADER_END 72

/* pointer to initialized memory */
char *myMemory;

/*--------------------------- memMapMgr.c Functions ---------------------------*/

/* Initalizes the memory block, dynamically allocates it using malloc
   - PARAMS: None
   - RETRUN: Void
   - PRE: myMemory is of type char *
   - POST: The function initializeBin() is called
*/
void initializeMem();

/* Initializes all the bins in the first 72 bytes of memory makes them all
   reference themselves and adds the fist block of size 65464 to the appropriate
   sized bin.
   - PARAMS: None
   - RETURN: Void
   - PRECONDITIONS: myMemory is initialized
   - POSTCONDITIONS: binBlock is called to add the block of size 65464 to the
     correct bin.
*/
void initializeBin();

/* Allocates the requested bytes, size, and returns a Pointer to the beginning
   of the allocated memory. If the space cannot be allocated, then NULL is returned.
   - PARAMS: size - number of bytes to allocate
   - RETURN: a pointer to a newly allocated memory region of the desired size
     or NULL if allocation fails
   - PRECONDITIONS: 0 < size < MAX_TOTAL_MEMORY
   - POSTCONDITIONS: region is allocated, and valid pointer is returned
     OR region is not allocated, and NULL is returned
*/
void *myMalloc(size_t size);

/* Frees the memory region at the GIVEN POINTER, region, that was previously
   allocated using myMalloc.It gives the chunk of memory containing region back
   to the allocator, and allows for it to be reused in the future.
   - PARAMS: region - a pointer to an allocated memory region
   - RETURN: void
   - PRECONDITIONS: myMemory + 76 <=bin <myMemory +  MAX_TOTAL_MEMORY
   - POSTCONDITIONS: the chunk containing region is added to the available memory
*/
void myFree(void *region);

/* Output all information regarding the bins of UNUSED chunk available for allocation.
   - PARAMS: no ne
   - RETURN: void
   - PRECONDITIONS: myMemory is initialized
   - POSTCONDITIONS: prints on stdout information about each bin in the format:
        +----------+------------+----------+
        | Bin Size | Total Bins | Sum      |
        |          |            |          |
        where:
            Bin Size-is the size of the bin
            Total Bins-is the number of chuncks in the bin
            Sum-is the sum of the sizes of all chuncks in the bin
*/
void outputBins();

/* Output all blocks of Memory and their status
   - PARAMS: None
   - RETURN: Void
   - PRECONDITIONS: myMemory is initialized
   - POSTCONDITIONS: Prints on stdout info about all blocks of Memory in the format:
        +---------+-------+------------+-------+
        |  Status | Start | Block Size | End   |
        |         |       |            |       |
        where:
           Status-is the status of the chunk containing the block
           Start-is the beginning of the block (the beginning of the user data space)
           Block Size-is the size of the block
           End-is the end of the block (the end of the user data space)
*/
void outputMemory();

/* This function basically returns a TRUE or FALSE (1 or 0) to check if a bin
   is empty or not.
   - PARAMS: An int that represents the 'line' where in which the bin is in myMemory
   - RETURN: An integer (1 or 0)
   - PRECONDITIONS: An integer is passed in the function.
   - POSTCONDITIONS: An int (macro def'd as TRUE or FALSE) is returned.
*/
int binIsEmpty(int binLine);

/* A this function is used to check if there is enough available memory for a
   size of requested size to be allocated using myMalloc.
   - PARAMS: An integer.
   - RETURN: An integer (1 or 0)
   - PRECONDITIONS: An integer is passed into the function
   - POSTCONDITIONS: An int (macro def'd as TRUE or FALSE) is returned.
*/
int memIsEmpty(int memSize);

/* This function finds the "index" of a bin or a particular size
   - PARAMS: An integer representing a block/chunk size
   - RETURN: An integer representing the index of the bin of chunk of particular size
   - PRECONDITIONS: An integer is passed into the function.
   - POSTCONDITIONS: An integer representing the index of the bin in myMemory is
     returned.
*/
int findBinLine(int size);

/* This function finds the size of the bin associated with the index of the bin,
   it's really only used in the outputBins() function.
   - PARAMS: An int representing the index of the bin.
   - RETURN: An int representing the chunk size of the bin that block is
     associated with.
   - PRECONDITIONS: An integer is passed in representing the index of a bin
   - POSTCONDITIONS: An integer is returned from the function
*/
int findBinSize(int size);

/* This function gets the void address of a chunk of memory and finds the line
   where it starts in myMemory.
   - PARAMS: A void pointer representing an allocated chunk of memory
   - RETURN: An integer representing the index line of the allocated memory chunk
   - PRECONDITIONS: A void pointer is passed into the function.
   - POSTCONDITIONS: The integer represeting the index of the allocated memory
     chunk is returned.
*/
int findBlockLine(void *region);

/* This function is CALLED binBlock() because of the splitting it does for
   myMalloc but it is also just used as a way to put a block of memory inside of
   a bin. Because of this, it is used in initializeMem() and myFree() as well as
   being used in myMalloc().
   - PARAMS: 3 integers, the bin index the chunk will go into, the line where the
     block of memory is (it's index), and the size of the block of memory.
   - RETURN: Void
   - PRECONDITIONS: Three integers are passed into the function.
   - POSTCONDITIONS: The blocks of memory are CDDL into the appropriate sized bin.
*/
void binBlock(int bin, int newBlock, int size);

/* This function sets the block into a USED "status", aka the 1 is added to the
   size of the block, making it indivisiable by 4.
   - PARAMS: 2 integers, one represents the line a block starts with and the
     other, the size of the block/chunk of memory.
   - RETURN: void
   - PRECONDITIONS: Two integers are passed into the function.
   - POSTCONDITIONS: The size of the block is incremented by 1 and is freed from
     it's previous links making it USED.
*/
void useBlock(int block, int size);

/* This function basicallyls -1 removes the links from a block and makes the block/or
   this bin, above and below it link to eachother instead.
   - PARAMS: An int represents the line that the block starts in.
   - RETURN: void
   - PRECONDITIONS: An integer is passed into the function.
   - POSTCONDITIONS: The block switches its links with the blocks or bin below
     and above it.
*/
void linkBlock(int block);

/* This block unlinks a chunk of memory from its bin so it could be merged with
   another chunk of memory beside it.
   - PARAMS: An int represeting the index of a chunk/block of memory (where it starts).
   - RETURN: void
   - PRECONDITIONS: An integer is passed into a function.
   - POSTCONDITIONS: The block of memory is unlinked from its previous bin.
*/
void freeBlock(int block);

/* This block checks if an inputted address is a valid block to be freed.
   PARAMS: and integer representing a region of a potential to be freed block
   RETURN: An integer (1 or a 0)
   PRECONDITIONS: a valid int is passed
   POSTCONDITIONS: A 1 or 0 integer is returned.
*/
int checkFree(int region);

/*--------------------------- memManager.c Functions --------------------------*/

/* This function, initializes the memory, initializes all of the bins and creates
   an "empty" memory map.
   - PARAMS: a char pointer
   - RETURN : Void
   - PRECONDITIONS: A char pointer is passed
   - POSTCONDITIONS: a binary file of myMemory is exported to a file
*/
int emptFile(char *filename);

/* This function imports the 'memory' of a binary file.
   - PARAMS: a char pointer
   - RETURN: an int that represents if a file was read succesfully
   - PRECONDITIONS: A char pointer needs to be passed into the function
   - POSTCONDITIONS: The file contents is transferred into myMemory
*/
int impFile(char *filename);

/* this function exports the 'memory' of a binary file.
   - PARAMS: a char pointers
   - RETURNS: an int that represents if a file was written succesfully
   - PRECONDITIONS: a char pointer needs to be passed into the function
   - POSTCONDITIONS: The 'memory' is 'exported' into a file or an int is returned.
*/
int expFile(char *filename);

/* Functin reads a file and prints out the statistics for it aka, the bins and then
   the whole memory.
   - PARAMS: a char pointer representing the filename
   - RETURNS: an int that represents if a file was written succesfully
   - PRECONDITIONS: a char pointer is passed into the array
   - POSTCONDITIONS: The 'empty memory' is 'exported' into a file or an int is returned.
*/
int statFile(char *filename);

#endif /* MEM_H */

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

/* system includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>
#include <openssl/evp.h>

/* macros */
#define TRUE 1
#define FALSE 0

#define MXTXNUM 64 /* The maximum number of transactions allowed in one block. */
#define PEEPLEN 256 /* The max length of a peep */

/*---------------------------------DATA STRUCTURES-----------------------------*/

/* Structure to Represent a modification [2 bytes]. (modification)
	 position	- Position in the peep that the event occured: Maximum position of 256
	 character	- The character that was modified  - ASCII codes 32 to 127
   event_type	- Type of event that has occured.
				  0 for Insert
				  1 for Delete
   NOTE: Bitfields must be used to condense data in memory and when written
*/
typedef struct modification
{
  unsigned char position: 8;
  unsigned char character: 7;
  unsigned char event_type: 1;
} Modification;

/* Structure to Represent a Transaction [8 bytes] (transaction)
	 timestamp	- Time that the event occurred (EPOCH time since January 1-st 2018). [6 bytes]
	 modification	- The modification part of the transaction. [2 bytes]
*/
typedef struct transaction
{
  unsigned long timestamp: 48; /* ????????????? */
  Modification mod; /* should already give two bytes */
} Transaction;

/* Structure to Represent a Block  [32 bytes for the  head + up to 8*64 bytes for transactions] (block)
	 previousHash	- Hash of the Previous block head. 0 if first. [7 bytes]
 	 timeStamp - Time that the hashing of the block occured. [6 bytes]
	 blockNum	- Incremental number of the block. [4 bytes]
	 blockSize - Size of transaction elements in the block. [1 byte]
	 blockHash - The Merkle tree hash of the transactions. [7 bytes]
	 headHash	- Hash of the head elements above. [7 bytes]
	 transactions	- Transactions contained in the block (maximum of 64 transactions)
NOTE: a hash of length 7 bytes is obtained by taking the last 7 bytes of the sha256 hash
      The truncation is to be applied only as the final step.
      All intermediary hashes are full sha256 hashes
*/
typedef struct block
{
  unsigned char previousHash[7]; /* head */
  unsigned long timestamp: 48; /* head */
  unsigned long blockNum: 32; /* head */
  unsigned long blockSize: 8; /* head */
  unsigned char blockHash[7]; /* head */
  unsigned char headHash[7]; /* hash of all the fucking heads */
  Transaction trns[MXTXNUM];
} Block;

/*------------------------------------FUNCTIONS--------------------------------*/

/* writeBlockChain - writes a block chain to a file
    - Params: char array, block structure, int, char array
    - Return: int
    - Pre: all values in params are passed
    - Post: an int is returned showing if successful
*/
int writeBlockChain(char peep[], Block *blkBuffer, int blockSz, char *filename);

/* readBlockChain - reads a block chain from a file
    - Params: char array, block structure, char array
    - Return: int
    - Pre: all values in params are passed
    - Post: an int is returned showing if successful
*/
int readBlockChain(char peep[], Block **blkBuffer, char *filename);

/* newBlockChain - makes a new empty peep + blockchain
    - Params: char array, block structure, char array
    - Return: int
    - Pre: all values in params are passed
    - Post: an int is returned showing if successful
*/
int newBlockChain(char peep[], Block **blkBuffer, char *filename);

/* errReadWrite - prints error message if the file read is unsuccessful
    - Params: char array
    - Return: none
    - Pre: char array is passed into function
    - Post: prints a message
*/
void errReadWrite(char *filename);

/* prints an error message if no transactions made on the block and then
   exits the program
    - Params: non
    - Return: none
    - Pre: the function is called
    - Post: an error messahe is printed and program is exited
*/
void errNoTransactions();

/* hashes the block and adds the hash the of the headblock to the block before saving
    - Params: block struct
    - Return: none
    - Pre: a block struct is passed in and exists
    - Post: adds the hash of the block to the block headHash
*/
void addBlockHash(Block *blkBuffer);

/* adds the previous hash the of the headblock to the block before saving
   copies the previous hash from the previous block
    - Params: block struct
    - Return: none
    - Pre: a block struct is passed in and exists
    - Post: adds the previous block headhash to the current's prev hash
*/
void addPreviousHash(Block *currBlockBuffer, Block *prevBlockBuffer);

/* addTransacions - adds a new session of transactions at the end of the block chain starting with a new block
    - Params: 2 ints, transaction struct, block struct
    - Return: none
    - Pre: all the parameters are passed in the function
    - Post: adds all the transaction info to the block
*/
void addTransactions(int trnsAmt, int blkAmt, Transaction *modBuffer, Block *blkBuffer );

/* printTransactions - prints all transactions contained in the blockchain & block info
    - Params: int, block struct
    - Return: none
    - Pre: all the parameters are passed in the function
    - Post: adds all the transaction info to the block
*/
void printTransactions(int blkAmt, Block *blkBuffer);

/* gets the amount of blocks in the file
    - Params: int
    - Return: int - the amount of blocks -1
    - Pre: an integer is passed in
    - Post: returns an int of how manu blocks are in the blockchain - 1
*/
int getBlockAmt(int blkBufferByteSz);

/* produces the peep at a certain time stamp by replaying all the transactions in the block chain up to (and including) the time stamp
   if a block timestamp is entered, everything up to and including that whole block will be played
    - Params: 2 ints, char array, stuct transaction, block struct
    - Return: none
    - Pre: all the parameters are passed in
    - Post: prints the peep up until a current timestamp
*/
void getPeepAtTime(int blkAmt, int tmStamp, char *peep, Transaction *modBuffer, Block *blkBuffer);

/* produces the current peep by replaying all the transactions contained in the blockchain
   if a block timestamp is entered, everything up to and including that whole block will be played
    - Params: an int, char array, stuct transaction, block struct
    - Return: none
    - Pre: all the parameters are passed in
    - Post: prints the CURRENT most recent peep
*/
void getPeep(int blkAmt, char *peep, Transaction *modBuffer, Block *blkBuffer);

/* verifyBlockChain - verifies the integrity of the block chain
   if a block timestamp is entered, everything up to and including that whole block will be played
    - Params: an int, and a block struct
    - Return: none
    - Pre: all the parameters are passed in
    - Post: checks all blocks and rehashed to make sure it is a valid blockchain
*/
void verifyBlockChain(int blkAmt, Block *blkBuffer);

/*-------------------------------------------------------
# Student's Name: Patricia Zapansa, Alyssa Norton
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

#define TRUNCBYTES 7 /* amount of bytes from hash stored */ 

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

/* writeBlockChain - writes a block chain to a file */
int writeBlockChain(char peep[], struct block *blkBuffer, int blockSz, char *filename);

/* readBlockChain - reads a block chain from a file */
int readBlockChain(char peep[], struct block **blkBuffer, char *filename);

/* newBlockChain - makes a new empty peep + blockchain */
int newBlockChain(char peep[], struct block **blkBuffer, char *filename);

/* errReadWrite - prints error message */
void errReadWrite(char *filename);

/* addTransacions - adds a new session of transactions at the end of the block chain starting with a new block */
void addTransactions(int trnsAmt, int blkAmt, Transaction *modBuffer, Block *blkBuffer );

/* printTransactions - prints all transactions contained in the blockchain */
void printTransactions(int blkAmt, struct block *blkBuffer);

/* gets the amount of blocks in the file */
int getBlockAmt(int blkBufferByteSz);

/* produces the peep at a certain time stamp by replaying all the transactions in the block chain up to (and including) the time stamp */
void getPeepAtTime(int blkAmt, int tmStamp, char *peep, struct transaction *modBuffer, struct block *blkBuffer);

/* produces the current peep by replaying all the transactions contained in the blockchain */
void getPeep(int blkAmt, char *peep, struct transaction *modBuffer, struct block *blkBuffer);

/*
verifyBlockChain - verifies the integrity of the block chain
*/

/*------------------------------------TESTING----------------------------------*/

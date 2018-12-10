/*-------------------------------------------------------
# Student's Name: Patricia Zapansa, Alyssa Norton
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

typedef struct merkleLeaf
{
  unsigned int height; 
  unsigned char hash[32];
} LEAF;

/* a structure to keep the hashes */
/* merkle tree done via a stack */  
typedef struct merkleTreeNode
{
  LEAF hash;
  unsigned capacity; 
  struct merkleTreeNode *next;
} TREE;

/* SHA256 */
#define EVPMAXSZ 64
#define HASHSELF -1
#define HASHCOUP -2
#define HASHTRNS -3

/* push new node the merkle tree */ 
TREE *push(TREE *top, char hash[32], int height);

/* pop node */
TREE *pop(TREE *top, int *height);

/* initialize tree */ 
void initTree(Transaction *modbuffer, int trnsAmt);	

/* hashing something */
void hashTransactions(Transaction *modBuffer, int trnsInd, char *hash256);
void hashTree(TREE *left, TREE *right, char *hash265);

void showStack(TREE *top);
int stackAmt(TREE *top);

TREE *getRoot(TREE *top, Transaction *modbuffer, int trnsAmt);
void addRoot(TREE *top, Block *blkBuffer);

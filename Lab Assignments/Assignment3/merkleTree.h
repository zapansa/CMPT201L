/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

typedef struct merkleHashData
{
  unsigned int height;
  unsigned char hash[32];
} DATA;

/* a structure to keep the hashes */
/* merkle tree done via a stack */
typedef struct merkleTreeNode
{
  DATA hash;
  struct merkleTreeNode *next;
} LEAF;

/* SHA256 */
#define HASHSZ 32

/* push new node the merkle tree
    - Params: a DATA struct, unsigned char
    - Return: a DATA struct - new top of stack
    - Pre: LEAF is initialized
    - Post: a LEAF struct is returned
*/
LEAF *push(LEAF *top, unsigned char hash[32], int height);

/* pops the top node off the "merkle tree"
    - Params: a DATA struct, unsigned char
    - Return: a DATA struct - new top of stack
    - Pre: LEAF is initialized
    - Post: a LEAF struct is returned
*/
LEAF *pop(LEAF *top);

/* checks how many LEAF structs there is
    - Params: a DATA struct, unsigned char
    - Return: a DATA struct - new top of stack
    - Pre: LEAF is initialized
    - Post: a LEAF struct is returned
*/
int stackAmt(LEAF *top);

/* function for hashing transactions from the modBuffer
    - Params: Transaction struct, int, unsigned char array
    - Return: none
    - Pre: all params are passed in
    - Post: transaction is hashed, pointer to array -> array is filled
*/
void hashTransactions(Transaction *modBuffer, int trnsInd, unsigned char *hash256);

/* function for hashing two leaves on the tree
    - Params: 2 LEAF structs, unsigned char array
    - Return: none
    - Pre: all params are passed in
    - Post: leftLeaf+rightLeaf is hashed, pointer to array -> array is filled
*/
void hashTree(LEAF *left, LEAF *right, unsigned char *hash265);

/* function for hashing a block header - first 25 bytes
    - Params: Block Struct, unsigned char array
    - Return: none
    - Pre: all params are passed in
    - Post: block header is hashed, pointer to array -> array is filled
*/
void hashBlockHeader(Block *blkBuffer, unsigned char *hash256);

/* function for calculating the merkle root of the hashes via a stack
    - Params: LEAF struct, Transaction struct, int
    - Return: LEAF stuct - new top of stack
    - Pre: all params are passed in
    - Post: LEAF struct is passed in
*/
LEAF *getRoot(LEAF *top, Transaction *modbuffer, int trnsAmt);

/* function for adding the merkle root to the block buffer
    - Params: LEAF struct, Block Struct
    - Return: none
    - Pre: all params are passed in
    - Post: Merkle root is added to the block's BlockHash
*/
void addRoot(LEAF *top, Block *blkBuffer);

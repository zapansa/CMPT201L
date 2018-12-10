/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes:
*------------------------------------------------------*/

/*rlibraries to include */
#include "blockChain.h"
#include "merkleTree.h"

/* use no global variables :^) */
LEAF *push(LEAF *top, unsigned char hash[32], int height)
{
  LEAF *temp = (LEAF*)malloc(sizeof(LEAF));
  /* malloc error checking */
  if(temp == NULL)
  {

    printf("Problem allocating! Exiting...\n");
    exit(0);
  }
  /* copy the hash of to the leaf */
  memcpy(temp->hash.hash, hash, 32);
  /* set height */
  temp->hash.height = height;
  /* make next the top */
  temp->next = top;
  /* set the top as temp */
  top = temp;
  return top;
}

LEAF *pop(LEAF *top)
{
  /* temp to hold current top of stack */
  LEAF *temp = top;
  /* top of stack is the next on stack */
  top = top->next;
  /* free the poppef leaf */
  free(temp);
  return top;
}

void showStack(LEAF *top)
{
  /* function for testing */
  LEAF *curr;
  curr = top;
  int i;
  /* if the stack isnt empty */
  if(curr != NULL)
  {
    /* while curr isnt null */
    while(curr != NULL)
    {
     /* print the height in the tree and the hash */
     printf("Height = %d, HASH = ", curr->hash.height);
      for(i=0; i < 32; i++)
        printf("%02x", curr->hash.hash[i]);
      printf("\n");
      /* move to next leaf */
      curr = curr->next;
    }
    printf("\n");
  }
  else
    printf("Empty!\n");
}

LEAF *getRoot(LEAF *top, Transaction *modBuffer, int trnsAmt)
{
  /* store the hash in here */
  unsigned char hashTemp[HASHSZ];
  int initialHeight, newHeight;
  int trnsInd = 0;
  int rootFlag = FALSE;

  //int temp = 0;

  while(rootFlag == FALSE)
  {
    /* exit case */
    if(stackAmt(top) == 1 && trnsInd == trnsAmt)
    {
      /* exit the loop */
      rootFlag = TRUE;
      /* this would exit it too but whatever */
      return top;
    }
    /* single transaction case */
    else if(trnsAmt == 1)
    {
      printf("SINGLE TRANSACTION CASE\n");
      /* set the initial height */
      initialHeight = 1;
      /* hash the transaction */
      hashTransactions(modBuffer, trnsInd, hashTemp);
      /* push transaction to stack */
      top = push(top, hashTemp, initialHeight);
      /* hash it to itself */
      hashTree(top, top, hashTemp);
      /* get new height => 2 */
      newHeight = initialHeight + 1;
      /* pop the old hash from stack */
      top = pop(top);
      /* push the new hash to stack */
      top = push(top, hashTemp, newHeight);
      /* just return it here */
      showStack(top);
      return top;
    }
    /* if there is 2 atleast in the stack */
    else if(top != NULL && top->next != NULL)
    {
      /* variables for clarity */
      LEAF *leftLeaf = top->next;
      LEAF *rightLeaf = top;
      /* if the stack contains 2 leafs with the same height */
      if(leftLeaf->hash.height == rightLeaf->hash.height)
      {
        printf("MERGING\n");
	/* store height before being popped off */
        newHeight = rightLeaf->hash.height + 1;
        /* hash the leftLeaf+rightLeaf store new hash in hashTemp */
        hashTree(leftLeaf, rightLeaf, hashTemp);
        /* pop off right leaf */
        top = pop(top);
        /* pop off left lead */
        top = pop(top);
        /* push the hash into the stack with the new height */
        top = push(top, hashTemp, newHeight);
      }
      /* odd hash amount case - hash block to self until height */
      else if(trnsInd == trnsAmt && top->hash.height != top->next->hash.height)
      {
        printf("ODD HASH CASE\n");
        /* get new height height */
        newHeight = top->hash.height + 1;
        /* hash the block to itself */
        hashTree(top, top, hashTemp);
        /* pop off the old hash */
        top = pop(top);
        /* push updated into the stack */
        top = push(top, hashTemp, newHeight);
      }
      /* 2 or more in stack but theres mote transactions to add */
      else if(trnsInd < trnsAmt)
      {
        printf("INNER TRNS IND = %d\n", trnsInd);
        /* initialize height of transactions in tree is 1 */
        initialHeight = 1;
        /* hash the transaction itself and store it in hashTemp */
        hashTransactions(modBuffer, trnsInd, hashTemp);
        /* push the hashed transaction to the stack */
        top = push(top, hashTemp, initialHeight);
        trnsInd++;
      }
    }
    /* there is less than 2 in the stack but not a merkle root yet */
    else if(trnsInd < trnsAmt)
    {
      printf("OUTER TRNS IND = %d\n", trnsInd);
      /* initialize height of transactions in tree is 1 */
      initialHeight = 1;
      /* hash the transaction itself and store it in hashTemp */
      hashTransactions(modBuffer, trnsInd, hashTemp);
      /* push the hashed transaction to the stack */
      top = push(top, hashTemp, initialHeight);
      trnsInd++;
    }
    showStack(top);
  }
  /* return the top of stack */
  return top;
}

int stackAmt(LEAF *top)
{
  LEAF *curr;
  curr = top;
  int count = 0;

  /* increase count until last in stack*/
  while(curr != NULL)
  {
    count += 1;
    curr = curr->next;
  }
  /* return amount in stack */
  return count;
}
void addRoot(LEAF *top, Block *blkBuffer)
{
  /* get the last 7 bytes of the root and add to the block header */
  memcpy(blkBuffer->blockHash,top->hash.hash+(32-7), 7);
}

void hashTree(LEAF *left, LEAF *right, unsigned char *hash256)
{
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[HASHSZ];
  unsigned int md_len = HASHSZ;
  /* make all algorithms available */
  OpenSSL_add_all_digests();

  /* spec. the hash type */
  md = EVP_get_digestbyname("SHA256");

  /* create the context */
  mdctx = EVP_MD_CTX_create();

  /* intialize conext */
  EVP_DigestInit_ex(mdctx, md, NULL);

  /* hash the string */
  EVP_DigestUpdate(mdctx, left->hash.hash, HASHSZ);
  EVP_DigestUpdate(mdctx, right->hash.hash, HASHSZ);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  /* copy to unsigned char array */
  memcpy(hash256, md_value, HASHSZ);

  /* free allocated space - destroy >:( */
  EVP_MD_CTX_destroy(mdctx);

  /* call once before exit for reassurance >:) */
  EVP_MD_CTX_cleanup(mdctx);
}

void hashTransactions(Transaction *modBuffer, int trnsInd, unsigned char *hash256)
{
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[HASHSZ];
  unsigned int md_len = HASHSZ;
  /* make all algorithms available */
  OpenSSL_add_all_digests();

  /* spec. the hash type */
  md = EVP_get_digestbyname("SHA256");

  /* create the context */
  mdctx = EVP_MD_CTX_create();

  /* intialize conext */
  EVP_DigestInit_ex(mdctx, md, NULL);

  /* turn to string */
  char hashStruct[8];
  memcpy(hashStruct, &modBuffer[trnsInd], 8);

  /* hash the string */
  EVP_DigestUpdate(mdctx, hashStruct, strlen(hashStruct));
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  /* copy to unsigned char array */
  memcpy(hash256, md_value, HASHSZ);

  /* free allocated space - destroy */
  EVP_MD_CTX_destroy(mdctx);

  /* call once before exit for reassurance */
  EVP_MD_CTX_cleanup(mdctx);
}

void hashBlockHeader(Block *blkBuffer, unsigned char *hash256)
{
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[HASHSZ];
  unsigned int md_len = HASHSZ;
  /* make all algorithms available */
  OpenSSL_add_all_digests();

  /* spec. the hash type */
  md = EVP_get_digestbyname("SHA256");

  /* create the context */
  mdctx = EVP_MD_CTX_create();

  /* intialize conext */
  EVP_DigestInit_ex(mdctx, md, NULL);

  /* turn to string */
  int blkSz = sizeof(Block);
  char hashStruct[blkSz];

  /* copy first 25 bytes from struct into array */
  /* first 25 include prev.hash, blockNum, blockSize, timestamp, blockHash */
  memcpy(hashStruct, &blkBuffer, 25);

  /* hash the string */
  EVP_DigestUpdate(mdctx, hashStruct, strlen(hashStruct));
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  /* copy to unsigned char array */
  memcpy(hash256, md_value, HASHSZ);

  /* free allocated space */
  EVP_MD_CTX_destroy(mdctx);

  /* call once before exit */
  EVP_MD_CTX_cleanup(mdctx);
}

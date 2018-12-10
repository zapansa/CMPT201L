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
/* i wanna fucking die why is my partner fucking useless literally wrote 0 code */ 

TREE *push(TREE *top, char hash[32], int height)
{
  TREE *temp = (TREE*)malloc(sizeof(TREE));
  /* malloc error checking */ 
  if(temp == NULL)
  {

    printf("Problem allocating! Exiting...\n");
    exit(0);
  }
  /* copy the hash of to the leaf */
  memcpy(temp->hash.hash, hash, 32);
  temp->hash.height = height; 
  temp->next = top;
  top = temp;
  return top;
}

TREE *pop(TREE *top, int *height)
{
  TREE *temp = top;
  *height = top->hash.height; 
  top = top->next;
  free(temp);
  return top;  
}

void showStack(TREE *top)
{
  TREE *curr;
  curr = top; 
  int i;
  if(curr != NULL)
  { 
    while(curr != NULL)
    {
     printf("Height = %d, HASH = ", curr->hash.height);
      for(i=0; i < 32; i++)
        printf("%02x", curr->hash.hash[i]); 
      printf("\n");
      curr = curr->next; 
    }
    printf("\n");
  }
  else
    printf("Empty!\n");
}

TREE *getRoot(TREE *top, Transaction *modBuffer, int trnsAmt)
{
  /* store the hash in here */
  char hashTemp[32];
  int height;
  int initialHeight, newHeight;
  int trnsInd = 0;
  int rootFlag = FALSE;

  //int temp = 0; 

  while(rootFlag == FALSE)
  { 
    // printf("ITERATION = %d IND = %d AMT = %d INSTACK = %d\n", temp+1, trnsInd, trnsAmt, stackAmt(top));
    // showStack(top);
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
      top = pop(top, &height);
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
      TREE *leftLeaf = top->next;
      TREE *rightLeaf = top;
      /* if the stack contains 2 leafs with the same height */
      if(leftLeaf->hash.height == rightLeaf->hash.height)
      {
        printf("MERGING\n");
	/* store height before being popped off */
        newHeight = rightLeaf->hash.height + 1;
        /* hash the leftLeaf+rightLeaf store new hash in hashTemp */
        hashTree(leftLeaf, rightLeaf, hashTemp);
        /* pop off right leaf */
        top = pop(top, &height);
        /* pop off left lead */
        top = pop(top, &height);
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
        top = pop(top, &height);
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

int stackAmt(TREE *top)
{
  TREE *curr;
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
void addRoot(TREE *top, Block *blkBuffer)
{
  /* get the last 7 bytes of the root and add to the block header */
  memcpy(blkBuffer->blockHash,top->hash.hash, 7); 
}

void hashTree(TREE *left, TREE *right, char *hash256)
{
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[64];
  unsigned int md_len = 64;
  /* make all algorithms available */
  OpenSSL_add_all_digests();

  /* spec. the hash type */
  md = EVP_get_digestbyname("SHA256");

  /* create the context */
  mdctx = EVP_MD_CTX_create();

  /* intialize conext */
  EVP_DigestInit_ex(mdctx, md, NULL);

  /* hash the string */
  EVP_DigestUpdate(mdctx, left->hash.hash, 64);
  EVP_DigestUpdate(mdctx, right->hash.hash, 64);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  /* copy to unsigned char array */
  memcpy(hash256, md_value, 32);

  /* free allocated space - destroy >:( */
  EVP_MD_CTX_destroy(mdctx);

  /* call once before exit for reassurance >:) */
  EVP_MD_CTX_cleanup(mdctx); 
}

void hashTransactions(Transaction *modBuffer, int trnsInd, char *hash256)
{ 
  EVP_MD_CTX *mdctx;
  const EVP_MD *md;
  unsigned char md_value[64];
  unsigned int md_len = 64;
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
  memcpy(hash256, md_value, 32);
  
  /* free allocated space - destroy >:( */
  EVP_MD_CTX_destroy(mdctx);
  
  /* call once before exit for reassurance >:) */
  EVP_MD_CTX_cleanup(mdctx);
}

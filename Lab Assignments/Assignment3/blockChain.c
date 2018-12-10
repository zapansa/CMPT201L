/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Notes: The main program that allows the
  interactions with a peep. Uses get opt to get cmd-line
  arguments.
*------------------------------------------------------*/

/* TO DO:
  [x] blockSize vs blockSize
  [x] blockNum
  [x] is the timestamp for the block different than the transaction?
  [ ] range checking
  [-] make Transaction trns dynamic
  [x] hashing
*/

/* libraries to include */
#include "blockChain.h"
#include "peepEditor.h"
#include "merkleTree.h"

int main(int argc, char **argv)
{
  /* declared ALL varibles */
  int option;
  int optFlag = FALSE, errFlag = FALSE;
  char *filename = NULL;
  TREE *top = NULL;

  /* peep stuff */
  char *peep = malloc((PEEPLEN+1)*sizeof(char));
  Transaction *modBuffer = malloc(MXTXNUM*sizeof(Transaction));
  Block *blkBuffer = NULL;
  int trnsAmt, blkAmt, timestamp;

  /* cmd line prompt while loop - actually only one option */
  while((option = getopt(argc, argv, "c:e:v:h:p:t:")) != -1)
  {
    /* if this is true exit */
    /* dont let user enter multiple options on one line */
    if(optFlag == TRUE)
      exit(0);

    /* switch statement for the different options */
    switch(option)
    {
      case 'c':
        /* exit the program at next option if any */
        optFlag = TRUE;

        /* get the name of the file */
        filename = optarg;

        /* read from the file */
        errFlag = newBlockChain(peep, &blkBuffer, filename);

        /* get block amount */
        blkAmt = getBlockAmt(errFlag);

        /* create a new peep loop sessions */
        trnsAmt = editor(peep, modBuffer);

        /* if there was transactions made on the buffer */
        if(trnsAmt != 0)
        {
          /* add the transactions to the blkBuffer */
          addTransactions(trnsAmt, blkAmt, modBuffer, &blkBuffer[blkAmt]);

          /* get the merkle root for the transactions */
          top = getRoot(top, modBuffer, trnsAmt);

          /* add the root to the block */
          addRoot(top, &blkBuffer[blkAmt]);

          /* add the previous hash */
          addPreviousHash(&blkBuffer[blkAmt], &blkBuffer[blkAmt]);

          /* hash the block! */
          addBlockHash(&blkBuffer[blkAmt]);

          /* export peep to file */
          writeBlockChain(peep, blkBuffer, errFlag, filename);
        }
        else /* there was no transaction on the block */
          errNoTransactions();
        break;
      case 'e':
        /* exit the program at next option if any */
        optFlag = TRUE;

        /* get the name of the file */
        filename = optarg;

        /* read from the file */
        errFlag = readBlockChain(peep, &blkBuffer, filename);

        /* checking for errors */
        if(errFlag != FALSE) /* file exists */
        {

          /* get block amount */
          blkAmt = getBlockAmt(errFlag);

          /* replay peep for display later */
          /* put replay into peep buff */
          getPeep(blkAmt, peep, modBuffer, blkBuffer);

          /* call editor to edit the peep */
          trnsAmt = editor(peep, modBuffer);

          /* if there was transactions made on the buffer */
          if(trnsAmt != 0)
          {
            /* add the transactions to the blkBuffer */
            addTransactions(trnsAmt, blkAmt, modBuffer, &blkBuffer[blkAmt]);

            /* get the merkle root for the transactions */
            top = getRoot(top, modBuffer, trnsAmt);

            /* add the root to the block */
            addRoot(top, &blkBuffer[blkAmt]);

	    /* add the previous hash */
            addPreviousHash(&blkBuffer[blkAmt], &blkBuffer[blkAmt-1]);

            /* hash the block! */
            addBlockHash(&blkBuffer[blkAmt]);

            /* export peep to file */
            writeBlockChain(peep, blkBuffer, errFlag, filename);
          }
          else /* there was no transaction on the block */
            errNoTransactions();
        }
        else /* doesn't exist - show error */
          errReadWrite(filename);
        break;
       case 'v':
         /* exit the program at next option if any */
         optFlag = TRUE;

         /* get the name of the file */
         filename = optarg;

         /* read from the file */
         errFlag = readBlockChain(peep, &blkBuffer, filename);

         /* checking for errors */
         if(errFlag != FALSE) /* file exists */
         {
           /* returns the amount of blocks via math lol */
           blkAmt = getBlockAmt(errFlag);

           /* function - verify the blockchain */
           verifyBlockChain(blkAmt, blkBuffer);
         }
         else /* doesn't exist - show error */
           errReadWrite(filename);
         break;
      case 'h':
        /* exit the program at next option if any */
        optFlag = TRUE;

        /* get the name of the file */
        filename = optarg;

        /* read from the file */
        errFlag = readBlockChain(peep, &blkBuffer, filename);

        /* checking for errors */
        if(errFlag != FALSE) /* file exists */
        {
          /* returns the amount of blocks via math lol */
          blkAmt = getBlockAmt(errFlag);

          /* print the transactions for each block */
          printTransactions(blkAmt, blkBuffer);
        }
        else /* doesn't exist - show error */
          errReadWrite(filename);
        break;
      case 'p':
        /* there has to be a -b after -p, so check */
        if(argv[3] == NULL || strcmp(argv[3], "-t")) /* order of OR's matter */
        {
          printf("Error! Unable to produce peep. No timestamp given.\n");
          exit(0);
        }
        /* get the name of the file */
        filename = optarg;

        /* import the file */
        errFlag = readBlockChain(peep, &blkBuffer, filename);

        /* check error */
        if(errFlag == FALSE)
        {
          errReadWrite(filename);
          exit(0);
        }
        break;
      case 't':
        /* exit the program at next option if any */
        optFlag = TRUE;

        /* ASCII to integer conversion */
        /* timestamp may be rep'd as an unsigned long, need explicit casting */
        timestamp = atoi(optarg);

        /* get the amount of blocks in a chain */
        blkAmt = getBlockAmt(errFlag);

        /* call to reproduce peep */
        getPeepAtTime(blkAmt, timestamp, peep, modBuffer, blkBuffer);
        break;
      default:
        printf("Unknown input! Try again.\n");
        break;
    }
  }
  /* free all of the buffers - mem leaks */
  free(peep);
  free(modBuffer);
  free(blkBuffer);

  /* exits the program */
  return 0;
}

int newBlockChain(char peep[], Block **blkBuffer, char *filename)
{
  /* file variable */
  FILE *imFile;

  /* open the file for reading - text file? */
  imFile = fopen(filename, "wb");

  /* check if it exists */
  if(imFile)
  {
    /* allocate room for a block, this is going to be the first block */
    *blkBuffer = malloc(sizeof(Block));

    /* clears and initalized peep array */
    peepInitialize(peep);

    /* write the contents of blkBuffer into file */
    fwrite(blkBuffer, sizeof(Block), 1, imFile);

    /* close the file please */
    fclose(imFile);
  }
  else /* file didn't exist */
    return FALSE;

  /* otherwise */
  return (sizeof(Block));
}

int readBlockChain(char peep[], Block **blkBuffer, char *filename)
{
  /* file variable */
  FILE *imFile;
  int imSz;
  int mallocSz, freadSz;

  /* open the file for reading - text file? */
  imFile = fopen(filename, "rb");

  /* check if it exists */
  if(imFile)
  {
    /* find size of the file */
    fseek(imFile, 0, SEEK_END); // FIX
    imSz = ftell(imFile);
    fseek(imFile, 0, SEEK_SET);

    /* manipulated values for allocating and freading into buffer */
    mallocSz = imSz + sizeof(Block);
    freadSz = (imSz/sizeof(Block));

    /* allocate amount into the buffer */
    /* but also give enough room for a block after the old one in the file */
    *blkBuffer = malloc(mallocSz);

    /* reads in the contents of the file into blkBuffer */
    fread(*blkBuffer, sizeof(Block), freadSz, imFile);

    /* :) close the file :) */
    fclose(imFile);
  }
  else /* file didn't exist */
    return FALSE;

  /* otherwise */
  return (mallocSz);
}

int writeBlockChain(char peep[], Block *blkBuffer, int blockSz, char *filename)
{
  /* file variable here */
  FILE *exFile;
  int fwriteSz = blockSz/sizeof(Block);

  /* open file for writing*/
  exFile = fopen(filename, "wb");

  /* file exists */
  if(exFile)
  {
    /* writes into blkBuffer */
    fwrite(blkBuffer, fwriteSz, sizeof(Block), exFile);

    /* close the file */
    fclose(exFile);
  }
  else /* doesn't exist */
    return FALSE;

  /* otherwise successful and */
  return TRUE;
}

void addBlockHash(Block *blkBuffer)
{
  /* store the hash */
  unsigned char hashTemp[HASHSZ];

  /* time at which block was hashed */
  blkBuffer->timestamp = getTimestamp();

  /* hash the block */
  hashBlockHeader(blkBuffer, hashTemp);

  /* use only the last 7 bytes copy hash to head hash */
  memcpy(blkBuffer->headHash, hashTemp+(HASHSZ-7), 7);
}

void addPreviousHash(Block *currBlockBuffer, Block *prevBlockBuffer)
{
  if(currBlockBuffer->blockNum == 1)
  {
    /* it is the first block set to 0 */
    currBlockBuffer->previousHash[0] = '0';
  }
  else
  {
    /* it is not the first block, so copy hash of old block */
    memcpy(currBlockBuffer->previousHash, &prevBlockBuffer->headHash, 7);
  }
}

void errReadWrite(char *filename)
{
  printf("Error! Unable to open file [%s], it may not exist.\n", filename);
}

void errNoTransactions()
{
  printf("There was no transactions made! Block will not be added.\n");
  printf("Exiting...\n");
  exit(0);
}

void addTransactions(int tNum, int blkAmt, Transaction *modBuffer, Block *blkBuffer)
{
  /* variables */
  int i;

  /* just set the stuff for the block so far */
  blkBuffer->blockNum = blkAmt+1;
  blkBuffer->blockSize = tNum;

  /* add the values in to the block struct at index */
  for(i = 0; i < tNum; i++)
  {
    blkBuffer->trns[i].timestamp = modBuffer[i].timestamp;
    blkBuffer->trns[i].mod.position = modBuffer[i].mod.position;
    blkBuffer->trns[i].mod.character = modBuffer[i].mod.character;
    blkBuffer->trns[i].mod.event_type = modBuffer[i].mod.event_type;
  }
}

void printTransactions(int blkAmt, Block *blkBuffer)
{
  /* variables */
  int i, j, k, trnsAmt;

  peepMenuBorder();

  for(i = 0; i < blkAmt; i++)
  {
    trnsAmt = blkBuffer[i].blockSize;

    printf("BLOCK #%d\n", blkBuffer[i].blockNum);
    peepMenuBorder();

    /* print transaction size */
    printf("Transaction Size: %d\n", trnsAmt);

    /* print the block timestamp */
    printf("Block Timestamp: %d\n", (int)blkBuffer[i].timestamp);

    printf("Previous Hash: ");
    if(i == 0) /* previous hash for first block is 0 not a hexadec.*/
    {
      /* not a hexadecimal */
      printf("%c\n", blkBuffer[i].previousHash[0]);
    }
    else
    {
      /* print block hash */
      for(k = 0; k < 7; k++)
        printf("%02x", blkBuffer[i].previousHash[k]);
      printf("\n");
    }

    /* print block hash 7 bytes */
    printf("Block Hash: ");
    for(k = 0; k < 7; k++)
      printf("%02x", blkBuffer[i].blockHash[k]);
    printf("\n");

    /* print block hash */
    printf("Head Hash: ");
    for(k = 0; k < 7; k++)
      printf("%02x", blkBuffer[i].headHash[k]);
    printf("\n-\n");

    /* printing transaction info */
    printf("Transaction History:\n");
    for(j = 0; j < trnsAmt; j++)
    {
      printf("%-10d ", (int)blkBuffer[i].trns[j].timestamp);
      printf("%5d ", blkBuffer[i].trns[j].mod.position);
      printf("%5c ", blkBuffer[i].trns[j].mod.character);
      printf("%5d \n", blkBuffer[i].trns[j].mod.event_type);
    }
   printf("\n");
   peepMenuBorder();
  }
}

int getBlockAmt(int blkBufferByteSz)
{
  return ((blkBufferByteSz/(sizeof(Block)))-1);
}

void getPeepAtTime(int blkAmt, int tmStamp, char *peep, Transaction *modBuffer, Block *blkBuffer)
{
  /* variables */
  int i, j, trnsAmt, fullBlock = FALSE;

  /* max indexes for replaying peep at time */
  int blkInd = 0;
  int trnsInd = 0;

  /* variables for replaying */
  unsigned char replayPos, replayEventType, replayChar;
  int stopReplayTmStamp = 0;

  /* remove whatever is in the peep buffer - just clear it in any way */
  peepInitialize(peep);

  /* get the indexes for where the timestamp is */
  /* so inefficient but it works lol */
  for(i = 0; i < blkAmt; i++)
  {
    /* get the amount of transactions in the block */
    trnsAmt = blkBuffer[i].blockSize;
    /* get the timestamp of the block */
    stopReplayTmStamp = blkBuffer[i].timestamp;
    /* check if it is to be replayed to the whole block */
    if(tmStamp == stopReplayTmStamp) /* replay the whole block */
    {
      /* get the index of the block */
      blkInd = i;
      /* make i == blkAmt to leave loop */
      i = blkAmt;
      /* set to true so the contents of the whole block is played */
      fullBlock = TRUE;
    }
    else /* replay up to a timestamp in the block */
      for(j = 0; j < trnsAmt; j++) /* for all the transactions in the block */
      {
        /* get the timestamp */
        stopReplayTmStamp = blkBuffer[i].trns[j].timestamp;
        /* check if the timestamp matches to the replay timestamp */
        if(tmStamp == stopReplayTmStamp) /* it matches */
        {
          /* get the index of the transactions in a block */
          trnsInd = j;
          /* make j == trnsAmt to leave loop */
          j = trnsAmt;
          /* get the index of the block */
          blkInd = i;
          /* make i == blkAmt to leave loop */
          i = blkAmt;
        }
      }
    /* otherwise check next block */
  }

  /* now replay the transactions in the peep until the indexes from previous for-for loop*/
  for(i = 0; i <= blkInd; i++)
  {
    if(i == blkInd && fullBlock == FALSE) /* replay block until transaction in block */
    {
      /* iterate through the transactions in all the blocks */
      for(j = 0; j <= trnsInd; j++)
      {
        replayChar = blkBuffer[i].trns[j].mod.character;
        replayPos = blkBuffer[i].trns[j].mod.position;
        replayEventType = blkBuffer[i].trns[j].mod.event_type;
        /* check the type of event to replay */
        if(replayEventType == 0) /* inserting event */
        {
          /* insert the character at the position */
          /* its okay to pass peep and modbuffer - nothing gets saved in the end */
          /* this just DISPLAYS the current peep and doesn't add to the block chain */
          pInsert(peep, modBuffer, replayPos, replayChar);
        }
        else /* deleting event */
        {
          /* delete character at position */
          /* its okay to pass peep and modbuffer - nothing gets saved in the end */
          /* this just DISPLAYS the current peep and doesn't add to the block chain */
          pDelete(peep, modBuffer, replayPos);
        }
      }
    }
    else /* replay the whole block */
    {
      trnsAmt = blkBuffer[i].blockSize;
      //printf("block %d Transaction amt: %d\n", i, trnsAmt);
      for(j = 0; j < trnsAmt; j++)
      {
        replayChar = blkBuffer[i].trns[j].mod.character;
        replayPos = blkBuffer[i].trns[j].mod.position;
        replayEventType = blkBuffer[i].trns[j].mod.event_type;
        /* check the type of event to replay */
        if(replayEventType == 0) /* inserting event */
        {
          /* insert the character at the position */
          /* its okay to pass peep and modbuffer - nothing gets saved in the end */
          /* this just DISPLAYS the current peep and doesn't add to the block chain */
          pInsert(peep, modBuffer, replayPos, replayChar);
        }
        else /* deleting event */
        {
          /* delete character at position */
          /* its okay to pass peep and modbuffer - nothing gets saved in the end */
          /* this just DISPLAYS the current peep and doesn't add to the block chain */
          pDelete(peep, modBuffer, replayPos);
        }
      }
    }
  }

  /* show the current string */
  peepString(peep, "REPLAYED PEEP", "Peep At Timestamp");
  peepShowPositions(peep);
}

void getPeep(int blkAmt, char *peep, Transaction *modBuffer, Block *blkBuffer)
{
  /* variables */
  int i, j, trnsAmt;

  /* variables for replaying */
  unsigned char replayPos, replayEventType, replayChar;

  /* remove whatever is in the peep buffer - just clear it in any way */
  peepInitialize(peep);

  for(i = 0; i < blkAmt; i++)
  {
    trnsAmt = blkBuffer[i].blockSize;
    //printf("block %d Transaction amt: %d\n", i, trnsAmt);
    for(j = 0; j < trnsAmt; j++)
    {
      replayChar = blkBuffer[i].trns[j].mod.character;
      replayPos = blkBuffer[i].trns[j].mod.position;
      replayEventType = blkBuffer[i].trns[j].mod.event_type;
      /* check the type of event to replay */
      if(replayEventType == 0) /* inserting event */
      {
        /* insert the character at the position */
        /* its okay to pass peep and modbuffer - nothing gets saved in the end */
        /* this just DISPLAYS the current peep and doesn't add to the block chain */
        pInsert(peep, modBuffer, replayPos, replayChar);
      }
      else /* deleting event */
      {
        /* delete character at position */
        /* its okay to pass peep and modbuffer - nothing gets saved in the end */
        /* this just DISPLAYS the current peep and doesn't add to the block chain */
        pDelete(peep, modBuffer, replayPos);
      }
    }
  }
}

void verifyBlockChain(int blkAmt, Block *blkBuffer)
{
  /* replay all the hashes on the block */
  /* store temp hash */
  unsigned char hashTemp[HASHSZ];
  unsigned char hashCmp[7];
  int i, j, compare;

  /* search though the blocks */
  for(i = 0; i < blkAmt; i++)
  {
    /* get the hash of the block store in temp */
    hashBlockHeader(&blkBuffer[i], hashTemp);

    printf("TEMP: ");
    for(j = 0; j < 7; j++)
      printf("%02x", hashTemp[j]);
    printf("\n");

    /* get the last 7 bytes of new hash store in hashCmp */
    memcpy(hashCmp, hashTemp+(HASHSZ-7), 7);
    /* compare the hashcmp to the hash stored in the block */
    compare = memcmp(hashCmp, &blkBuffer[i].headHash,7);

    /* print block hash */
    printf("NEW: ");
    for(j = 0; j < 7; j++)
      printf("%02x", hashCmp[j]);
    printf("\n");

    /* print block hash */
    printf("OLD: ");
    for(j = 0; j < 7; j++)
      printf("%02x", blkBuffer[i].headHash[j]);
    printf("\n");

    /* if they do not match it is not valid blockchain */
    if(compare != 0)
    {
      /* notify */
      printf("Block #%d hashes do not match!\n", blkBuffer[i].blockNum);
    }
    else
    {
      /* they match */
      printf("Block #%d is verified.\n", blkBuffer[i].blockNum);
    }
  }
}

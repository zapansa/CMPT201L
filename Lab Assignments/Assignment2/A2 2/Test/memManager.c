/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description/Note:

  The specs for myMalloc and myFree on the A2 document is a
  little different (I think) than my implementation. Instead of
  returning an address from myMalloc (the one that changes at
  each time). I return the actual line from which the user data
  starts in the allocated memory block.
  Example:
    If a block is allocated and starts at 72, then what is
    returned from myMalloc is (72+2=)74. This is where the user
    data starts, at byte 74 of the allocated block of memory.
  Similarily, myFree takes in that number 74 (casted) instead of
  the 'address address'. This is the only way I could figure out
  how this works.
  Otherwise I didn't change anything from the directions (I think,
  I feel like I actually might have especially the CDDL).

*------------------------------------------------------*/

/* TO DO:
  [x] Case if there is >8 in memory size - myMalloc
  [x] outputMemory function
! [?] myFree function
! [x] case for adding while theres no more memory
! [?] myMalloc best fit approach
  [x] Multi chunk linking to bin DLL!!
  [x] set bins to point to self again
  [x] needs to be added in decending order
  [?] fix linking problem in binBlock
  [x] fix memIsEmpty() function
  [x] check if the myFree() region is actually exists in the file

  NTS:
  - Its working kind of, but is it working as asked for ?????
*/

#include "memManager.h"

void initializeMem()
{
  /* Allocate the whole memory first */
  myMemory = malloc(MAX_TOTAL_MEMORY);

  /* Initialize all bins and set inital chunk */
 initializeBin();
}

void initializeBin()
{
  /* Declaring Variables */
  int i;

  /* Reference chunks to themselves except */
  for(i=0; i<=(BIN_HEADER_END-4); i+=4)
  {
    *((unsigned short*)(&myMemory[i])) = (unsigned short)i+PAD2;
    *((unsigned short*)(&myMemory[i+PAD2])) = (unsigned short)i;
  }

  /* The last chunk that holds the first memory in bin index 68 (65464-4) */
  /* Adjust size and links with this function :) */
  binBlock((BIN_HEADER_END-4), i, (MAX_TOTAL_MEMORY-BIN_HEADER_END));
}

void *myMalloc(size_t size)
{
  /* Declaring Variables */
  int memSize, bin, lineReturn;
  int firstBlock = 0, varBlock = 0, varBlockSize;
  int remBlockStart, remBlockSize, remBin;

  /* Size is invalid return NULL */
  if(size <= 0 || size > (MAX_TOTAL_MEMORY-BIN_HEADER_END))
  {
    printf("No memory could be allocated.\n");
    return NULL;
  }

  /* 2 for A2, this could be +4 */
  memSize = ALIGN4(size)+2*2;

  /* check if theres no memory left to add the needed mem */
  if(memIsEmpty(memSize)==FALSE)
  {
    printf("No memory could be allocated. Memory is empty.\n");
    return NULL; /* if there isn't, return null */
  }

  /* Check which bin it belongs to */
  bin = findBinLine(memSize);

  /* Checking the fixed bins first under the following conditions */
  if(memSize<=32)
  {
    /* Check appropriate bin first and if it ISNT empty theres an availiable chunk */
    if(binIsEmpty(bin)==FALSE)
    {
      /* Theres a block in the bin */
      /* just used the first one - lifo? or? */
      firstBlock = *((unsigned short*)(&myMemory[bin]))-PAD4; /* PREV LINK */

      /* Change the links*/
      linkBlock(firstBlock);

      /* Make in use */
      useBlock(firstBlock, memSize);
    }
    /* There is no chunks in the appropriate sized bin */
    else if(binIsEmpty(bin)==TRUE)
    {
      /* Go to the next bin and check until there is one with a memory chunk available */
      while(binIsEmpty(bin)==TRUE) /* While loop will stop once there is one with memory */
        bin += 4;

      /* Once while loop finds a bin with memory, check if its the only chunk in bin */
      firstBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;

      /* refrence links to bin to bin */
      linkBlock(firstBlock);

      /* Since the block is bigger, need to split */
      /* get the starting "line" of the remaining block and size */
      remBlockStart = firstBlock+memSize;
      remBlockSize = *((unsigned short*)(&myMemory[firstBlock]))-memSize;

      /* if there's less than 8 bytes just give all */
      if(remBlockSize<8)
      {
        /* By recalculating the size, add the remaining to memSize */
        memSize += remBlockSize;

        /* And reassigning these variables with new memSize */
        remBlockStart = firstBlock+memSize;
        remBlockSize = *((unsigned short*)(&myMemory[firstBlock]))-memSize;
      }

      /* function to get the appropriate size of the remBlock and sets links and stuff */
      remBin = findBinLine(remBlockSize);
      binBlock(remBin, remBlockStart, remBlockSize);

      /* make in use */
      useBlock(firstBlock, memSize);
      }

    /* check with prof on implementation */
    lineReturn = findBlockLine((myMemory+firstBlock+PAD2));

    /* Return the data part of the block to the user */
    return (void*)(size_t)lineReturn+PAD2; /*(myMemory+firstBlock+PAD2) */
  }
  /* in the variable bins */
  else if(memSize>32)
  {
    /* Check appropriate bin first if it isnt empty theres an available chunk */
    if(binIsEmpty(bin)==FALSE)
    {
      /* it is the variable sized bins so you need to check if the chunk fits the needed amount */
      /* Otherwise check the next chunk in the bin until one fits */
      /* This is where the first block in the variable sized bins start */
      varBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;

      /* The size associated with the variable sized chunk in the bin */
      varBlockSize = *((unsigned short*)(&myMemory[varBlock]));

      /* Looping through the variable sized blocks until one fits */
      while(varBlockSize<memSize && varBlock+NEXT != bin)
      {
        varBlock = *((unsigned short*)(&myMemory[varBlock+NEXT]))-PAD4;
        varBlockSize = *((unsigned short*)(&myMemory[varBlock]));
      }

      /* If the first block fits, it's not gonna go into the while loop anyway */
      /* When and if it fits then change the links and split if neccassary */

      /* Case if it is equal to the varBlockSize */
      if(memSize==varBlockSize)
      {
        /* Theres no need to split, just change the links and make in use */
        /* change links in the block */
        linkBlock(varBlock);

        /* Make block in use */
        useBlock(varBlock, memSize);
      }
      else if(memSize<varBlockSize)
      {
        /* Since the varblock is bigger, we're going to need to split the block */
        remBlockStart = varBlock+memSize;
        remBlockSize = *((unsigned short*)(&myMemory[varBlock]))-memSize;

        /* if there's less than 8 bytes just give all */
        if(remBlockSize<8)
        {
          /* By recalculating the size, add the remaining to memSize */
          memSize += remBlockSize;

          /* And reassigning these variables with new memSize */
          remBlockStart = varBlock+memSize;
          remBlockSize = *((unsigned short*)(&myMemory[varBlock]))-memSize;
        }

        /* Find bin for the remBlockSize */
        remBin = findBinLine(remBlockSize);
        binBlock(remBin, remBlockStart, remBlockSize);

        /* change links */
        linkBlock(varBlock);

        /* make the block in use */
        useBlock(varBlock, memSize);
      }
    }
    /* There is nothing in the bin */
    else if(binIsEmpty(bin)==TRUE)
    {
      /* search for the next sized bin with memory*/
      while(binIsEmpty(bin)==TRUE)
        bin+=4;

      /* Since this the next size bin mem is definately bigger than the needed mem amount */
      varBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;

      /* The size associated with the variable sized chunk in the bin */
      varBlockSize = *((unsigned short*)(&myMemory[varBlock]));

      /* change the links */
      linkBlock(varBlock);

      /* Get the info for the remaining block */
      remBlockStart = varBlock+memSize;
      remBlockSize = *((unsigned short*)(&myMemory[varBlock]))-memSize;
      /* if there's less than 8 bytes just give all */

      if(remBlockSize<8)
      {
        /* By recalculating the size, add the remaining to memSize */
        memSize += remBlockSize;

        /* And reassigning these variables with new memSize */
        remBlockStart = varBlock+memSize;
        remBlockSize = *((unsigned short*)(&myMemory[varBlock]))-memSize;
      }

      /* function to get the appropriate size of the remBlock and sets links and stuff */
      remBin = findBinLine(remBlockSize);
      binBlock(remBin, remBlockStart, remBlockSize);

      /* make the block in use */
      useBlock(varBlock, memSize);
    }

    /* check with prof on implementation */
    lineReturn = findBlockLine((myMemory+varBlock+PAD2));

    /* return varblock user data part */
    return (void*)(size_t)lineReturn + PAD2; /* (myMemory+varBlock+PAD2) */
  }
  /* Something happened, cant allocate anything */
  return NULL;
}

void myFree(void *region)
{
  /* Some variables */
  int regStart, regSize, aStatus, bStatus, bin;

  /* Find the line where the region starts */
  /* regStart = findBlockLine(region); */

  /* cast to size_t first, gets rid of the warning, size_t is narrower than into
     shouldn't be a problem on most systems though ? */
  regStart = (size_t)region - PAD2;

  /* Fine the size of the chunk to be freed */
  regSize = *((unsigned short*)(&myMemory[regStart]))-1;

  /* check if the chunk above/below it if free */
  /* if either are free, then combine them */

  /* getting sizes of chunks above/below to check if they free */
  aStatus = *((unsigned short*)(&myMemory[regStart-PAD2]));
  bStatus = *((unsigned short*)(&myMemory[regStart+regSize]));

  /* in either of these conditions it is out of the scope of the
    availible memory */
  /* These conditions for bStatus and aStatus is so that it will never reach */
  if((regStart+regSize)>=MAX_TOTAL_MEMORY)
    bStatus = 1;
  else if(regStart<=BIN_HEADER_END)
    aStatus = 1;

  /* Both blocks are free */
  if(aStatus%4==0 && bStatus%4==0)
  {
    /* free the blocks above and below from the bins */
    freeBlock(regStart-aStatus);
    freeBlock(regStart+regSize);

    /* Get new starline and size */
    regStart = regStart-aStatus;
    regSize = regSize+aStatus+bStatus;

    /* Add the chunk to appropriate bin */
    bin = findBinLine(regSize);
    binBlock(bin, regStart, regSize);
  }
  /* Only the block above is free */
  else if(aStatus%4==0)
  {
    /* free block above from the bins */
    freeBlock(regStart-aStatus);

    /* get new start line and size */
    regStart = regStart-aStatus;
    regSize = regSize+aStatus;

    /* Add the chunk to appropriate bin */
    bin = findBinLine(regSize);
    binBlock(bin, regStart, regSize);
  }
  /* Only the block below is free */
  else if(bStatus%4==0)
  {
    /* free block above from the bins */
    freeBlock(regStart+regSize);

    /* get new start line and size */
    /* where it starts would be the same, just need to extend the size */
    regSize = regSize+bStatus;

    /* Add the chunk to appropriate bin */
    bin = findBinLine(regSize);
    binBlock(bin, regStart, regSize);
  }
  /* no blocks above/below are free - no merging just add to bin */
  else
  {
    /* Add the chunk to appropriate bin */
    bin = findBinLine(regSize);
    binBlock(bin, regStart, regSize);
  }
}

void outputBins()
{
  /* Declaring some variables */
  int bin, binAmt, binSum, binSize, startBlock, nextBlock;
  for(bin=0; bin<=(BIN_HEADER_END-4); bin+=4)
  {
    binAmt = 0;
    binSum = 0;

    /* Check for non empty bins to print info */
    if(binIsEmpty(bin) == FALSE)
    {
      startBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;
      nextBlock = *((unsigned short *)(&myMemory[startBlock+NEXT]));

      /* there is more than 1 chunk in the bin */
      if(nextBlock != (bin+PAD2))
      {
        /* first block */
        binSum += *((unsigned short *)(&myMemory[startBlock]));
        binAmt += 1;
        /* traverse through the bins */
        while(nextBlock != (bin+PAD2))
        {
          startBlock = nextBlock-PAD4; /* goes to the next block startline*/
          nextBlock = *((unsigned short*)(&myMemory[startBlock+NEXT])); /* next block prev line */
          /* add for the following blocks */
          binSum += *((unsigned short *)(&myMemory[startBlock]));
          binAmt += 1;
        }

      }
      /* there is only one chunk in bin */
      else if(nextBlock == (bin+PAD2))
      {
        /* add only once - theres only one block in the bin */
        binSum = *((unsigned short *)(&myMemory[startBlock]));
        binAmt = 1;
      }

      /* print this one bin per one bin stacked */
      binSize = findBinSize(bin); /* look for appropriate bin size */
      printf("+----------+------------+----------+\n");
      printf("|%-10d|%-12d|%-10d|\n", binSize, binAmt, binSum);
      printf("|          |            |          |\n");
    }
  }

}

void outputMemory()
{
  /* Declaring some variables */
  int blockSize, actualSize;
  char blockInUse[] = "IN USE";
  char blockFree[] = "FREE";
  char *blockStatus;
  int lineStart = BIN_HEADER_END, lineEnd;

  /* Check all the blocks till the end */
  while(lineStart != MAX_TOTAL_MEMORY)
  {
    blockSize = *((unsigned short*)(&myMemory[lineStart]));

    /* Check what kind of block for printing */
    if(blockSize%4==1)
    {
      actualSize = blockSize-1;
      blockStatus = blockInUse;
      lineEnd = lineStart+actualSize;
    }
    else
    {
      blockStatus = blockFree;
      lineEnd = lineStart+ blockSize;
    }
    /* Print the info on stdout */
    printf("+---------+-------+------------+-------+\n");
    printf("|%-9s|%-7d|%-12d|%-7d|\n", blockStatus, lineStart, blockSize, lineEnd);
    printf("|         |       |            |       |\n");

    /* Check what kind of block for incrementing */
    if(blockSize%4==1)
      lineStart += actualSize;
    else
      lineStart += blockSize;
  }
}

int binIsEmpty(int bin)
{
  /* Checks if an individual bin is empty */
  if(*((unsigned short*)(&myMemory[bin])) == bin+PAD2)
    return TRUE; /* If a bin is empty return TRUE */
  else
    return FALSE; /* Otherwise it isn't empty and return false */
}

int memIsEmpty(int memSize)
{
  /* declaring some variables */
  int blockSize, actualSize, memLeft = 0;
  int lineStart = BIN_HEADER_END;

  /* while loop to traverse through the block in memory */
  while(lineStart != MAX_TOTAL_MEMORY)
  {
    /* gets the size of the block at index wherever lineStart is */
    blockSize = *((unsigned short*)(&myMemory[lineStart]));

    /* this checks what kind of block it is and what to use to increment to the next block
        also checks if there is enough memory to add the needed amount */
    if(blockSize%4==1) /* the block is used, actual size is -1 the size listed */
    {
      actualSize = blockSize-1;
      lineStart += actualSize;
    }
    else /* the block is free and already shows the actual size */
    {
      lineStart += blockSize;

      /* memLeft becomes the blockSize at every instance memSize is <= blockSize,
        this makes it so that if there a block of memory greater than or equal to
        the requested amount, you can know because memSize will have to be
        atleast the size of the requested amount */
      if(memSize <= blockSize)
        memLeft = blockSize; /* there is some free memory left */
    }
  }

  /* check if that memory that is left is enough to allocate how much mem is needed */
  if(memLeft>=memSize) /* There is enough memory left to allocate */
    return TRUE;
  else /* there is not enough space to allocate */
    return FALSE;
}

int findBinLine(int size)
{
  /* Finds the bin for fixed sizes 8-32 */
  if(size<=32)
  {
    switch (size)
    {
      case 8: return 0;
      case 12: return 4;
      case 16: return 8;
      case 20: return 12;
      case 24: return 16;
      case 28: return 20;
      case 32: return 24;
    }
  } /* Otherwise the size is variable look for a fitting bin */
  else if(size>32 && size<=64)
    return 28;
  else if(size>64 && size<=128)
    return 32;
  else if(size>128 && size<=256)
    return 36;
  else if(size>256 && size<=512)
    return 40;
  else if(size>512 && size<=1024)
    return 44;
  else if(size>1024 && size<=2048)
    return 48;
  else if(size>2048 && size<=4096)
    return 52;
  else if(size>4096 && size<=8192)
    return 56;
  else if(size>8192 && size<=16384)
    return 60;
  else if(size>16384 && size<=32768)
    return 64;
  else if(size>32768 && size<=65536)
    return 68;
  return 0;
}

int findBinSize(int line)
{
  /* find what bin size the "index" correlates with */
  switch(line)
  {
    case 0: return 8;
    case 4: return 12;
    case 8: return 16;
    case 12: return 20;
    case 16: return 24;
    case 20: return 28;
    case 24: return 32;
    case 28: return 64;
    case 32: return 128;
    case 36: return 256;
    case 40: return 512;
    case 44: return 1024;
    case 48: return 2048;
    case 52: return 4096;
    case 56: return 8192;
    case 60: return 16384;
    case 64: return 32768;
    case 68: return 65536;
  }
  return 0;
}

int findBlockLine(void *region)
{
  /* Declaring some variables */
  int blockSize, actualSize, lineStart = BIN_HEADER_END;

  /* iterate blocks to find the start line of the malloc'd region */
  while(lineStart != MAX_TOTAL_MEMORY)
  {
    blockSize = *((unsigned short*)(&myMemory[lineStart]));

    /* If the address is the same */
    if(region == &myMemory[lineStart+PAD2])
      if(blockSize%4) /* check if its a malloc'd point */
        return lineStart; /* Return the line it starts on */

    /* otherwise - Check what kind of block for incrementing */
    if(blockSize%4==1)
    {
      actualSize = blockSize-1;
      lineStart += actualSize;
    }
    else
      lineStart += blockSize;
  }
  /* Its not probably not a valid address */
  /* its not in the scope of the memory */
  return 0;
}

void binBlock(int bin, int newBlock, int size)
{
  /* If there is no chunk in the bin already aka it's empty */
  if(binIsEmpty(bin)==TRUE)
  {
    /* set the size */
    *((unsigned short*)(&myMemory[newBlock])) = (unsigned short)size;
    *((unsigned short*)(&myMemory[size+newBlock-PAD2])) = (unsigned short)size;

    /* Point the bin to the chunk */
    *((unsigned short*)(&myMemory[bin])) = (unsigned short)(newBlock+PREV);
    *((unsigned short*)(&myMemory[bin+PAD2])) = (unsigned short)(newBlock+NEXT);

    /* point the chunk to the bin */
    *((unsigned short*)(&myMemory[newBlock+NEXT])) = (unsigned short)bin+PAD2;
    *((unsigned short*)(&myMemory[newBlock+PREV])) = (unsigned short)bin;
  }
  /* If there is one or more chunks in the bin */
  else
  {
    /* get info on the first block in the bin starting line */
    int binBlock = *((unsigned short*)(&myMemory[bin]))-PAD4;
    int binBlockSize = *((unsigned short*)(&myMemory[binBlock]));
    int nextBlock = *((unsigned short*)(&myMemory[binBlock+NEXT]));
    int blk;

    /* if size is greater than the block in the bin */
    while(size>binBlockSize && nextBlock != (bin+PAD2))
    {
      /* traverse the bin for the next sized block */
      binBlock = nextBlock-PAD4;
      binBlockSize = *((unsigned short*)(&myMemory[binBlock]));

      nextBlock = *((unsigned short*)(&myMemory[binBlock+NEXT]));
    }

    /* leave the while loop */
    /* check sizes */

    /*  If the binBlockSize of the last block after leaving thr while loop is */
    if(binBlockSize<=size)
    {
      /* insert the newBlock before it */

      /* save the next link of the bin block */
      blk = *((unsigned short*)(&myMemory[binBlock+NEXT]));

      /* point the saved link to the newBlock next and visevera */
      *((unsigned short*)(&myMemory[blk])) = (unsigned short)(newBlock+NEXT);
      *((unsigned short*)(&myMemory[newBlock+NEXT])) = (unsigned short)blk;

      /* point the binBlock next link in the newBlock prev and vise versa */
      *((unsigned short*)(&myMemory[binBlock+NEXT])) = (unsigned short)(newBlock+PREV);
      *((unsigned short*)(&myMemory[newBlock+PREV])) = (unsigned short)(binBlock+NEXT);
    }
    /* otherwise it it is more then binBlockSize */
    else
    {
      /* save the previous link of the bin block */
      blk = *((unsigned short*)(&myMemory[binBlock+PREV]));

      /* point the binBlock prev to newBlock next and visevera */
      *((unsigned short*)(&myMemory[binBlock+PREV])) = (unsigned short)newBlock+NEXT;
      *((unsigned short*)(&myMemory[newBlock+NEXT])) = (unsigned short)binBlock+PREV;

      /* point the saved link to newBlock prev and vice versa */
      *((unsigned short*)(&myMemory[blk])) = (unsigned short)newBlock+PREV;
      *((unsigned short*)(&myMemory[newBlock+PREV])) = (unsigned short)blk;
    }

    /* in both cases save the size */
    *((unsigned short*)(&myMemory[newBlock])) = (unsigned short)size;
    *((unsigned short*)(&myMemory[size+newBlock-PAD2])) = (unsigned short)size;
  }
}

void useBlock(int block, int size)
{
  /* remove the links from varblock to the bin */
  *((unsigned short*)(&myMemory[block+NEXT])) = (unsigned short)0;
  *((unsigned short*)(&myMemory[block+PREV])) = (unsigned short)0;

  /* Get that varblock and adjust its size by making it in use */
  *((unsigned short*)(&myMemory[block])) = (unsigned short)(size+1);
  *((unsigned short*)(&myMemory[block+size-PAD2])) = (unsigned short)(size+1);
}

void linkBlock(int block)
{
  /* change the links in the block */
  /* could be to the bin or to the next block, etc */
  /* this basically takes a block out kind of */
  int nxt = *((unsigned short*)(&myMemory[block+NEXT]));
  int pre = *((unsigned short*)(&myMemory[block+PREV]));
  *((unsigned short*)(&myMemory[nxt])) = (unsigned short)pre;
  *((unsigned short*)(&myMemory[pre])) = (unsigned short)nxt;
}

void freeBlock(int block)
{
  /* change links */
  int nxt = *((unsigned short*)(&myMemory[block+NEXT]));
  int pre = *((unsigned short*)(&myMemory[block+PREV]));
  *((unsigned short*)(&myMemory[nxt])) = (unsigned short)pre;
  *((unsigned short*)(&myMemory[pre])) = (unsigned short)nxt;

  /* remove the links from the block to whatever was in it*/
  *((unsigned short*)(&myMemory[block+NEXT])) = (unsigned short)0;
  *((unsigned short*)(&myMemory[block+PREV])) = (unsigned short)0;
}

int checkFree(int region)
{
  /* get the size of value at region-2 */
  int regionSize = *((unsigned short*)(&myMemory[region-PAD2]));

  /* check for this end size of the chunk */
  int regionCheck = *((unsigned short*)(&myMemory[(region-PAD2)+(regionSize-1-PAD2)]));

  /* if equal then it is a free-able block */
  if((regionCheck == 0 && regionSize == 0) || regionSize != regionCheck)
  {
    /* this is not a free block */
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

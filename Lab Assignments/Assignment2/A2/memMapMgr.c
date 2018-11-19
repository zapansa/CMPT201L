/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Description:

  Drives the memManager, this takes command line input.
  -c, -i, -e, -s options only allow one argument.
  Example:
    ./memMapMgr -s test -s test -s test
    only the first test will print, all other will be ignored.
  -a & -b, and -f & -p, are the exceptions to this (sort of).
  -a will check for -b if its not there–exit. -f will do the
  same with -p.

  Choosing -c will initialize the memory and the bins and
  write to a file indicated by the user.

  Choosing -i will only just take the file (if it exists) and
  read its contents into myMemory.

  Chosing -e will export the current myMemory and will write it
  to a file. At this point I don't know what the difference is
  supposed to be for -e and -c :)

  Chosing -s will read the file into myMemory and use the output
  functions from memManager.c to print statistics.

  The options -a and -b must be used together, and they allocate
  memory from a file.

  The options -f and -p must be used together too and they
  free memory at a LOCATION. This location is not the 'address'
  'address' but an index in myMemory.
  Example:
    If a block is allocated and starts at 72 then to free it you
    must add 2 to 72. Thats where the UD starts–at 74, and thats
    the number used to be freed.
    ./memMapMgr -f test -p 74

*------------------------------------------------------*/

/* TO DO:
  [x] Command line input - memMapMgr.c
  [kind of] Error checking
  [x] Testing files
  [x] all argv cases
  [ ] case e and case i clarification. :'(
  [:)] check for leaks
*/

#include "memManager.h"

int main(int argc, char **argv)
{
  /* Declaring Variables */
  int option, errflag, optflag = FALSE;
  int allocSize, freeSize;
  char *filename = NULL;

  /* cmd line prompt loop */
  while((option = getopt(argc, argv, "c:i:e:s:a:b:f:p:")) != -1)
  {
    /* if this is true, exit, dont run the while loop anymore */
    /* so it only takes the first arg on some cases */
    if(optflag == TRUE)
      exit(0);

    /* switch for the options from the command line */
    switch(option)
    {
      case 'c':
        /* only allow one instance of an argument */
        optflag = TRUE;
        /* init memory */
        initializeMem();
        /* the argument after -c is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = emptFile(filename);
        /* if the errflag returns a false */
        if(errflag == FALSE)
          printf("Error! Something went wrong.\n");
        break;
      case 'i':
        /* only allow one instance of an argument */
        optflag = TRUE;
        /* init memory for file to be imported*/
        initializeMem();
        /* the argument after -i is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = impFile(filename);
        /* if the errflag is false here, the file doesn't exist */
        if(errflag == FALSE)
          printf("Error! That filename does not exist.\n");
        break;
      case 'e':
        /* only allow one instance of an argument */
        optflag = TRUE;
        /* init memory */
        initializeMem();
        /* the argument after -e is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = expFile(filename);
        /* if the errflag doesn't exist */
        if(errflag == FALSE)
          printf("Error! Something went wrong.\n");
        break;
      case 's':
        /* only allow one instance of an argument */
        optflag = TRUE;
        /* initialize memory before - so it works lol */
        initializeMem();
        /* the argument after -s is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = statFile(filename);
        /* if the errflag is false here, the file doesn't exist */
        if(errflag == FALSE)
          printf("Error! Unable to print map statistics file may not exist.\n");
        break;
      case 'a':
        /* if the argument following a is not -b */
        if(argv[3] == NULL || strcmp(argv[3], "-b"))
        {
          printf("Error! '-a' needs to be followed by a '-b'\n");
          exit(0);
        }
        /* initialize memory before - so it works lol */
        initializeMem();
        /* the argument after -a is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = impFile(filename);
        /* if the errflag is false here, the file doesn't exist */
        if(errflag == FALSE)
        {
          printf("Error! That filename does not exist.\n");
          exit(0);
        }
        break;
      case 'b':
        /* dont allow options after this exit program */
        optflag = TRUE;
        /* ASCII to int converstion */
        allocSize = atoi(optarg);
        /* returns a void pointer specifying address of allocation */
        myMalloc(allocSize);
        /* export whatevee was manipulated to the file */
        expFile(filename);

        break;
      case 'f':
        /* if the argument following a is not -p */
        if(argv[3] == NULL || strcmp(argv[3], "-p"))
        {
          printf("Error! '-f' needs to be followed by a '-p'\n");
          exit(0);
        }
        /* initialize memory before - so it works lol */
        initializeMem();
        /* the argument after -a is the filename */
        filename = optarg;
        /* returns a true or false if it was successful */
        errflag = impFile(filename);
        /* error checking */
        if(errflag == FALSE)/* the file is invalid or doesn't exist error message */
        {
          printf("Error! That filename does not exit.\n");
          exit(0);
        }
        break;
      case 'p':
        /* dont allow options after this exit program */
        optflag = TRUE;
        /* ASCII to integer converstion */
        freeSize = atoi(optarg);
        /* check if a free-able block */
        if(checkFree(freeSize) == TRUE)
        {
          /* free the block */
          myFree((void*)(size_t)freeSize);
          /* export results back to file */
          expFile(filename);
        }
        else
          printf("Error! That address cannot be freed.\n");
        break;
      case '?': /* Unknown input */
        printf("Error! Make sure filename is specified.\n");
        break;
      default:
        printf("Error! Illegal option.\n");
        break;
    }
  }
  /* so theres no memory leaks */
  free(myMemory);
  return 0;
}

int emptFile(char *filename)
{
  /* writing file variable */
  FILE *mpWrite;
  /* Open the the file for writing */
  mpWrite = fopen(filename, "wb");

  /* If it is null, the user didn't enter the name of a bin file */
  if(mpWrite)
  {
    /* write myMemory into the file */
    fwrite(myMemory, sizeof(myMemory[0]), MAX_TOTAL_MEMORY, mpWrite);
    fclose(mpWrite);
  }
  else
    return FALSE;

  return TRUE;
}

int impFile(char *filename)
{
  /* Declaring file variable */
  FILE *mpRead;

  /* Open the the file for reading */
  mpRead = fopen(filename, "rb");

  /* Check if it exists */
  if(mpRead) /* it exists */
  {
    /* read the file into char *myMemory */
    fread(myMemory, MAX_TOTAL_MEMORY, sizeof(myMemory[0]), mpRead);
    fclose(mpRead);
  }
  else /* it doesn't exist */
    return FALSE;
  /* The file exists and was imported to myMemory*/
  return TRUE;
}

int expFile(char *filename)
{
  /* writing file variable */
  FILE *mpWrite;

  mpWrite = fopen(filename, "wb");

  /* If it is null, the user didn't enter the name of a bin file */
  if(mpWrite)
  {
    /* write myMemory into the file */
    fwrite(myMemory, sizeof(myMemory[0]), MAX_TOTAL_MEMORY, mpWrite);
    fclose(mpWrite);
  }
  else
    return FALSE;

  return TRUE;
}

int statFile(char *filename)
{
  /* Declare file variable */
  FILE *mpRead;

  /* Open the the file for reading */
  mpRead = fopen(filename, "rb");

  /* Check if it exists */
  if(mpRead) /* it exists */
  {
    /* read the file into char *myMemory */
    fread(myMemory, sizeof(myMemory[0]), MAX_TOTAL_MEMORY, mpRead);

    printf("\nMEMORY STATISTICS\n");
    /* Output memory info */
    outputMemory();

    printf("\nBIN STATISTICS\n");
    /* output bin info */
    outputBins();

    /* close the file */
    fclose(mpRead);
  }
  else /* it doesn't exist */
    return FALSE;

  /* the file exists :) */
  return TRUE;
}

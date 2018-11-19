*----------------------------------*
Student's Name: Patricia Zapansa
Lab Assignment #2
Lab Section: 201-X02L
Lab Instructor’s Name: Calin Anton
Course: CMPUT 201
Instructor's Name: Calin Anton
*----------------------------------*

*----------------------------------*
 README
*----------------------------------*
"a text file explaining the content of each file you have included in the directory
and the usage of your submission"

In this, I included the purpose and the contents of certain files. I didn't make
any extra files to work with the main files for assignment 2
(memMapMgr.c, memManager.h, memManager.c), I only used the the files mentioned on
assignment sheet.

I did however, make some 'testing' programs that test by making executables to run.
I've listed them here just incase BUT have not included them in the 'make all' in
my makefile. There will probably be a re-iteration of what they are in the
testing.txt file because for some reason I thought it went in this document
but probably not :)

*----------------------------------*
 Testing Programs
*----------------------------------*

I. memTest1.c
-----
   The purpose of this file is to check myMalloc and myFree. To see if they
   are giving the correct results. Compile and run, and it just prints the
   results of various tests.

   The tests are as follows:
   - test1(): This is my initial test, I just put in a bunch of random numbers
     to check if it even compiles.
   - test2(): This test, I made it so, when I free'd a chunk it would go into
     that bin. Each free'd chunk is separated by another chunk to prevent
     merging in this test. I am testing to see if the linking in the bins is
     working properly.
   - test3(): In this, I am checking to see if the merging will work properly.
     If successful, it should merge into one big block and be put into that
     specific sized bin. The original size'd bin should be empty and not printed.
   - test4(): In this I am checking to see if the initial memory is put inside
     the correct bin.
   - test5(): I am again checking to see if chunks will link to the bin. But this
     time, I'm checking if it will happen twice and to a bigger number too (>32)

   NOTE: Compiled with memManager.c and memManager.h. It create an executable
   called 'memTest1'


II. memTest2.c
-----
   This program looks at the inside of the bins and lists the chunks from beginning
   of the list to the end. Its use is so that I can check if the blocks are in
   increasing order. It contains a function that is derived from the original
   outputBins(). How it works is that it just, One–outputs the bins normally, two–
   prints the non-empty bins size, traverses through the bins, and prints the first
   and the last size of the chunk in the bin.

   There is 3 tests I did, they are:
   - test1(): variable sizes that are >124 but <= 256 are malloc'd, with another
     different sized malloc'd chunk separating them. The variable sizes malloc'd
     earlier are free'd. I am checking to see if the variable sized malloc'd chunks
     all go into the bin in increasing order.
   - test2(): testing to see if even after merging, the new merged chunks would still
     go into the appropriate sized bin in increasing order.
   - test3(): same as test1(), however with fixed sizes. They are all the same size
     just testing to see if it would list all the blocks.

   NOTE: Compiled with memManager.c and memManager.h. It create an executable
   called 'memTest2'.


*----------------------------------*
 Required Files
*----------------------------------*
I. memMapMgr.c
-----
   This file drives memManager.c. It contains the memory manager program. And it
   works with a given memory map. That memory map is a binary file containing
   65k bytes–an external copy of the internal memory of memManager module. Uses getopt
   to get input via the command line.

   Functions Included are:
   - emptFile(): creates an 'empty' memory map. The empty memory map is just myMemory
     initialized with all its bins referencing themselves except the last one which
     contains the initial 65464 bytes.
   - impFile(): This just reads a binary file of a specific name and 'reads' the contents
     of the binary file into myMemory. It basically just copies it into myMemory.
   - expFile(): takes whatever is in myMemory and copies that into a binary file.
   - statFile(): gets a binary file of and reads it into myMemory, then prints out the
     statistics of that file using outputMemory() and outputBins().

II. memManager.c
-----
   This file contains the various functions in regards to the implementation of the
   memory manager. Aside from the required functions,

   This module contains the functions:
   - initializeMem(): This function allocates the myMemory char array with myMalloc and
     then calls initializeBins() to reference the bins to itself except the very last
     bin containing the initial 65464 chunk of memory.
   - initalizeBin(): References all the bins to itself and then takes the initial
     65646 chunk and places it in the correct bin.
   - binIsEmpty(): function checks if a bin is empty via an if and else. It checks if a
     bin at a location references itself. Returns true or false (1 or 0).
   - memIsEmpty(): This function is called at the beginning of myMalloc. It checks if
     there is enough room to allocate a size. It checks the size, and then checks the
     contents of myMemory and figures out if there is memory left via a while loop
     that traverses all the in-use and free blocks in all of myMemory.
   - findBinLine(): Depending on how big a size is, it checks the index of a certain bin
     that can fit the size. Via if/elseif and switch, it returns the index of a bin
     fitting a certain size.
   - findBinSize(): Does the opposite of findBinLine(). Gets the index of a bin and
     returns the size to which it pertains to via a switch.
   - binBlock(): This function is the worst. It determines the 'links' of a chunk to a
     bin. It does re-linking, either with myFree, or with the remaining chunk of myMalloc
     it is also used in initializeBins to link the initial chunk to a bin. It adds the
     chunk to the bin in increasing order (first to last).
   - useBlock(): Sets the values of a block to 'used', basically by adding 1 to its
     original size.
   - linkBlock(): This block takes the links off a block that is in use, and transfers
     that blocks link to the blocks/bins beside it.
   - freeBlock(): Does the same thing as link block, it could honestly just be one function
     instead of 2 that do similar things.
   - checkFree(): This function is used in memMapMgr.c as a means of checking if a region
     or inputted size is a valid region to free. Kind of in a way, checks if a block
     starting at a region exists or not, and if it does--is free-able.


III. memManager.h
-----
   This program contains some macro-definitions and the function declarations of the files
   memManager.c and memMapMgr.c as well as the descriptions of each function.

*----------------------------------*
 Executables
*----------------------------------*
   The executable files created will be called
   - memMapMgr: Compiled with memManager.c and memManager.h and memMapMgr.c. It is the main
     program as written in the A2 sheets, that takes input from the command line.

   - memTest1: Compiled with memManager.c and memManager.h and memTest1.c. It serves only
     to test the if myMalloc, myFree, outputBins, and outputMemory are working as intended
     under certain directions.

   - memTest2: Compiled with memManager.c and memManager.h and memTest2.c. After passing the
     memTest1, and having a somewhat functioning memManager, this mainly just tests if
     the chunks in each bin are getting linked in increasing order.

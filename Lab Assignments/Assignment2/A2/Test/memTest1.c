/*-------------------------------------------------------
# Student's Name: Patricia Zapansa
# Lab Assignment #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton
# Program Description: This is just a program I used to check myMalloc and
  myFree. Compile and run, and it just prints the results of various tests.
  - test1(): This is my inital test, I just put in a bunch of random numbers
    to check if it even compiles.
  - test2(): This test, I made it so, when I free'd a chunk it would go into
    that bin. Each free'd chunk is separated by another chunk to prevent
    merging in this test. I am testing to see if the linking in the bins is
    working properly.
  - test3(): In this, I am checking to see if the merging will work properly.
    If successful, it should merge into one big block and be put into that
    specific sized bin. The original size'd bin should be empty and not printed.
  - test4(): In this I am checking to see if the inital memory is put inside
    the correct bin.
  - test5(): I am again checking to see if chunks will link to the bin. But
    this time, I'm checking if it will happen twice and to a bigger number too
    (>32)
*------------------------------------------------------*/

#include "memManager.h"

char SEPARATOR[] = "******************************************************";

void test1();
void test2();
void test3();
void test4();
void test5();

int main(void)
{
  test1();
  test2();
  test3();
  test4();
  test5();
}

void test1()
{
  /* Random case */
  initializeMem();
  void *x = myMalloc(12);
  myMalloc(23);
  myMalloc(300);
  myMalloc(12);
  void *y = myMalloc(50);

  myFree(x);
  myFree(y);

  printf("\nMemory Stats:\n");
  outputMemory();
  printf("\nBin Stats:\n\n");
  outputBins();
  printf("\n%s\n", SEPARATOR);
  /* Correct:
      Memory Stats:
      +---------+-------+------------+-------+
      |FREE     |72     |16          |88     |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |88     |29          |116    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |116    |305         |420    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |420    |17          |436    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |436    |65100       |65536  |
      |         |       |            |       |

      Bin Stats:

      +----------+------------+----------+
      |16        |1           |16        |
      |          |            |          |
      +----------+------------+----------+
      |65536     |1           |65100     |
      |          |            |          |

      Size 16 is only free'd once, should go into the bin
      Bin for 65365 should be (16+28+305+16) = 65100
  */
}

void test2()
{
  /* freeing same amount, checking if they go into the bins */
  initializeMem();
  void *a = myMalloc(12);
  myMalloc(400);
  void *b = myMalloc(12);
  myMalloc(400);
  void *c = myMalloc(12);
  myMalloc(400);
  myMalloc(333);
  void *d = myMalloc(12);
  myMalloc(400);

  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);

  printf("\nMemory Stats:\n");
  outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  printf("\n%s\n", SEPARATOR);
  /* Correct
    Memory Stats:
    +---------+-------+------------+-------+
    |FREE     |72     |16          |88     |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |IN USE   |88     |405         |492    |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |FREE     |492    |16          |508    |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |IN USE   |508    |405         |912    |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |FREE     |912    |16          |928    |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |IN USE   |928    |405         |1332   |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |IN USE   |1332   |341         |1672   |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |FREE     |1672   |16          |1688   |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |IN USE   |1688   |405         |2092   |
    |         |       |            |       |
    +---------+-------+------------+-------+
    |FREE     |2092   |63444       |65536  |
    |         |       |            |       |

    Bin Stats:

    +----------+------------+----------+
    |16        |4           |64        |
    |          |            |          |
    +----------+------------+----------+
    |65536     |1           |63444     |
    |          |            |          |

    The free'd blocks should have gone into the bins
    4 free'b blocks * 16 = 64
*/
}
void test3()
{
  /* check merging */
  initializeMem();
  void *a = myMalloc(12);
  void *b = myMalloc(12);
  void *c = myMalloc(12);
  void *d = myMalloc(12);
  myMalloc(12);

  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);

  printf("\nMemory Stats:\n");
  outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  printf("\n%s\n", SEPARATOR);
  /* Correct:
      Memory Stats:
      +---------+-------+------------+-------+
      |FREE     |72     |64          |136    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |136    |17          |152    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |152    |65384       |65536  |
      |         |       |            |       |

      Bin Stats:

      +----------+------------+----------+
      |64        |1           |64        |
      |          |            |          |
      +----------+------------+----------+
      |65536     |1           |65384     |
      |          |            |          |

      The blocks should have merged together with a joint size of 16 * 4 = 64.
      The merged block should have went to the variable sized bin.
  */
}

void test4()
{
  initializeMem();
  printf("\nMemory Stats:\n");
  outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  printf("\n%s\n", SEPARATOR);
  /* Correct:
    Memory Stats:
    +---------+-------+------------+-------+
    |FREE     |72     |65464       |65536  |
    |         |       |            |       |

    Bin Stats:
    +----------+------------+----------+
    |65536     |1           |65464     |
    |          |            |          |

    The single chunk of memory should be at size 65464 in the very
    last bin.
  */
}

void test5()
{
  /* see if bigger sizes work too ask well as multiple bins being unfree */
  initializeMem();
  void *a = myMalloc(12);
  myMalloc(24);
  void *b = myMalloc(500);
  myMalloc(24);
  void *c = myMalloc(12);
  myMalloc(24);
  void *d = myMalloc(500);
  myMalloc(24);
  void *e = myMalloc(12);
  myMalloc(24);
  void *f = myMalloc(500);
  myMalloc(24);

  myFree(a);
  myFree(b);
  myFree(c);
  myFree(d);
  myFree(e);
  myFree(f);


  printf("\nMemory Stats:\n");
  outputMemory();
  printf("\nBin Stats:\n");
  outputBins();
  printf("\n%s\n", SEPARATOR);

  /* Correct:
      Memory Stats:
      +---------+-------+------------+-------+
      |FREE     |72     |16          |88     |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |88     |29          |116    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |116    |504         |620    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |620    |29          |648    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |648    |16          |664    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |664    |29          |692    |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |692    |504         |1196   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |1196   |29          |1224   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |1224   |16          |1240   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |1240   |29          |1268   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |1268   |504         |1772   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |IN USE   |1772   |29          |1800   |
      |         |       |            |       |
      +---------+-------+------------+-------+
      |FREE     |1800   |63736       |65536  |
      |         |       |            |       |

      Bin Stats:
      +----------+------------+----------+
      |16        |3           |48        |
      |          |            |          |
      +----------+------------+----------+
      |512       |3           |1512      |
      |          |            |          |
      +----------+------------+----------+
      |65536     |1           |63736     |
      |          |            |          |

      There should be 3 chunks in both the size 16 bin and 512.
  */
}

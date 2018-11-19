#--------------------------------------------------------------------#
# Student's Name: Patricia Zapansa                                   #
# Lab Excercise #6 makefile                                          #
# Lab Section: 201-X02L                                              #
# Lab Instructor’s Name: Calin Anton                                 #
# CMPUT 201                                                          #
# Instructor's Name: Calin Anton                                     #
#--------------------------------------------------------------------#

CFLAGS = -Wall -g
CC = gcc

#----------------------------Excecutables----------------------------#

all: memMapMgr

memMapMgr: memMapMgr.o memManager.o
	$(CC) $(CFLAGS) -o memMapMgr memMapMgr.o memManager.o

memMapMgr.o: memMapMgr.c memManager.h
	$(CC) $(CFLAGS) -c memMapMgr.c

memManager.o: memManager.c memManager.h
	$(CC) $(CFLAGS) -c memManager.c

memTest1: memTest1.o memManager.o
	$(CC) $(CFLAGS) -o memTest1 memTest1.o memManager.o

memTest1.o: memTest1.c memManager.h
	$(CC) $(CFLAGS) -c memTest1.c

memTest2: memTest2.c memManager.h
	$(CC) $(CFLAGS) -o memTest2 memTest1.o memManager.o

memTest2.o: memTest2.c memManager.h
	$(CC) $(CFLAGS) -c memTest2.c

#-----------------------------Testing Targets---------------------------#

test1:
	./memMapMgr -c test1
	./memMapMgr -s test1 > outputTest1

test2:
	./memMapMgr -c test2
	./memMapMgr -a test2 -b 100
	./memMapMgr -a test2 -b 12
	./memMapMgr -a test2 -b 50
	./memMapMgr -a test2 -b 65000
	./memMapMgr -a test2 -b 50
	./memMapMgr -a test2 -b 224
	./memMapMgr -s test2 > outputTest2

test3:
	./memMapMgr -c test3
	./memMapMgr -a test3 -b 16
	./memMapMgr -a test3 -b 10
	./memMapMgr -a test3 -b 16
	./memMapMgr -a test3 -b 10
	./memMapMgr -a test3 -b 16
	./memMapMgr -a test3 -b 24
	./memMapMgr -a test3 -b 16
	./memMapMgr -a test3 -b 128
	./memMapMgr -a test3 -b 144
	./memMapMgr -a test3 -b 10
	./memMapMgr -f test3 -p 74
	./memMapMgr -f test3 -p 94
	./memMapMgr -f test3 -p 130
	./memMapMgr -f test3 -p 146
	./memMapMgr -f test3 -p 166
	./memMapMgr -f test3 -p 214
	./memMapMgr -f test3 -p 494
	./memMapMgr -s test3 > outputTest3

test4:
	./memMapMgr -c test4
	./memMapMgr -a test4 -b 65460
	./memMapMgr -a test4 -b 100 > outputTest4
	./memMapMgr -a test4 -b 100 >> outputTest4
	./memMapMgr -a test4 -b 100 >> outputTest4
	./memMapMgr -s test4 >> outputTest4

test5:
	./memMapMgr -c test5
	./memMapMgr -a test5 -a test5 -a test5 > outputTest5
	./memMapMgr -i testrhebf >> outputTest5
	./memMapMgr -i test5 >> outputTest5
	./memMapMgr -s testuir >> outputTest5
	./memMapMgr -a dddff -c test5 >> outputTest5
	./memMapMgr -f ffw -a -f -f >> outputTest5
	./memMapMgr -a hello -b 800 >> outputTest5
	./memMapMgr -f Hey -p 900 >> outputTest5
	./memMapMgr -a test5 -b 700 >> outputTest5
	./memMapMgr -s test5 -s test5 >> outputTest5

test6:
	./memMapMgr -c test6
	./memMapMgr -i nonRealFile > outputTest6
	./memMapMgr -a test6 -b 65460 >> outputTest6
	./memMapMgr -a test6 -b 100 >> outputTest6
	./memMapMgr -a 6test -b 100 >> outputTest6
	./memMapMgr -a eeeee -c error >> outputTest6
	./memMapMgr -s test6 >> outputTest6
	./memMapMgr -s nonFile >> outputTest6
	./memMapMgr -f test6 -p 9000 >> outputTest6
	./memMapMgr -f test6 -b 9000 >> outputTest6
	./memMapMgr -f 9000 >> outputTest6

test7: memTest1 memTest2
	./memTest1 > outputMemTest1
	./memTest2 > outputMemTest2

testAll: test1 test2 test3 test4 test5 test6 test7

testCheck:
	diff outputTest1 correctTest1
	diff outputTest2 correctTest2
	diff outputTest3 correctTest3
	diff outputTest4 correctTest4
	diff outputTest5 correctTest5
	diff outputTest6 correctTest6
	diff outputMemTest1 correctMemTest1
	diff outputMemTest2 correctMemTest2

#---------------------------------Other---------------------------------#

clean: #-f to ignore, source: https://bit.ly/2DKKC77
	rm -f *.o *~ test? memMapMgr memTest?

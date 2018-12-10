#--------------------------------------------------------------------#
# Student's Name: Patricia Zapansa                                   #
# Lab Excercise #6 makefile                                          #
# Lab Section: 201-X02L                                              #
# Lab Instructor’s Name: Calin Anton                                 #
# CMPUT 201                                                          #
# Instructor's Name: Calin Anton                                     #
#--------------------------------------------------------------------#

CFLAGS = -Wall -g -lcrypto
CC = gcc

#----------------------------Excecutables----------------------------#

all: peepTest

peepTest: blockChain.o peepEditor.o merkleTree.o
	$(CC) $(CFLAGS) -o peepTest blockChain.o peepEditor.o merkleTree.o

peepEditor.o: peepEditor.h peepEditor.c
	$(CC) $(CFLAGS) -c peepEditor.c

blockChain.o: blockChain.c blockChain.h
	$(CC) $(CFLAGS) -c blockChain.c

merkleTree.o: merkleTree.c merkleTree.h
	$(CC) $(CFLAGS) -c merkleTree.c

clean:
	rm -f *.o

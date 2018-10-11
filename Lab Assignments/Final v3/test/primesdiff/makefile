# Student's Name: Patricia Zapansa
# Lab Assignment #1 Exercise #5
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton


# Makefile for testing the primesdiff program

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

# Compile program
primesdiff: primesdiff.c
	$(CC) $(CFLAGS) primesdiff.c -o primesdiff $(LDLIBS)
# Test target for user input
test:
	./primesdiff
# Test target for multi-line input
test1:
	./primesdiff < testInputPrimesDiff1 > testOutputPrimesDiff1
# Test target for single line input
test2:
	./primesdiff < testInputPrimesDiff2 > testOutputPrimesDiff2
	./primesdiff < testInputPrimesDiff3 > testOutputPrimesDiff3
# Checking testfiles to see if they yield correct output
checktest:
	diff testOutputPrimesDiff1 ansPrimesDiff1
	diff testOutputPrimesDiff2 ansPrimesDiff2
	diff testOutputPrimesDiff3 ansPrimesDiff3
# Test target to do all testing previously mentioned
testall: test1 test2 checktest
# Remove unneeded files
clean:
	rm *~

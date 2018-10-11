# student's Name: Patricia Zapansa
# Lab Assignment #1 Exercise #4
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton


# Makefile for testing the squeeze program

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

squeeze: squeeze.c
	$(CC) $(CFLAGS) squeeze.c -o squeeze $(LDLIBS)
# Test target for user inputted testing
test:
	./squeeze
# Test target for multi-line file input
test1:
	./squeeze < testInputSqueeze1 > testOutputSqueeze1
# Test target for single-line file input
test2:
	./squeeze < testInputSqueeze2 > testOutputSqueeze2
	./squeeze < testInputSqueeze3 > testOutputSqueeze3
# Checking testfiles to see if they yield correct output
checktest:
	diff testOutputSqueeze1 ansSqueeze1
	diff testOutputSqueeze2 ansSqueeze2
	diff testOutputSqueeze3 ansSqueeze3
# Test target to do all testing previously mentioned
testall: test1 test2 checktest test
# Remove uness. files
clean:
	rm *~

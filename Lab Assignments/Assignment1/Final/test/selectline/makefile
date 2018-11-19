# student's Name: Patricia Zapansa
# Lab Assignment #1 Exercise #1
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton


# Makefile for testing the select line program

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

selectline: selectline.c
	$(CC) $(CFLAGS) selectline.c -o selectline $(LDLIBS)
# Test target for user inputted testing
test:
	./selectline
# Test target for multi-line file input
test1:
	./selectline < testInputSelectLine1 > testOutputSelectLine1
# Test target for single-line file input
test2:
	./selectline < testInputSelectLine2 > testOutputSelectLine2
	./selectline < testInputSelectLine3 > testOutputSelectLine3
	./selectline < testInputSelectLine4 > testOutputSelectLine4
	./selectline < testInputSelectLine5 > testOutputSelectLine5
# Checking testfiles to see if they yield correct output
checktest:
	diff testOutputSelectLine1 ansSelectLine1
	diff testOutputSelectLine2 ansSelectLine2
	diff testOutputSelectLine3 ansSelectLine3
	diff testOutputSelectLine4 ansSelectLine4
	diff testOutputSelectLine5 ansSelectLine5
# Test target to do all testing previously mentioned
testall: test1 test2 checktest
# Remove uness. files
clean:
	rm *~

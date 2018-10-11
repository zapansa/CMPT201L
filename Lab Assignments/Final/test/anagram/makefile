# student's Name: Patricia Zapansa
# Lab Assignment #1 Exercise #3
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

# Makefile for testing the anagram program

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

anagram: anagram.c
	$(CC) $(CFLAGS) anagram.c -o anagram $(LDLIBS)
# Test target for user inputted testing
test:
	./anagram
# Test target for multi-line file input
test1:
	./anagram < testInputAnagram1 > testOutputAnagram1
# Test target for single-line file input
test2:
	./anagram < testInputAnagram2 > testOutputAnagram2
	./anagram < testInputAnagram3 > testOutputAnagram3
# Checking testfiles to see if they yield correct output
checktest:
	diff testOutputAnagram1 ansAnagram1
	diff testOutputAnagram2 ansAnagram2
	diff testOutputAnagram3 ansAnagram3
# Test target to do all testing previously mentioned
testall: test1 test2 checktest test
# Remove uness. files
clean:
	rm *~

# student's Name: Patricia Zapansa
# Lab Assignment #1 Exercise #2
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

# Makefile for testing the printfamday program

CFLAGS = -Wall
LDLIBS = -lm
CC = gcc

printfamday: printfamday.c
	$(CC) $(CFLAGS) printfamday.c -o printfamday $(LDLIBS)
# Test target for user inputted testing
test:
	./printfamday
# Test target for multi-line file input
test1:
	./printfamday < testInputPrintFamDay1 > testOutputPrintFamDay1
	./printfamday < testInputPrintFamDay2 > testOutputPrintFamDay2
# Test target for single-line file input
test2:
	./printfamday < testInputPrintFamDay3 > testOutputPrintFamDay3
	./printfamday < testInputPrintFamDay4 > testOutputPrintFamDay4
# Checking testfiles to see if they yield correct output
checktest:
	diff testOutputPrintFamDay1 ansPrintFamDay1
	diff testOutputPrintFamDay2 ansPrintFamDay2
	diff testOutputPrintFamDay3 ansPrintFamDay3
	diff testOutputPrintFamDay4 ansPrintFamDay4
# Test target to do all testing previously mentioned
testall: test1 test2 checktest
# Remove uness. files
clean:
	rm *~

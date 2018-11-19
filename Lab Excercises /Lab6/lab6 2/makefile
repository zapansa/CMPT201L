# Student's Name: Patricia Zapansa
# Lab Excercise #6 makefile
# Lab Section: 201-X02L
# Lab Instructor’s Name: Calin Anton
# CMPUT 201
# Instructor's Name: Calin Anton

CFLAGS = -Wall
CC = gcc

lab6E1: lab6E1.c dynamicArray.c 
	$(CC) -c lab6E1.c
	$(CC)    -c -o dynamicArray.o dynamicArray.c
	$(CC) -o lab6E1 dynamicArray.o lab6E1.o
lab6E2: lab6E2.c stuff.c
	$(CC) -c lab6E2.c
	$(CC)    -c -o stuff.o stuff.c
	$(CC) -o lab6E2 stuff.o lab6E2.o
clear: 
	rm *.o *~